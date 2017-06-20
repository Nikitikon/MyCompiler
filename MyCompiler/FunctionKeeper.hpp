//
//  FunctionKeeper.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef FunctionKeeper_hpp
#define FunctionKeeper_hpp

#include "FunctionData.hpp"

class FunctionKeeper {
    
private:
    char* Name;
    FunctionData* Data;
    TValue* ReturnValue;
    
    
public:
    FunctionKeeper(char* Name, FunctionData* Data); // Done
    ~FunctionKeeper(); // Done
    
    char* GetName(); // Done
    FunctionData* GetData(); // Done
    TValue* GetRetuenValue(); // Done
    
    void SetFunctionTree(IndependentOperationsNode* FunctionTree); // Done
    
};

#endif /* FunctionKeeper_hpp */
