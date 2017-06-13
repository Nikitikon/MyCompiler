//
//  Automat.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 13.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Automat.hpp"


Automat::Automat(char* FileName){
    parser = new Parser(FileName);
}

Automat::~Automat(){
    if (parser)
        delete parser;
}

Automat::Token Automat::StringToToken(char* Str)// возвращает тип токена по поступившему стартовому значению
{
    if (!strcmp(Str, "SLZSymbolComment"))
        return Token::SingleLineComment;
    
    if (!strcmp(Str, "MLZSymbolComment"))
        return Token::MultilineComment;
    
    if (!strcmp(Str, "zeroSymbolString"))
        return Token::String;
    
    if (!strcmp(Str, "isreservedWord"))
        return Token::ReservedWord;
    
    if (!strcmp(Str, "zeroSymbolDigit"))
        return Token::Digit;
    
    if (!strcmp(Str, "zeroSymbolChar"))
        return Token::Char;
    
    if (!strcmp(Str, "isbracket"))
        return Token::Bracket;
    
    if (!strcmp(Str, "isStar"))
        return Token::Star;
    
    if (!strcmp(Str, "isCompOper"))
        return Token::CompOper;
    
    if (!strcmp(Str, "isLogicOper"))
        return Token::LogicOper;
    
    if (!strcmp(Str, "isBiteOp"))
        return Token::BiteOp;
    
    if (!strcmp(Str, "isAssignment"))
        return Token::Assignment;
    
    if (!strcmp(Str, "isSeparator"))
        return Token::Separator;
    
    if (!strcmp(Str, "isUserType"))
        return Token::UserType;
    
    if (!strcmp(Str, "isSpace"))
        return Token::Space;
    
    if (!strcmp(Str, "isNewLine"))
        return Token::NewLine;
    
    if (!strcmp(Str, "isReservedType"))
        return Token::ReservedType;
    
    if (!strcmp(Str, "isCondition"))
        return Token::Condition;
    
    if (!strcmp(Str, "isSysFunc"))
        return Token::SysFunction;
    
    if (!strcmp(Str, "isArOp"))
        return Token::ApOp;
    
    if (!strcmp(Str, "isIncOrDec"))
        return Token::IncOrDec;
    
    return Token::Non;
}



bool Automat::IsLetter(char simbol)
{
    if ((simbol >= (char)'a') && (simbol <= (char)'z'))
        return true;
    
    if ((simbol >= (char)'A') && (simbol <= (char)'Z'))
        return true;
    
    return false;
}




char* Automat::CharToString(char simbol)
{
    char* Str = new char[2];
    memset(Str, '\0', 2);
    Str[0] = simbol;

    return Str;
}



int Automat::ComposeWord(char* Str, char* startCondition, char* endCondition){
   
    //Подсчитывает количество букв в слове в начале строки
    int count = 0;
    for (int i = 0; i < strlen(Str) && IsLetter(Str[i]); i++)
        count++;
    // Если строка начинается не с слова, то возвращает 0
    if (!count)
        return count;
    
    char* word = new char[count];
    Copy(word, Str, count);
    //Проверяем удовлетворяет ли слово какой-либо инструкции
    char* CurrentCondition = parser->Find(startCondition, word);
    
    if (!strcmp(CurrentCondition, endCondition)) {
        return count;
    }
    
    return 0;
}



Automat::ResultOfParsing* Automat::ParseString(char* Str){ // Парсим строку на токены
    //За одно выполнение методы мы выделяем только 1 токен из строки
    parser->RestartConditionIndex();
    char* StartCondition = parser->GetStartCondition();
    //Перебироем все инструкции пока не найдем нужную
    while (StartCondition) {
        //Рассметриваем отдельно зарезервированные слова
        if (!strcmp(StartCondition, "isReservedWord")) {
            
            int lenght = ComposeWord(Str, StartCondition, "reservedWord");
            if (lenght == 0)
            {
                StartCondition = parser->GetStartCondition();
                continue;
            }
            
            char* word = new char[lenght];
            Copy(word, Str, lenght);
            return new ResultOfParsing(Token::ReservedWord, word);
        }
        //Рассматриваем отдельно системные функции
        if (!strcmp(StartCondition, "isSysFunc")){
            
            int lenght = ComposeWord(Str, StartCondition, "sysFunc");
            if (lenght == 0)
            {
                StartCondition = parser->GetStartCondition();
                continue;
            }
            
            char* word = new char[lenght];
            Copy(word, Str, lenght);
            return new ResultOfParsing(Token::SysFunction, word);
        }
        //Рассматриваем отдельно зарезервированные типы данных
        if (!strcmp(StartCondition, "isReservedType")){
            
            int lenght = ComposeWord(Str, StartCondition, "reservedType");
            if (lenght == 0)
            {
                StartCondition = parser->GetStartCondition();
                continue;
            }
            
            char* word = new char[lenght];
            Copy(word, Str, lenght);
            return new ResultOfParsing(Token::ReservedType, word);
        }
        //Рассматриваем отдельно состояния
        if (!strcmp(StartCondition, "isCondition")){
            
            int lenght = ComposeWord(Str, StartCondition, "condition");
            if (lenght == 0)
            {
                StartCondition = parser->GetStartCondition();
                continue;
            }
            
            char* word = new char[lenght];
            Copy(word, Str, lenght);
            return new ResultOfParsing(Token::Condition, word);
            
        }
        
        int fragmentLenght = 0;
        char* currentCondition = StartCondition;
        //все остальное, рассматривается посимвально
        for (int i = 0; i < strlen(Str); i++) {
            char* tempStr = CharToString(Str[i]);
            currentCondition = parser->Find(currentCondition, tempStr);
            
            if (currentCondition == NULL)
                throw Exceptions::InvalidCharacter;
            //Если инструкция подошла частично
            if (!strcmp(currentCondition, "error0"))
                break;
            //если символ подошел данной инструкции
            if (strcmp(currentCondition, "error") != 0)
                fragmentLenght++;
            
            if (!strcmp(currentCondition, "charError"))
                throw Exceptions::CharError;
            
            if (!strcmp(currentCondition, "stringError"))
                throw Exceptions::StringError;
            //Проверяем на конец строки и первый символ не подходящий под данную инструкцию
            if (!strcmp(currentCondition, "error") || i == strlen(Str) - 1) {
                if (fragmentLenght == 0)//Если первый символ не подошел инструкции то переходим к другой
                    break;
                //Если подошел набор подряд идущих символов, то возвращаем новый токен
                char* word = new char[fragmentLenght];
                Copy(word, Str, fragmentLenght);
                return new ResultOfParsing(StringToToken(StartCondition), word);
            }
        }
        
        StartCondition = parser->GetStartCondition();
    }
    
    return NULL;
}



List* Automat::Work(char* Str){//выполняет работу
    ResultOfParsing* result = NULL;
    
    List* tokens = new List(sizeof(ResultOfParsing));
    
    char* workStr = new char[strlen(Str)];
    Copy(workStr, Str, strlen(Str));
    
    while (strlen(workStr))
    {
        result = ParseString(workStr);
        
        if (result == NULL)
            throw Exceptions::TokenNotFound;
        
        tokens->add(result);
        
        char* temp = new char[strlen(workStr) - strlen(result->Str) + 1];
        Copy(temp, workStr + strlen(result->Str), strlen(workStr) - strlen(result->Str));
        delete[] workStr;
        workStr = temp;
    }
    
    return tokens;
}




















