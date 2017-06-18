//
//  Builder.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Builder.hpp"

Builder::Builder(char* sourceCode){
    Automat* automat = new Automat(AUTOMAT);
    FileReader* fileReader = new FileReader(sourceCode);
    
    try {
        Tokens = automat->Work(fileReader->ReadSourceCode());
    } catch (Exceptions e) {
        throw new Exception("Ошибка конечного автомата", 0);
    }
    
    if (automat)
        delete automat;
    
    if (fileReader)
        delete fileReader;
    
    Tokens = ConvertToNewToken(Tokens);
    
    PrintList(Tokens);
    
    Prioritize(Tokens);
    
    Root = NULL;
    CurrentList = NULL;
    CurrentScope = NULL;
}


Builder::~Builder(){
    if (Tokens)
        delete Tokens;
    
    if (Root)
        delete Root;
    
    if (CurrentScope)
        delete CurrentScope;
    
    if (CurrentList)
        delete CurrentList;
    
    Tokens = NULL;
    Root = NULL;
    CurrentList = NULL;
    CurrentScope = NULL;
}



// Запуск выполения дерева.
void Builder::Run(){
    
    if (Root)
        Root->Execute();
    else
        throw new Exception("Необходимо построить синтексное дерево до выполнения", 0);
}


//Вывод списка лексем, результата работы конечного автомата.
void Builder::PrintList(List* tokens)
{
    char* stringToken[] = { "String", "SingleLineComment", "MultilineComment", "Digit", "Char", "Bracket", "ReservedWord", "Star", "CompOper", "LogicOper", "BiteOp", "Assignment", "SysFunction", "Separator", "UserType", "Space", "NewLine", "ReservedType", "Condition", "ApOp", "IncOrDec" };
    
    cout << "Type\t\tValue\t\tPriority\n";
    for (int i = 0; i < Tokens->count(); i++)
    {
        NewToken* token = (NewToken*)Tokens->get(i);
        
        cout << stringToken[token->Type] << " ";
        cout << token->String << " ";
        cout << token->Priority << " ";
        cout << token->Value << " ";
        cout << token->LineIndex << endl;
    }
}


//Построение дерева операций, которое затем выполняется командой Execute() и дерева областей видимости, хранящего константы, переменные, массивы.
void Builder::Build(){
    try {
        Root = CurrentList = new IndependentOperationsNode();
        CurrentScope = CurrentList->GetScope();
        
        ParseMultiLine(0, Tokens->count());
    } catch (Exceptions e) {
        if (e == Exceptions::ArgumentOutOfRange)
            throw new Exception("UnexpectedEndOfFile: неожиданный конец файла.", 0);
            
        throw e;
    }
    
}



//Возвращает true, если число является дробным, и false в противном случае.
bool Builder::IsFraction(char* Str){
    bool IsPower = false;
    
    for (int i = 0; i < strlen(Str); i++) {
        if (Str[i] == '.')
            return true;
        if (Str[i] == 'e' || Str[i] == 'E')
            IsPower = true;
        if (Str[i] == 'x' || Str[i] == 'X')
            return  false;
    }
    
    if (IsPower)
        return true;
    
    return false;
}


//Конвертирует в double целые числа в различных системах и дробные числа.
double Builder::StringToDouble(char* Str){
    return IsFraction(Str) ? atof(Str) : strtol(Str, nullptr, 0);
}


//Возвращает индекс парной для OpeningBracketIndex скобки.

//Если скобка не найдена или OpeningBracketIndex не является скобкой, выбрасывает Exceptions::MissingBracket.
int Builder::ClosingBracketIndex(int OpeningBracketIndex){
    char* openBracket = ((NewToken*)Tokens->get(OpeningBracketIndex))->String;
    char* closeBracket;
    
    if (!strcmp(openBracket, "("))
        closeBracket = ")";
    else
        if (!strcmp(openBracket, "["))
            closeBracket = "]";
        else
            if (!strcmp(openBracket, "{"))
                closeBracket = "}";
            else
                throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get (OpeningBracketIndex))->LineIndex);
    
    for (int bracketCount = 0, i = OpeningBracketIndex; i < Tokens->count(); i++) {
        char* NextToket = ((NewToken*)Tokens->get(i))->String;
        
        if (!strcmp(NextToket, openBracket))
            bracketCount++;
        
        if (!strcmp(NextToket, closeBracket)){
            bracketCount--;
            
            if (!bracketCount)
                return i;
        }
    }
    
    throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(OpeningBracketIndex))->LineIndex);
}


