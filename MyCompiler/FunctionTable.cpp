//
//  FunctionTable.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FunctionTable.hpp"

FunctionTable::~FunctionTable(){
    Hash::~Hash();
}



unsigned int FunctionTable::Key1(char* Key){
    if (Key == NULL)
        return 0;
    
    return (int)(*Key % 10);
}


void FunctionTable::Put(FunctionKeeper* Keeper){
    if (Keeper) {
        List* putList = find_list(Keeper->GetName());
        
        if (putList == NULL) {
            putList = new List(sizeof(TValueKeeper));
            setList(Keeper->GetName(), putList);
        }
        
        putList->add(Keeper);
    }
}

FunctionKeeper* FunctionTable::Find(char* Name){
    List* listForFind = NULL;
    
    if ((listForFind = find_list(Name))){
        
        FunctionKeeper* keeper = NULL;
        for (int i = 0; i < listForFind->count(); i++) {
            keeper = (FunctionKeeper*)listForFind->get(i);
            
            if (!strcmp(Name, keeper->GetName()))
                return keeper;
        }
    }
    
    return NULL;
}






























