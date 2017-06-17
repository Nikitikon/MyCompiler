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
    
    static bool IsFraction(char* Str);
    static double StringToDouble(char* Str);
    
    int ClosingBracketIndex(int openingBracketIndex);
    int FindOperationWithMinimalPriority(int start, int finish);
    void Prioritize(List*);
    int FindToken(int, int, char*);
    bool isOperator(Automat::Token);
    bool IsAnExpression(int start, int end);
    List* OldTokenToNewToken(List*);
    TNode* ParseLine(int, int);
    
    TNode* ParseSingleTokenLine(int index);
    void ParseConstInitialization(int& index);
    void ParseInitialization(int& index);
    TNode* ParseIfElse(int& index);
    TNode* ParseWhile(int& index);
    TNode* ParseVariableName(int& index, TNodeType& type);
    void ParseMultiLine(int, int);
    
public:
    Builder(char* sourceCode);
    ~Builder();
    
    void Build();
    void Run();
    void PrintList(List*);
};

#endif /* Builder_hpp */