//Находит индекс операции с минимальным приоритетом в списке tokens
int Builder::FindOperationWithMinimalPriority(int StartPosition , int FinishPosition){
    //16 уровней приоритета операций от 1 до 16
    int minPriority = 0;
    int resultPosition = -1;
    
    for (int i = StartPosition; i < FinishPosition + 1 && i < Tokens->count(); i++) {
        NewToken* nextToken = (NewToken*)Tokens->get(i);
        
        if (isOperator(nextToken->Type)){
            if (!strcmp("[", nextToken->String) && minPriority == 0){
                int temp = ClosingBracketIndex(i);
                
                if (temp == FinishPosition)
                    return i;
                else
                    i = temp;
            }
        }
        //Присваивание
        if (nextToken->Priority > minPriority && nextToken->Priority == 15){
            minPriority = nextToken->Priority;
            resultPosition = i;
        }
        //Другие операции
        if (nextToken->Priority >= minPriority && nextToken->Priority != 15){
            minPriority = nextToken->Priority;
            resultPosition = i;
        }
        
        //Смещение на закрывающую круглую скобку
        if (nextToken->Type == Automat::Bracket && !strcmp("(", nextToken->String))
            i = ClosingBracketIndex(i);
        
    }
    
    if (resultPosition == -1){
        throw new Exception("InvalidOperation: недопустимая операция.", ((NewToken*)Tokens->get (StartPosition))->LineIndex);
    }
    
    return resultPosition;
}

//Проставляет значения приоритета для операций в списке tokens от 1 до 16, где 1 - наивысший приоритет.
void Builder::Prioritize(List* ToketList){
    NewToken* currentToken = NULL;
    NewToken* previousToken = NULL;
    
    for (int i = 0; i < ToketList->count(); i++) {
        if (i > 0)
            previousToken = currentToken;
        
        currentToken = (NewToken*)ToketList->get(i);
        
        if (isOperator(currentToken->Type)){
            char* tempStr = currentToken->String;
            
            if (!strcmp(tempStr, ",")){
                currentToken->Priority = 16;
                continue;
            }
            
            if (!strcmp(tempStr, "=")){
                currentToken->Priority = 15;
                continue;
            }
            
            if (!strcmp(tempStr, "?") || !strcmp(tempStr, ":"))
            {
                currentToken->Priority = 14;
                continue;
            }
            
            if (!strcmp(tempStr, "||"))
            {
                currentToken->Priority = 13;
                continue;
            }
            
            if (!strcmp(tempStr, "&&"))
            {
                currentToken->Priority = 12;
                continue;
            }
            
            if (!strcmp(tempStr, "|"))
            {
                currentToken->Priority = 11;
                continue;
            }
            
            if (!strcmp(tempStr, "^"))
            {
                currentToken->Priority = 10;
                continue;
            }
            
            
            //Разыменование указателя , взятие адреса, унарные плюс и минус, префиксные инкремент и декремент.
            if (!strcmp(tempStr, "*") || !strcmp(tempStr, "&") || !strcmp(tempStr, "+") || !strcmp(tempStr, "-") || !strcmp(tempStr, "++") || !strcmp(tempStr, "--"))
                currentToken->Priority = 2;
            
            if ((!strcmp(tempStr, "+") || !strcmp(tempStr, "-")) && ((previousToken->Type == Automat::Token::Digit) || previousToken->Type == Automat::Token::UserType || previousToken->Type == Automat::Token::IncOrDec || !strcmp(previousToken->String, ")") || !strcmp(previousToken->String, "]"))){
                currentToken->Priority = 5;
                continue;
            }
            
            if (!strcmp(tempStr, "&") && (previousToken->Type == Automat::Token::UserType))
            {
                currentToken->Priority = 9;
                continue;
            }
            
            if (!strcmp(tempStr, "==") || !strcmp(tempStr, "!="))
            {
                currentToken->Priority = 8;
                continue;
            }
            
            if (!strcmp(tempStr, "<") || !strcmp(tempStr, ">") || !strcmp(tempStr, "<=") || !strcmp(tempStr, ">="))
            {
                currentToken->Priority = 7;
                continue;
            }
            
            if ((!strcmp(tempStr, "*") || !strcmp(tempStr, "/") || !strcmp(tempStr, "%")) && ((previousToken->Type == Automat::Token::Digit) || (previousToken->Type == Automat::Token::UserType) || !strcmp(previousToken->String, "]") || !strcmp(previousToken->String, ")")))
            {
                currentToken->Priority = 4;
                continue;
            }
            
            if (((!strcmp(tempStr, "--") || !strcmp(tempStr, "++") || !strcmp(tempStr, "[") || !strcmp(tempStr, "->")) && (previousToken->Type == Automat::Token::UserType)) || !strcmp(tempStr, "]"))
                currentToken->Priority = 1;
            
            if (currentToken->Type == Automat::SysFunction)
                currentToken->Priority = 2;
            
            if (!strcmp(tempStr, "<<") || !strcmp(tempStr, ">>")){
                currentToken->Priority = 6;
                continue;
            }
            
        }
    }
}



//Поиск индекса токена token в списке Tokens с позиции startPosition по finishPosition. Если токен не найден, выбрасывается Exceptions::TokenNotFound.
int Builder::FindToken(int StartPosition, int FinishPosition, char* token){
    for (int i = StartPosition; i < FinishPosition + 1 && i < Tokens->count(); i++) {
        if (!strcmp(((NewToken*)Tokens->get(i))->String, token))
            return i;
    }
    
    throw new Exception("TokenNotFound: токен не найден.", ((NewToken*)Tokens->get(StartPosition))->LineIndex);
}


