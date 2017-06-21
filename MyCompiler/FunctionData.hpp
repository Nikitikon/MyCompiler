//
//  FunctionData.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef FunctionData_hpp
#define FunctionData_hpp

#include "Scope.hpp"
#include "IndependentOperationsNode.hpp"

class FunctionData{
    
private:
    int ReturnType;
    
public:
    List* ArgumentNameList;
    List* ArgumentTypeList;
    
    FunctionData(int ReturnType, List* ArgumentNameList, List* ArgumentTypeList); // Done
    ~FunctionData(); // Done
    int GetReturnType();
};

#endif /* FunctionData_hpp */
