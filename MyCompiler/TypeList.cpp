//
//  TypeList.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 14.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "TypeList.hpp"

TypeList::TypeList(){
    Types = new List(MAX_TYPE_NAME_LENGHT);
    AddPrimitiveTypes();
}

TypeList::~TypeList(){
    delete Types;
}

void TypeList::AddPrimitiveTypes(){
    Types->add((void*)"int");
    Types->add((void*)"double");
    Types->add((void*)"bool");
    Types->add((void*)"float");
    Types->add((void*)"char");
    Types->add((void*)"void");

}


TypeList& TypeList::Instance(){
    static TypeList instance;
    return instance;
}


void TypeList::AddUserType(char* Name){
    if (Name == NULL)
        return;
    
    if (IsType(Name))
        return;
    
    if (strlen(Name) > MAX_TYPE_NAME_LENGHT)
        throw Exceptions::TypeNameLengthError;
    
    Types->add(Name);
}


bool TypeList::IsType(char* Name){
    return GetTypeIndex(Name) < 0 ? false : true;
}

int TypeList::GetTypeIndex(char* Name){
    for (int i = 0; i < Types->count(); i++) {
        if (!strcmp(Name, (char*)Types->get(i)))
            return i;
    }
    
    return  -1;
}

char* TypeList::GetTypeName(int Index){
    if (Index < 0 || Index >= Types->count())
        return NULL;
    
    char* type = (char*)Types->get(Index);
    char* CopyType = new char[strlen(type)];
    Copy(CopyType, type, strlen(type));
    
    return CopyType;
}









































