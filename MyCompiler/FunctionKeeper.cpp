//
//  FunctionKeeper.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FunctionKeeper.hpp"

FunctionKeeper::FunctionKeeper(char* Name, FunctionData* Data, int StartPosition, int FinishPosition){
    if (Name == NULL || Data == NULL)
        throw Exceptions::NullObject;
    
    this->Name = Name;
    this->Data = Data;
    this->StartPosition = StartPosition;
    this->FinishPosition = FinishPosition;
}

FunctionKeeper::~FunctionKeeper(){
    if (Name)
        delete Name;
    
    if (Data)
        delete Data;
    

    
    Name = NULL;
    Data = NULL;
}


char* FunctionKeeper::GetName(){
    return  Name;
}

FunctionData* FunctionKeeper::GetData(){
    return Data;
}