//Возвращает true, если token является операцией и false в противном случае
bool Builder::isOperator(Automat::Token token){
    
    switch (token)
    {
        case Automat::Token::ApOp:
            return true;
        case Automat::Token::Assignment:
            return true;
        case Automat::Token::BiteOp:
            return true;
        case Automat::Token::CompOper:
            return true;
        case Automat::Token::Condition:
            return true;
        case Automat::Token::IncOrDec:
            return true;
        case Automat::Token::LogicOper:
            return true;
        case Automat::Token::ReservedWord:
            return true;
        case Automat::Token::Separator:
            return true;
        case Automat::Token::Star:
            return true;
        case Automat::Token::SysFunction:
            return true;
        default:
            return false;
    }
}


//Возвращает true, если участок является выражением, содержащим арфметические, логические операции или системные функции,  и false в противном случае.
bool Builder::IsAnExpression(int StartPosition, int FinishPosition){
    int count = Tokens->count();
    for (int i = StartPosition; i < FinishPosition + 1 && i < count; i++) {
        NewToken* token = (NewToken*)Tokens->get(i);
        
        if (token->Type == Automat::Bracket && !strcmp(token->String, "["))
            i = ClosingBracketIndex(i);
        
        if (token->Type == Automat::ApOp || token->Type == Automat::CompOper || token->Type == Automat::IncOrDec || token->Type == Automat::SysFunction || token->Type == Automat::Assignment)
            return true;
    }
    
    return false;
}


//Конвертация токенов в новый формат NewToken с приоритетами с получением значения Value для чисел
List* Builder::ConvertToNewToken(List* OldToken){
    List* ListFoNewToken = new List(sizeof(NewToken));
    int CountLines = 1;
    int OldTokenCount = OldToken->count();
    
    for (int i = 0; i < OldTokenCount; i++) {
        Automat::ResultOfParsing* TempTokenInOldFormat = (Automat::ResultOfParsing*)OldToken->get(i);
        
        if (TempTokenInOldFormat->token == Automat::Token::Space ||
            TempTokenInOldFormat->token == Automat::Token::NewLine ||
            TempTokenInOldFormat->token == Automat::Token::SingleLineComment ||
            TempTokenInOldFormat->token == Automat::Token::MultilineComment){
            
            if (TempTokenInOldFormat->token == Automat::NewLine)
                CountLines++;
            
            continue;
        }
        
        
        if (TempTokenInOldFormat->token == Automat::ReservedWord){
            if (strcmp(TempTokenInOldFormat->Str, "true") == 0){
                TempTokenInOldFormat->token = Automat::Digit;
                TempTokenInOldFormat->Str = "1";
            }
            if (strcmp(TempTokenInOldFormat->Str, "false") == 0){
                TempTokenInOldFormat->token = Automat::Digit;
                TempTokenInOldFormat->Str = "0";
            }
        }
        
        double value = 0;
        
        if (TempTokenInOldFormat->token == Automat::Token::Digit){
            value = StringToDouble(TempTokenInOldFormat->Str);
        }
        
        //Для системных функций, возвращающих значение (всех, кроме input и output),  значение value = 1.
        if (TempTokenInOldFormat->token == Automat::Token::SysFunction){
            
            if (strcmp(TempTokenInOldFormat->Str, "print") && strcmp(TempTokenInOldFormat->Str, "input")){
                value = 1;
            }
        }
        
        NewToken* newToken = new NewToken(TempTokenInOldFormat->token, TempTokenInOldFormat->Str, value, 0, CountLines);
        ListFoNewToken->add(newToken);
    }
    
    return ListFoNewToken;
}




