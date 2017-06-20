//
//  FunctionTable.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef FunctionTable_hpp
#define FunctionTable_hpp

#include "Scope.hpp"
#include "hash.hpp"
#include "TNode.hpp"
#include "FunctionKeeper.hpp"

class FunctionTable : public Hash{
    
protected:
    unsigned int Key1(char* Key);
    
public:
    
    FunctionTable() : Hash(9,0,0,0,0) {};
    ~FunctionTable();
    
    FunctionKeeper* Find(char* Name); // Done
    
    void Put(FunctionKeeper* Keeper); // Done
};


#endif /* FunctionTable_hpp */
