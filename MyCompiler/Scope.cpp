//
//  Scope.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Scope.hpp"

Scope::Scope(Scope* parentScope){
    table = new VariableTable();
    this->parentScope = parentScope;
}

Scope::~Scope(){
    if (table)
        delete table;
    
    table = NULL;
    parentScope = NULL;
}

void Scope::Put(TValueKeeper* Keeper){
    table->Put(Keeper);
}

TValueKeeper* Scope::Find(char* Name){
    
}
