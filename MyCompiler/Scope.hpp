//
//  Scope.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef Scope_hpp
#define Scope_hpp

#include "VariableTable.hpp"

class Scope{
    
private:
    VariableTable* Table;
    Scope* parentScope;
    
public:
    Scope(Scope* parentScope = NULL); // Done
    ~Scope(); // Done
    
    void Put(TValueKeeper* Keeper); // Done
    void Put(char* Name, double Value, int Type, int Size = 0); // Done
    TValueKeeper* Find(char* Name); // Done
    TValueKeeper* FindInThisScope(char* Name); // Done
    Scope* GetParentScope(); // Done
};

#endif /* Scope_hpp */
