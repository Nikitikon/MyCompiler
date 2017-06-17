//
//  UnaryOperationList.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "UnaryOperationList.hpp"

UnaryOperationList::UnaryOperationList(){
    unaryOperation = new List(MAX_OPERATION_NAME_LENGHT);
    LoadDefaultOperations();
}


UnaryOperationList::~UnaryOperationList(){
    if (unaryOperation)
        delete unaryOperation;
}

void UnaryOperationList::LoadDefaultOperations(){
    
    unaryOperation->add((void*)"+");
    unaryOperation->add((void*)"-");
    
    unaryOperation->add((void*)"!");
    
    unaryOperation->add((void*)"î++");
    unaryOperation->add((void*)"î--");
    unaryOperation->add((void*)"++î");
    unaryOperation->add((void*)"--î");
    
    unaryOperation->add((void*)"input");
    unaryOperation->add((void*)"print");
    
    unaryOperation->add((void*)"sin");
    unaryOperation->add((void*)"cos");
    unaryOperation->add((void*)"rand");
}

UnaryOperationList& UnaryOperationList::Instance(){
    static UnaryOperationList instance;
    return instance;
}

bool UnaryOperationList::IsUnaryOperation(char* Name){
    return GetOperationIndex(Name) < 0 ? false : true;
}

int UnaryOperationList::GetOperationIndex(char* Name){
    for (int i = 0; i < unaryOperation->count(); i++) {
        if (!strcmp(Name, (char*)unaryOperation->get(i)))
            return i;
    }
    
    return -1;
}

char* UnaryOperationList::GetOperationName(int Index){
    if (Index >= unaryOperation->count() || Index < 0)
        return NULL;
    
    char* CopyName = (char*)unaryOperation->get(Index);
    char* result = new char[strlen(CopyName)];
    Copy(result, CopyName, (int)strlen(CopyName));
    
    return result;
}
