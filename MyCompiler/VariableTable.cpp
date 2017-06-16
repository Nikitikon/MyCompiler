//
//  VariableTable.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "VariableTable.hpp"

VariableTable::~VariableTable(){
    Hash::~Hash();
}


unsigned int VariableTable::Key1(char* Key)
{
    if (Key == NULL)
        return 0;
    
    return (int)(*Key % 10);
}


TValueKeeper* VariableTable::Find(char* Name){
    List* listForFind = NULL;
    
    if ((listForFind = find_list(Name))){
        
        TValueKeeper* keeper = NULL;
        for (int i = 0; i < listForFind->count(); i++) {
            keeper = (TValueKeeper*)listForFind->get(i);
            
            if (!strcmp(Name, keeper->GetName()))
                return keeper;
        }
    }
    
    return NULL;
}

TValueKeeper* VariableTable::Put(TValueKeeper *Keeper){
    
    if (Keeper) {
        List* putList = find_list(Keeper->GetName());
        
        if (putList == NULL) {
            putList = new List(sizeof(TValueKeeper));
            setList(Keeper->GetName(), putList);
        }
        
        putList->add(Keeper);
        return Find(Keeper->GetName());
    }
    
    return NULL;
}

TValueKeeper* VariableTable::Put(char* Name, double Value,int Type, int Size){
    return Put(new TValueKeeper(Name, new TValue(Value, Type, Size)));
}



