//Для парсинга единственной строки (TNode*)
TNode* Builder::ParseLine(int StartPosition, int FinishPosition){
    NewToken* Token = (NewToken*)Tokens->get(StartPosition);
    
    //Убираем окаймляющие скобки
    while (Token->Type == Automat::Token::Bracket && ClosingBracketIndex(StartPosition) == FinishPosition){
        
        StartPosition++;
        FinishPosition--;
        
        Token = (NewToken*)Tokens->get(StartPosition);
    }
    
    //Единственный токен в строке
    if (StartPosition == FinishPosition){
        return ParseSingleTokenLine(StartPosition);
    }
    
    //Line не является выражением, содержащим арифметические, логические операции, операции присваивания или системные функции.
    
    if (!IsAnExpression(StartPosition, FinishPosition)){
        TNodeType type;
        return ParseVariableName(StartPosition, type);
    }
    
    int PositionTokenWithMinPriority = FindOperationWithMinimalPriority(StartPosition, FinishPosition);
    NewToken* WorkElement = (NewToken*)Tokens->get(PositionTokenWithMinPriority);
    
    //Арифметические операции
    if (WorkElement->Type == Automat::ApOp){
        
        if (WorkElement->Priority == 2)
            return new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(WorkElement->String), ParseLine(PositionTokenWithMinPriority + 1, FinishPosition));
        
        return new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex(WorkElement->String), ParseLine(StartPosition, PositionTokenWithMinPriority - 1), ParseLine(PositionTokenWithMinPriority + 1, FinishPosition));
    }
    
    
    //Инкремент и декремент
    if (WorkElement->Type == Automat::IncOrDec){
        if (!strcmp(WorkElement->String, "++")){
            if (((NewToken*)Tokens->get(PositionTokenWithMinPriority + 1))->Type == Automat::UserType)
                return new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex("++î"), ParseLine(PositionTokenWithMinPriority + 1, FinishPosition));
            
            return new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex("î++"), ParseLine(StartPosition, PositionTokenWithMinPriority - 1));
        }
        
        if (!strcmp(WorkElement->String, "--")){
            if (((NewToken*)Tokens->get(PositionTokenWithMinPriority + 1))->Type == Automat::UserType){
                return new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex("--î"), ParseLine(PositionTokenWithMinPriority + 1, FinishPosition));
            }
            
            return new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex("î--"), ParseLine(StartPosition, PositionTokenWithMinPriority - 1));
        }
        
        throw new Exception("UnknownOperation: неподдерживаемая операция.", ((NewToken*)Tokens->get(StartPosition))->LineIndex);
    }
    
    //Операторы сравнения
    if (WorkElement->Type == Automat::CompOper)
    {
        return new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex(WorkElement->String), ParseLine(StartPosition, PositionTokenWithMinPriority - 1), ParseLine(PositionTokenWithMinPriority + 1, FinishPosition));
    }
    
    
    //Системные функции, возвращающие значение
    if (WorkElement->Type == Automat::SysFunction && WorkElement->Value){
        PositionTokenWithMinPriority++;
        NewToken* OpenBracket = (NewToken*)Tokens->get(PositionTokenWithMinPriority);
        
        if (OpenBracket->Type != Automat::Bracket)
            throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(PositionTokenWithMinPriority))->LineIndex);
        
        int CloseBracket = ClosingBracketIndex(PositionTokenWithMinPriority);
        
        if (CloseBracket - PositionTokenWithMinPriority == 1)
            throw new Exception("MissingArguments: пропущены аргументы при вызове функции", ((NewToken*)Tokens->get(PositionTokenWithMinPriority))->LineIndex);
        
        if (UnaryOperationList::Instance().IsUnaryOperation(WorkElement->String)){
            TNode* argument = ParseLine(PositionTokenWithMinPriority, CloseBracket);
            UnaryOperationNode* unaryOperation = new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(WorkElement->String), argument);
            return unaryOperation;
        }
        
        
        if (BinaryOperationList::Instance().IsBinaryOperation(WorkElement->String)){
            int SeparatorIndex = -1;
            
            for (int i = PositionTokenWithMinPriority; i < CloseBracket; i++){
                NewToken* Separator = (NewToken*)Tokens->get(i);
                
                if (Separator->Type == Automat::Separator && strcmp(Separator->String, ",") == 0){
                    SeparatorIndex = i;
                    break;
                }
            }
            

            if (SeparatorIndex == -1)
               throw new Exception("MissingArguments: пропущены аргументы при вызове функции",((NewToken*)Tokens->get(PositionTokenWithMinPriority))->LineIndex);
            
            
            
            TNode* FirstArgument = ParseLine(PositionTokenWithMinPriority + 1, SeparatorIndex - 1);
            TNode* SecondArgument = ParseLine(SeparatorIndex + 1, CloseBracket - 1);
            
            BinaryOperationNode* BinaryOperation = new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex(WorkElement->String), FirstArgument, SecondArgument);
            return BinaryOperation;
        }
        
        throw new Exception("SystemFunctionIsNotSupported: неподдерживаемая системная функция", ((NewToken*)Tokens->get(StartPosition))->LineIndex);
    }
    
    
    
    //Присваевание
    if (WorkElement->Type == Automat::Assignment){
        
        TNodeType ResultType;
        TNode* LeftArgument = ParseVariableName(StartPosition, ResultType);
        TNode* RightArgument = ParseLine(PositionTokenWithMinPriority + 1, FinishPosition);
        
        if (ResultType == TNodeType::Const)
            throw new Exception("ConstantReinitialization: изменение значения константы невозможно", ((NewToken*)Tokens->get(StartPosition))->LineIndex);
        
        return new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex("="), LeftArgument, RightArgument);
    }
    
    //Логические операции
    if (WorkElement->Type == Automat::LogicOper){
        
        if (strcmp(WorkElement->String, "!")){
            return new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex(WorkElement->String), ParseLine(StartPosition, PositionTokenWithMinPriority - 1), ParseLine(PositionTokenWithMinPriority + 1, FinishPosition));
        }
        else{
            PositionTokenWithMinPriority++;
            NewToken* Bracket = (NewToken*)Tokens->get(PositionTokenWithMinPriority);
            
            if (Bracket->Type != Automat::Bracket)
                throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(PositionTokenWithMinPriority))->LineIndex);
            
            int CloseBracket = ClosingBracketIndex(PositionTokenWithMinPriority);
            return new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(WorkElement->String), ParseLine(PositionTokenWithMinPriority + 1, CloseBracket - 1));
        }
    }
    
    throw new Exception("InvalidOperation: недопустимая операция", ((NewToken*)Tokens->get(StartPosition))->LineIndex);
    
}




