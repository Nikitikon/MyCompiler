//
//  IfElseNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "IfElseNode.hpp"

IfElseNode::IfElseNode(TNode* Condition, IndependentOperationsNode* Then,IndependentOperationsNode* Else){
    this->Condition = Condition;
    this->Then = Then;
    this->Else = Else;
}

IfElseNode::~IfElseNode(){
    if (Condition)
        delete Condition;
    
    if (Then)
        delete Then;
    
    if (Else)
        delete Else;
}

TValue* IfElseNode::Execute(){
    
    if (Condition->Execute()->GetValue())
        return Then->Execute();
    else
        if (Else)
        return Else->Execute();
    return NULL;
}
