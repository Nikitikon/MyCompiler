//
//  OperationList.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 14.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "OperationList.hpp"

OperationList::OperationList(){
    operations = new List(MAX_OPERATION_NAME_LENGHT);
    LoadDefaultOperations();
}

OperationList::~OperationList(){
    delete operations;
}

void OperationList::LoadDefaultOperations()
{
    operations->add((void*)"=");
    operations->add((void*)"+");
    operations->add((void*)"-");
    operations->add((void*)"*");
    operations->add((void*)"/");
    operations->add((void*)"%");
    operations->add((void*)"î++");
    operations->add((void*)"î--");
    operations->add((void*)"++î");
    operations->add((void*)"--î");
    
    operations->add((void*)"==");
    operations->add((void*)"!=");
    operations->add((void*)">");
    operations->add((void*)"<");
    operations->add((void*)">=");
    operations->add((void*)"<=");
    
    operations->add((void*)"!");
    operations->add((void*)"&&");
    operations->add((void*)"||");
    
    operations->add((void*)"~");
    operations->add((void*)"&");
    operations->add((void*)"|");
    operations->add((void*)"^");
    operations->add((void*)"<<");
    operations->add((void*)">>");
    
    operations->add((void*)"+=");
    operations->add((void*)"-=");
    operations->add((void*)"*=");
    operations->add((void*)"/=");
    operations->add((void*)"%=");
    operations->add((void*)"&=");
    operations->add((void*)"|=");
    operations->add((void*)"^=");
    operations->add((void*)"<<=");
    operations->add((void*)">>=");
    
    operations->add((void*)"[]");
    operations->add((void*)"&");
    operations->add((void*)"->");
    operations->add((void*)".");
    operations->add((void*)"->*");
    operations->add((void*)".*");
    
    operations->add((void*)"()");
    operations->add((void*)",");
    operations->add((void*)";"); //
    operations->add((void*)"?:");
    operations->add((void*)"::");
    operations->add((void*)"sizeof");
    operations->add((void*)"alignof");
    operations->add((void*)"typeid");
    operations->add((void*)"new");
    operations->add((void*)"delete");
    
    operations->add((void*)"input");
    operations->add((void*)"print");
    
    operations->add((void*)"sin");
    operations->add((void*)"cos");
    operations->add((void*)"min");
    operations->add((void*)"max");
    operations->add((void*)"rand");
}

OperationList& OperationList::Instance(){
    static OperationList instance;
    return instance;
}

bool OperationList::IsOperation(char* Name){
    return GetOperationIndex(Name) < 0 ? false : true;
}

int OperationList::GetOperationIndex(char* Name){
    for (int i = 0; i < operations->count(); i++) {
        if (!strcmp(Name, (char*)operations->get(i)))
            return i;
    }
    
    return -1;
}

char* OperationList::GetOperationName(int Index){
    if (Index >= operations->count() || Index < 0)
        return NULL;
 
    char* CopyName = (char*)operations->get(Index);
    char* result = new char[strlen(CopyName)];
    Copy(result, CopyName, (int)strlen(CopyName));
    
    return result;
}

























