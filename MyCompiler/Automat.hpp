//
//  Automat.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 13.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef Automat_hpp
#define Automat_hpp

#include "Parser.hpp"

class Automat{
    
public:
    enum Token{
        SingleLineComment, //0
        MultilineComment, //1
        String, //2
        Char, //3
        ReservedType, //4
        Condition, //5
        ReservedWord, //6
        SysFunction, //7
        Digit, //8
        Bracket, //9
        IncOrDec, //10
        CompOper, //11
        ApOp, //12
        Star, //13
        LogicOper, //14
        BiteOp, //15
        Assignment, //16
        Separator, //17
        UserType,//18
        Space,//19
        NewLine,//20
        Non//21
    };
    
    struct ResultOfParsing{
        Token token;
        char* Str;
        
        ResultOfParsing(Token token, char* Str){
            this->token = token;
            this->Str = Str;
        }
    };
    
    Automat(char * FileName); //done
    ~Automat(); //done
    List* Work(char* Str);//done
    
private:
    Parser* parser;
    
    Token StringToToken(char* Str); //done
    bool IsLetter(char simbol); //done
    char* CharToString(char simbol); //done
    int ComposeWord(char* Str, char* startCondition, char* endCondition); //done
    ResultOfParsing* ParseString(char* Str); //done
};

#endif /* Automat_hpp */






















