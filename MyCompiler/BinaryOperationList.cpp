//
//  BinaryOperationList.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "BinaryOperationList.hpp"

BinaryOperationList::BinaryOperationList(){
    binaryOperation = new List(MAX_OPERATION_NAME_LENGHT);
    LoadDefaultOperations();
}


BinaryOperationList::~BinaryOperationList(){
    if (binaryOperation)
        delete binaryOperation;
}

void BinaryOperationList::LoadDefaultOperations(){

    binaryOperation->add((void*)"=");
    
    binaryOperation->add((void*)"+");
    binaryOperation->add((void*)"-");
    binaryOperation->add((void*)"*");
    binaryOperation->add((void*)"/");
    binaryOperation->add((void*)"%");
    
    binaryOperation->add((void*)"&&");
    binaryOperation->add((void*)"||");
    
    binaryOperation->add((void*)"==");
    binaryOperation->add((void*)"!=");
    binaryOperation->add((void*)">");
    binaryOperation->add((void*)"<");
    binaryOperation->add((void*)">=");
    binaryOperation->add((void*)"<=");
    
    binaryOperation->add((void*)"&");
    binaryOperation->add((void*)"|");
    binaryOperation->add((void*)"<<");
    binaryOperation->add((void*)">>");
    
    binaryOperation->add((void*)"[]");
    
    binaryOperation->add((void*)"min");
    binaryOperation->add((void*)"max");
}

BinaryOperationList& BinaryOperationList::Instance(){
    static BinaryOperationList instance;
    return instance;
}

bool BinaryOperationList::IsBinaryOperation(char* Name){
    return GetOperationIndex(Name) < 0 ? false : true;
}

int BinaryOperationList::GetOperationIndex(char* Name){
    for (int i = 0; i < binaryOperation->count(); i++) {
        if (!strcmp(Name, (char*)binaryOperation->get(i)))
            return i;
    }
    
    return -1;
}

char* BinaryOperationList::GetOperationName(int Index){
    if (Index >= binaryOperation->count() || Index < 0)
        return NULL;
    
    char* CopyName = (char*)binaryOperation->get(Index);
    char* result = new char[strlen(CopyName)];
    Copy(result, CopyName, (int)strlen(CopyName));
    
    return result;
}










































