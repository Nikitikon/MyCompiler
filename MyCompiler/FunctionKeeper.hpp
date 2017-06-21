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

    
    
public:
    int StartPosition;
    int FinishPosition;
    FunctionKeeper(char* Name, FunctionData* Data, int StartPosition, int FinishPosition); // Done
    ~FunctionKeeper(); // Done
    
    char* GetName(); // Done
    FunctionData* GetData(); // Done
    

    
};

#endif /* FunctionKeeper_hpp */
