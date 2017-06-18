//
//  Builder.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef Builder_hpp
#define Builder_hpp

#include "Automat.hpp"
#include "TNode.hpp"
#include "Exceptions.h"
#include "TNode.hpp"
#include "hash.hpp"
#include "UnaryOperationNode.hpp"
#include "BinaryOperationNode.hpp"
#include "Scope.hpp"
#include "ConstNode.hpp"
#include "VariableNode.hpp"
#include "ArrayNode.hpp"
#include "ArrayNode.hpp"
#include "IndependentOperationsNode.hpp"
#include "IfElseNode.hpp"
#include "WhileNode.hpp"
#include "Exception.hpp"

enum TNodeType
{
    Const,
    Variable,
    Array
};


class Builder{
    
private:
    
    struct NewToken{
        Automat::Token Type;
        char* String;
        double Value;
        int Priority;
        int LineIndex;
        
        NewToken(Automat::Token Type, char* String, double Value, int Prioritet, int LineIndex){
            this->Type = Type;
            this->String = String;
            this->LineIndex = LineIndex;
            this->Priority = Priority;
            this->Value = Value;
        }
    };
    
    IndependentOperationsNode* Root;
    List* Tokens;
    
    Scope* CurrentScope;
    IndependentOperationsNode* CurrentList;
    
     bool IsFraction(char* Str); // Done
     double StringToDouble(char* Str); // Done
    
    int ClosingBracketIndex(int OpeningBracketIndex); // Done
    int FindOperationWithMinimalPriority(int startPosition , int finishPosition); // Done
    void Prioritize(List* TokenList); // Done
    int FindToken(int startPosition, int finishPosition, char* token); // Done
    bool isOperator(Automat::Token token); // Done
    bool IsAnExpression(int startPosition, int finishPosition); // Done
    List* OldTokenToNewToken(List* OldToken); //
    TNode* ParseLine(int, int);
    
    TNode* ParseSingleTokenLine(int index);
    void ParseConstInitialization(int& index);
    void ParseInitialization(int& index);
    TNode* ParseIfElse(int& index);
    TNode* ParseWhile(int& index);
    TNode* ParseVariableName(int& index, TNodeType& type);
    void ParseMultiLine(int, int);
    
public:
    Builder(char* sourceCode); // Done
    ~Builder(); // Done
    
    void Build(); // Done
    void Run(); // Done
    void PrintList(List*); // Done
};

#endif /* Builder_hpp */