//Если единственный токен в строке, он может быть или константой или переменной.
//Возвращает (TConst : TNode) или (TVariable : TNode), для добавления в дерево TList* root.
//Если токен не является константой или переменной, Exceptions::InvalidOperation.
//Если переменная не найдена, Exceptions::VariableNameNotFound.
TNode* Builder::ParseSingleTokenLine(int Index){
    NewToken* FirstElement = (NewToken*)Tokens->get(Index);
    
    if (FirstElement->Type == Automat::Digit || FirstElement->Type == Automat::Char) {
        if (FirstElement->Type == Automat::Digit){
            TValue* Value = new TValue(FirstElement->Value, TypeList::Instance().GetTypeIndex("double"));
            return new ConstNode(Value);
        }
        
        char Symbol = FirstElement->String[1];
        TValue* Value = new TValue(Symbol, TypeList::Instance().GetTypeIndex("char"));
        return new ConstNode(Value);
    }
    
    if (FirstElement->Type == Automat::UserType){
        TValueKeeper* Var = CurrentScope->Find(FirstElement->String);
        
        if (Var == NULL)
            throw new Exception("VariableNameNotFound: необъявленная переменная или константа", ((NewToken*)Tokens->get(Index))->LineIndex);
        
        if (Var->IsReference())
            throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(Index))->LineIndex);
        
        if (Var->IsConst()){
            return new ConstNode(Var->GetValue());
        }
        else{
            return new VariableNode(Var->GetValue());
        }
    }
    
    throw new Exception("InvalidCharacter: недопустимый символ", ((NewToken*)Tokens->get(Index))->LineIndex);
}



//Объявление и инициализация константы const.
//Значение константы должно быть явно указано и известно при компиляции: ect.: const int a = 5;
// index	index + 1	index + 2	index + 3	index + 4	index + 5 = semicolon
// const	type		name		=			value		;

