//
//  VariableNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "VariableNode.hpp"

VariableNode::VariableNode(TValue* Variable){
    this->Variable = Variable;
}

VariableNode::~VariableNode(){
    if (Variable)
        delete Variable;
}

TValue* VariableNode::GetTValue(){
    return Variable;
}

double VariableNode::GetValue(){
    if (!Variable)
        return NULL;
    
    return Variable->GetValue();
}

int VariableNode::GetType(){
    if (!Variable)
        return NULL;
    
    return Variable->GetType();
}

void VariableNode::SetValue(double Value){
    if (!Variable)
        return ;
    
    Variable->SetValue(Value);
}

TValue* VariableNode::Execute(){
    return GetTValue();
}
