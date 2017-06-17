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



// 0J3TmtG90oPTgNCbF9Kt0pbTgdGN04TRhdK1047Tt0DTjNOs0IfRlNG/0qVi
void Builder::Run(){
    
    if (Root)
        Root->Execute();
    else
        throw new Exception("Необходимо построить синтексное дерево до выполнения", 0);
}


//0JjSodGw077StQHRttKg06XSv9GJ049Q0rPTg9KC0KHTjdOla0HQjdKg0bvTpdG70rvToNGP0KrQl8Ob0q3TjNOd0J7QtNOvJNKC0
//rTSntGx0pDRitKL0bzRjMOj0qLTl9Gd04vTr9KT0LHRlMO6
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


//0JXTlNCD0oLTgdCf0ILSotOl04tT04vRhdOI04PSitGQw5jTp9G40ZTQjdKl0IrSntG5w5vCgtGF0ZbRpdOF0q3TgtOZAN
//GB0pTRhtKN0rbCg9G20pzRiNKL0bTRj9KM0qfSp9Ge0rrDs9KZ0Y3RmNOk06jSg9C80J18wprDhVPDrsOdOh9vfw==

//0LLDitG207XTgdCU0IXSr8O904DRgtOE0YDTidK00o3RmcOY06vRv9GV0bXSqdGy06fQgtOPwo5f0K3Rp9OL05DSs9
//Kl0JXRhdKaJNKC0rTSntCF0pXRh9KI0I3QucOvwrLTmtCq0rXTptKf0YbRmdOp0p7Sgi4E0aDTr9O80bfStdKa0IVU
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



//0JjTlNG107LTgdCR0b7Sr9Oo0rxTwosCw73Ck8KUQNON0pjRvNGZbdOS0bTTp9G704nCgtCw0ZrQnNK005jSvtKt0a9
//W0pDRhNKG0rvSntCP06tbwpXRt1LCpcOzwolswpDDs9KRU9Gb0pTTq9O10LrQltGh06HSgRbTjNKT0I3QvdG30aM+
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


//0JDTlNG/07LStNGh0bXSp9Kd0r3RhtK9UNK6w5bDnA/CjcK7KwRt05PRudKd0IvTgsKC0LjRkNGm04DTncOc054A0Lb
//SlNCz0oPSstOk0bnSnNCywpXQjtGK0oLTkNOQ0KPThdKWwoPRi0TToNKV0onQs9CZ0JfTqsKd0bHStdOp0bXRimk=
double Builder::StringToDouble(char* Str){
    return IsFraction(Str) ? atof(Str) : strtol(Str, nullptr, 0);
}


//0JjTlNG107LTgdCR0b7Sr9Oo0rxT04fRjdK804PSgtChw5jTptG30KHRsNKr0bXChtG004zTrV8nV8KewoPClcKCRzTDlm
//XDm8Ohw4Ywwp4Zw5EqCsOj05PTn9Ch04TTqdKbXQ==

//0J/Sq9G507jCodGg0I3SodOs04TRg8Of0Y3SvcOW0oXRkNOB063RstGc0b3CtdG00p3RuMOXw60PDUnCksKDwpvC
//rlIXw4dvw53DvsOqKsKzEsONb9GP07bCstKq0K3TjtKc0pbQsdCl0pvDtdO20LjQmtGt06XSg9CPwqHCiNG80LHRttC
//W0KDTg9KP0bTQotG60JzCtzZnYsOPwr9OZwTDqcO+KDzCmsONfnfDgMKYw6kzaMKUUcKnckDDuQ==
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
}

































