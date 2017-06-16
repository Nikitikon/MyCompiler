//
//  VariableTable.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef VariableTable_hpp
#define VariableTable_hpp

#include "TValueKeeper.hpp"
#include "hash.hpp"

class VariableTable : public Hash{
    
protected:
    unsigned int Key1(char* Key); // Done
    
public:
    
    VariableTable() : Hash(9,0,0,0,0) {} // Done
    ~VariableTable(); // Done
    
    TValueKeeper* Find(char* Name); // Done
    
    TValueKeeper* Put(TValueKeeper* Keeper); // Done
    TValueKeeper* Put(char* Name, double Value, int Type, int Size = 0); //Done
    
};
#endif /* VariableTable_hpp */
