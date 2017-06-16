//
//  TValueKeeper.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 15.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "TValueKeeper.hpp"

TValueKeeper::TValueKeeper(char* Name, TValue* Value, bool Const){
    
    if (Value == NULL || Name == NULL)
        throw Exceptions::NullObject;
    
    this->Name = Name;
    this->Value = Value;
    this->Const = Const;
}

TValueKeeper::~TValueKeeper(){
    if (Name)
        delete[] Name;
    
    if (Value)
        delete [] Value;
    
    Name = NULL;
    Value = NULL;
    Const = false;
}


char* TValueKeeper::GetName(){
    return Name;
}

TValue* TValueKeeper::GetValue(){
    
    return Value;
}

void TValueKeeper::SetValue(TValue* Value){
    if (Const)
        throw Exceptions::ConstInitializationError;
    
    if (Value == NULL)
        throw Exceptions::NullObject;
    
    this->Value = Value;
}

bool TValueKeeper::IsConst(){
    return Const;
}

bool TValueKeeper::IsReference(){
    if (Value == NULL)
        throw Exceptions::NullObject;
    
    return Value->IsReference();
}

































