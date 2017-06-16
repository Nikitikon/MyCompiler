//
//  Scope.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Scope.hpp"

Scope::Scope(Scope* parentScope){
    Table = new VariableTable();
    this->parentScope = parentScope;
}

Scope::~Scope(){
    if (Table)
        delete Table;
    
    Table = NULL;
    parentScope = NULL;
}

void Scope::Put(TValueKeeper* Keeper){
    Table->Put(Keeper);
}

void Scope::Put(char* Name, double Value, int Type, int Size){
    Table->Put(Name, Value, Type, Size);
}

TValueKeeper* Scope::Find(char* Name){
    TValueKeeper* result = FindInThisScope(Name);
    
    if (result != NULL)
        return result;
    
    if (parentScope != NULL)
        return parentScope->Find(Name);
    
    return NULL;
}


TValueKeeper* Scope::FindInThisScope(char* Name){
    return Table->Find(Name);
}

Scope* Scope::GetParentScope(){
    return parentScope;
}
