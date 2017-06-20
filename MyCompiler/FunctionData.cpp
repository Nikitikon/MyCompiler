//
//  FunctionData.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FunctionData.hpp"

FunctionData::FunctionData(int ReturnType, VariableTable* Argument){
    this->Argument = Argument;
    this->ReturnType = ReturnType;
    this->FunctionTree = new IndependentOperationsNode();
}


FunctionData::~FunctionData(){
    if (Argument)
        delete Argument;
    
    if (FunctionTree)
        delete FunctionTree;
    
    Argument = NULL;
    FunctionTree = NULL;
}


int FunctionData::GetReturnType(){
    return ReturnType;
}


VariableTable* FunctionData::GetArgument(){
    return Argument;
}


IndependentOperationsNode* FunctionData::GetFunctionTree(){
    return FunctionTree;
}


void FunctionData::SetFunctionTree(IndependentOperationsNode* FunctionTree){
    this->FunctionTree = FunctionTree;
}























