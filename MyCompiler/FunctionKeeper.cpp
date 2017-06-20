//
//  FunctionKeeper.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FunctionKeeper.hpp"

FunctionKeeper::FunctionKeeper(char* Name, FunctionData* Data){
    if (Name == NULL || Data == NULL)
        throw Exceptions::NullObject;
    
    this->Name = Name;
    this->Data = Data;
}

FunctionKeeper::~FunctionKeeper(){
    if (Name)
        delete Name;
    
    if (Data)
        delete Data;
    
    if (ReturnValue)
        delete ReturnValue;
    
    Name = NULL;
    Data = NULL;
    ReturnValue = NULL;
}


char* FunctionKeeper::GetName(){
    return  Name;
}

FunctionData* FunctionKeeper::GetData(){
    return Data;
}


TValue* FunctionKeeper::GetRetuenValue(){
    return ReturnValue;
}


void FunctionKeeper::SetFunctionTree(IndependentOperationsNode* FunctionTree){
    
    if (FunctionTree == NULL)
        throw Exceptions::NullObject;
    
    Data->SetFunctionTree(FunctionTree);
}

