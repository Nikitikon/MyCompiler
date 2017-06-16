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
    VariableTable* table;
    Scope* parentScope;
    
public:
    Scope(Scope* parentScope = NULL); // Done
    ~Scope(); // Done
    
    void Put(TValueKeeper* Keeper); // Done
    TValueKeeper* Find(char* Name); // 
    TValueKeeper* FindInThisScope(char* Name);
    Scope* GetParentScope();
};

#endif /* Scope_hpp */
