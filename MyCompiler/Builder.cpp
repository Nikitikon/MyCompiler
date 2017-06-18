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
    
    Tokens = OldTokenToNewToken(Tokens);
    
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
int Builder::FindOperationWithMinimalPriority(int startPosition , int finishPosition){
    //16 уровней приоритета операций от 1 до 16
    int minPriority = 0;
    int resultPosition = -1;
    
    for (int i = startPosition; i < finishPosition + 1; i++) {
        NewToken* nextToken = (NewToken*)Tokens->get(i);
        
        if (isOperator(nextToken->Type)){
            if (!strcmp("[", nextToken->String) && minPriority == 0){
                int temp = ClosingBracketIndex(i);
                
                if (temp == finishPosition)
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
        throw new Exception("InvalidOperation: недопустимая операция.", ((NewToken*)Tokens->get (startPosition))->LineIndex);
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
            
            if (!currentToken->Priority)
                throw new Exception("InvalidOperation: недопустимая операция.", currentToken->LineIndex);
        }
    }
}
