// index	index + 1	index + 2	index + 3	index + 4	index + 5	index + 6 = semicolon
// const	type		name		=			- (+)		value		;
void Builder::ParseConstInitialization(int& Index){
    int Semicolon = FindToken(Index, Tokens->count(), ";");
    int LenghtExpression = Semicolon - Index;
    
    if (LenghtExpression != 5 && LenghtExpression != 6)
        throw new Exception("ConstInitializationError: ошибка инициализации константы.", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    Index++;
    NewToken* Type = (NewToken*)Tokens->get(Index);
    
    if (!TypeList::Instance().IsType(Type->String))
        throw new Exception("UnknownType: неподдерживаемый тип данных", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    Index++;
    NewToken* Name = (NewToken*)Tokens->get(Index);
    
    if (Name->Type != Automat::UserType)
        throw new Exception("ConstInitializationError: ошибка инициализации константы", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    if (CurrentScope->FindInThisScope(Name->String) != NULL)
        throw new Exception("RedefinitionVariable: недопустимое переопределение переменной", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    Index++;
    NewToken* Assignment = (NewToken*)Tokens->get(Index);
    
    if (Assignment->Type != Automat::Assignment)
        throw new Exception("UninitializedConstant: неинициализированная константа", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    int sign = 1;
    
    if (LenghtExpression == 6){
        Index++;
        NewToken* SignToken = (NewToken*)Tokens->get(Index);
        
        if (strcmp(SignToken->String, "-") == 0)
            sign = -1;
        else
            if (strcmp(SignToken->String, "+") == 0)
            sign = 1;
        else
            throw new Exception("ConstInitializationError: ошибка инициализации константы", ((NewToken*)Tokens->get(Index))->LineIndex);
    }
    
    Index++;
    NewToken* Value = (NewToken*)Tokens->get(Index);
    
    if (Value->Type == Automat::Digit){
        CurrentScope->Put(new TValueKeeper(Name->String, new TValue(sign * (Value->Value), TypeList::Instance().GetTypeIndex(Type->String), 0), true));
        return;
    }
    
    throw new Exception("ConstInitializationError: ошибка инициализации константы", ((NewToken*)Tokens->get(Index))->LineIndex);
}

// Объявление (и инициализация) переменной или объявление статического массива.
// Не инициализированным пользователю переменным и элементам массивов присваивается значение 0.
// Если переменная инициализируется значением явно, соответствующая BinaryOperationNode* для операции =  добавляется в CurrentList для последующего вычисления.

// 1. Переменная
// index	index + 1	index + 2 = semicolon
// type		name		;

// 2. Переменная с присваиванием значения
// index	index + 1	index + 2	index + 3	index + 4
// type		name		=			value		;

// 3. Массив
// index	index + 1	index + 2	index + 3	index + 4	index + 5
// type		name		[			size		]			;
void Builder::ParseInitialization(int& Index){
    int Semicolon = FindToken(Index, Tokens->count(), ";");
    
    if (Semicolon - Index < 2)
        throw new Exception("VariableNameIsNotSpecified: не указано имя переменной", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    NewToken* Type = (NewToken*)Tokens->get(Index);
    
    if (!TypeList::Instance().IsType(Type->String))
        throw new Exception("UnknownType: неподдерживаемый тип данных", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    Index++;
    NewToken* Name = (NewToken*)Tokens->get(Index);
    if (Name->Type != Automat::UserType)
        throw new Exception("ConstInitializationError: недопустимое имя переменной", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    if (CurrentScope->FindInThisScope(Name->String) != NULL)
        throw new Exception("RedefinitionVariable: недопустимое переопределение переменной", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    if (Semicolon - Index == 1){
        // 1. Переменная без присваивания: добавляем в хеш со значением по умолчанию 0
        CurrentScope->Put(new TValueKeeper(Name->String, new TValue(0, TypeList::Instance().GetTypeIndex(Type->String), 0)));
        return;
    }
    Index++;
    NewToken* BracketOrAssignment = (NewToken*)Tokens->get(Index);
    
    // 2. Переменная с присваиванием
    if (BracketOrAssignment->Type == Automat::Assignment){
        TValue* tValue = new TValue(0, TypeList::Instance().GetTypeIndex(Type->String), 0);
        
        //Добавляем переменную в хеш со значением по умолчанию 0
        CurrentScope->Put(new TValueKeeper(Name->String, tValue));
        
        // Символьный тип данных
        if (!strcmp(Type->String, "char")){
            Index++;
            char Symbol = ((NewToken*)Tokens->get(Index))->String[1];
            
            CurrentList->Push(new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex("="), new VariableNode(CurrentScope->FindInThisScope(Name->String)->GetValue()), new ConstNode(new TValue(Symbol, TypeList::Instance().GetTypeIndex("char")))));
            return;
        }
        
        Index++;
        TNode* value = ParseLine(Index, Semicolon - 1);
        
        CurrentList->Push(new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex("="), new VariableNode(CurrentScope->FindInThisScope(Name->String)->GetValue()), value));
        return;
    }
    
    
    // 3. Массив
    if (BracketOrAssignment-Type == Automat::Bracket && Semicolon - Index == 3){
        Index++;
        NewToken* Size = (NewToken*)Tokens->get(Index);
        int IntegerSize = 0;
        
        // Целое положительное числовое значение
        if (Size->Type == Automat::Digit){
            if (Size->Value <= 0 || IsFraction(Size->String))
                throw new Exception("ArraySizeIsNotAnInteger: размер массива должен быть целым положительным числом", ((NewToken*)Tokens->get(Index))->LineIndex);
            
            IntegerSize = (int)Size->Value;
        }
        else // Константа, объявленная ранее
            if (Size->Type == Automat::UserType){
                TValueKeeper* ConstSize = (CurrentScope->Find(Size->String));
                if (ConstSize == NULL){
                    throw new Exception("VariableNameNotFound: необъявленная переменная или константа", ((NewToken*)Tokens->get(Index))->LineIndex);
                }
                else{
                    if (ConstSize->IsConst()){
                        if (ConstSize->GetValue()->GetType() == TypeList::Instance().GetTypeIndex("int")){
                            IntegerSize = (int)ConstSize->GetValue()->GetValue();
                            
                            if (IntegerSize <= 0)
                                throw new Exception("ArraySizeIsNotAnInteger: размер массива должен быть целым положительным числом", ((NewToken*)Tokens->get(Index))->LineIndex);
                        }else
                            throw new Exception("ArraySizeIsNotAnInteger: размер массива должен быть целым положительным числом", ((NewToken*)Tokens->get(Index))->LineIndex);
                    }
                    throw new Exception("ArraySizeIsNotAConstant: размер массива должен быть задан константой", ((NewToken*)Tokens->get(Index))->LineIndex);
                }
            }
        // Закрывающая скобка
        Index++;
        if (Index != ClosingBracketIndex(Index - 2))
            throw new Exception("ArrayInitializationError: ошибка объявления массива", ((NewToken*)Tokens->get(Index))->LineIndex);
        
        CurrentScope->Put(new TValueKeeper(Name->String, new TValue(0, TypeList::Instance().GetTypeIndex(Type->String), IntegerSize)));
        return;
    }
    throw new Exception("InitializationError: ошибка объявления или инициализации.", ((NewToken*)Tokens->get(Index))->LineIndex);
}


// Конструкция if-else
// if (condition)
// {
//		body;
// }
// else *
// { *
//		body; *
// } *
// * - optional
TNode* Builder::ParseIfElse(int& Index){
    // 1. Условие if.
    Index++;
    NewToken* OpeningParenthesis = (NewToken*)Tokens->get(Index);
    
    if (strcmp(OpeningParenthesis->String, "("))
        throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    int ClosingParenthesis = ClosingBracketIndex(Index);
    
    TNode* Condition = ParseLine(Index, ClosingParenthesis);
    Index = ClosingParenthesis;
    
    // 2. Тело then.
    Index++;
    NewToken* OpeningBrace = (NewToken*)Tokens->get(Index);
    if (strcmp(OpeningBrace->String, "{"))
        throw new Exception("MissingBracket: пропущена скобка.", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    int ClosingBrace = ClosingBracketIndex(Index);
    
    // Создаем IndependentOperationsNode для тела then с соответствующей областью видимости Scope
    // Текущую CurrentList сохраняем в TempList
    // Меняем CurrentList и currentScope на IndependentOperationsNode и Scope тела цикла
    
    IndependentOperationsNode* ThenBranch = new IndependentOperationsNode(CurrentList);
    IndependentOperationsNode* TempList = CurrentList;
    CurrentList = ThenBranch;
    CurrentScope = ThenBranch->GetScope();
    
    // Парсим тело then.
    ParseMultiLine(Index + 1, ClosingBrace - 1);
    
    // Восстанавливаем CurrentList и область видимости CurrentScope
    CurrentList = TempList;
    CurrentScope = CurrentList->GetScope();
    
    Index = ClosingBrace;
    // 3. Тело else
    
    // Есть ли вообще код после тела then
    if (Index == Tokens->count() - 1){
        return new IfElseNode(Condition, ThenBranch, NULL);
    }
    
    int IndexBeforeElseBranch = Index;
    
    Index++;
    NewToken* ElseToken = (NewToken*)Tokens->get(Index);
    IndependentOperationsNode* ElseBranch = NULL;
    
    // Если есть else
    if (ElseToken && !strcmp(ElseToken->String, "else")){
        Index++;
        NewToken* OpeningBrace = (NewToken*)Tokens->get(Index);
        if (OpeningBrace->Type != Automat::Bracket)
            throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(Index))->LineIndex);
        
        int ClosingBrace = ClosingBracketIndex(Index);
        
        // Аналогично then.
        ElseBranch = new IndependentOperationsNode(CurrentList);
        TempList = CurrentList;
        CurrentList = ElseBranch;
        CurrentScope = ElseBranch->GetScope();
        
        ParseMultiLine(Index + 1, ClosingBrace - 1);
        
        CurrentList = TempList;
        CurrentScope = CurrentList->GetScope();
        
        Index = ClosingBrace;
    }
    
    if (ElseBranch == NULL)
        Index = IndexBeforeElseBranch;
    
    return new IfElseNode(Condition, ThenBranch, ElseBranch);
}


// while (condition)
// {
//		body;
// }
TNode* Builder::ParseWhile(int& Index){
    // 1. Условие
    Index++;
    NewToken* OpeningParenthesis = (NewToken*)Tokens->get(Index);
    
    if (strcmp(OpeningParenthesis->String, "("))
        throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    int ClosingParenthesis = ClosingBracketIndex(Index);
    
    TNode* Condition = ParseLine(Index, ClosingParenthesis);
    
    Index = ClosingParenthesis;
    
    // 2. Тело цикла.
    Index++;
    NewToken* OpeningBrace = (NewToken*)Tokens->get(Index);
    if (strcmp(OpeningBrace->String, "{"))
        throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    int ClosingBrace = ClosingBracketIndex(Index);
    
    IndependentOperationsNode* Body = new IndependentOperationsNode(CurrentList);
    IndependentOperationsNode* TempList = CurrentList;
    CurrentList = Body;
    CurrentScope = Body->GetScope();
    
    ParseMultiLine(Index + 1, ClosingBrace - 1);
    
    Index = ClosingBrace;
    
    CurrentList = TempList;
    CurrentScope = TempList->GetScope();
    
    return new WhileNode(Condition, Body);
}



// Имена переменных и обращения к элементам массивов.
TNode* Builder::ParseVariableName(int& Index, TNodeType& Type){
    // Название переменной
    NewToken* VariableName = (NewToken*)Tokens->get(Index++);
    
    TValueKeeper* Keeper = CurrentScope->Find(VariableName->String);
    
    if (Keeper == NULL)
        throw new Exception("VariableNameNotFound: необъявленная переменная или константа", ((NewToken*)Tokens->get(Index))->LineIndex);
    
    // Переменная хранит ссылку на массив значений
    // Для доступа к нужному элементу необходимо указание индекса элемента в квадратных скобках
    if (Keeper->IsReference()) {
        //  Квадратные скобки
        NewToken* Brackets = (NewToken*)Tokens->get(Index);
        if (Brackets->Type == Automat::Bracket && !strcmp(Brackets->String, "[")) {
            int CloseBracket = ClosingBracketIndex(Index);
            
            // Индекс элемента
            TNode* ElemIndex = ParseLine(Index + 1, CloseBracket - 1);
            
            Index = CloseBracket + 1;
            
            Type = TNodeType::Array;
            return new ArrayNode(Keeper->GetValue(), ElemIndex);
        }
        else{
            // Нет скобок после переменной, хранящей ссылку на массив
            throw new Exception("IndexIsNotSpecified: не указан индекс элемента массива", ((NewToken*)Tokens->get(Index))->LineIndex);
        }
    }
    else
    {
        // Константа.
        if (Keeper->IsConst())
        {
            Type = TNodeType::Const;
            return new ConstNode(Keeper->GetValue());
        }
        // Переменная.
        else
        {
            Type = TNodeType::Variable;
            return new VariableNode(Keeper->GetValue());
        }
    }
}



// Для парсинга программы и тела конструкций if и циклов
// Не возвращает значение, все TNode* цепляются к CurrentList
void Builder::ParseMultiLine(int Start, int End){
    for (int i = Start; i < End && i < Tokens->count(); i++){
        NewToken* Token = (NewToken*)Tokens->get(i);
        
        // Пропуск точки с запятой
        if (Token->Type == Automat::Separator)
            continue;
        
        // 1. Объявление константы.
        if (!strcmp(Token->String, "const")){
            // const int a = <expression>;
            ParseConstInitialization(i);
            continue;
        }
        
        // 2. Объявление переменных и массивов.
        // тип имя = <expression>;
        // тип имя[размер];
        if (Token->Type == Automat::Token::ReservedType){
            ParseInitialization(i);
            continue;
        }
        
        
        // 3. Конструкции if и while.
        if (Token->Type == Automat::Token::Condition){
            if (!strcmp(Token->String, "if")){
                CurrentList->Push(ParseIfElse(i));
                continue;
            }
            else
                if (!strcmp(Token->String, "while")){
                CurrentList->Push(ParseWhile(i));
                continue;
            }
            else
            {
                throw new Exception("InvalidOperation: недопустимая операция.", ((NewToken*)Tokens->get(i))->LineIndex);
            }
        }
        
        // 4. Системные функции c одним аргументом input и output, не возвращающие значение
        if (Token->Type == Automat::Token::SysFunction && Token->Value == 0){
            // Аргумент функции в круглых скобках.
            NewToken* Bracket = (NewToken*)Tokens->get(++i);
            if (Bracket->Type != Automat::Token::Bracket)
                throw new Exception("MissingBracket: пропущена скобка", ((NewToken*)Tokens->get(i))->LineIndex);
            
            int CloseBracketIndex = ClosingBracketIndex(i);
            
            if (CloseBracketIndex - i == 1)
                throw new Exception("MissingArguments: пропущены аргументы при вызове функции.", ((NewToken*)Tokens->get(i))->LineIndex);
            i++;
            
            NewToken* DigitOrChar = (NewToken*)Tokens->get(i);
            
            if (DigitOrChar->Type == Automat::UserType){
                TNode* Argument = ParseLine(i, CloseBracketIndex - 1);
                
                // Вывод.
                if (!strcmp(Token->String, "print")){
                    CurrentList->Push(new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(Token->String), Argument));
                }
                // Ввод.
                else{
                    CurrentList->Push(new BinaryOperationNode(BinaryOperationList::Instance().GetOperationIndex("="), Argument, new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(Token->String), Argument)));
                }
            }
            else if (DigitOrChar->Type == Automat::String){
                // Создание символьного массива
                int StringLenght = strlen(DigitOrChar->String) - 2 + 1;
                
                TValue* tValueString = new TValue(0, TypeList::Instance().GetTypeIndex("char"), StringLenght);
                
                double* DoubleString = new double[StringLenght];
                for (int i = 0, j = 1; i < StringLenght - 1; i++, j++){
                    DoubleString[i] = DigitOrChar->String[j];
                }
                DoubleString[StringLenght] = '\0';
                
                tValueString->SetPointer(DoubleString);
                
                // Имена переменных не обязаны быть уникальными, так как они тут же выводятся.
                CurrentScope->Put(new TValueKeeper("@string", tValueString));
                
                CurrentList->Push(new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(Token->String), new VariableNode(tValueString)));
            }
            else
            {
                TNode* Argument = ParseLine(i, CloseBracketIndex - 1);
                CurrentList->Push(new UnaryOperationNode(UnaryOperationList::Instance().GetOperationIndex(Token->String), Argument));
            }
            
            i = CloseBracketIndex;
            
            continue;
        }
        
        
        // 5. Обращение к переменной и массивам
        // a = <expression>;
        // a [i] = <expression>;
        int semicolon = FindToken(i, Tokens->count(), ";");
        CurrentList->Push(ParseLine(i, semicolon - 1));
        i = semicolon;
    }
}







































