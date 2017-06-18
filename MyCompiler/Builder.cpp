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
        
        
    }
    
}















