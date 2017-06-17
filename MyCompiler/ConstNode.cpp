//
//  ConstNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "ConstNode.hpp"

ConstNode::ConstNode(TValue* Const){
    this->Const = Const;
}

ConstNode::~ConstNode(){
    if (Const)
        delete Const;
}

TValue* ConstNode::GetTValue(){
    return Const;
}

double ConstNode::GetValue(){
    if (!Const)
        return NULL;
    
    return Const->GetValue();
}

int ConstNode::GetType(){
    if (!Const)
        return NULL;
    
    return Const->GetType();
}

TValue* ConstNode::Execute(){
    return GetTValue();
}

