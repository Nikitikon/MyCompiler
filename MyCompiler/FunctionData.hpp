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
    VariableTable* Argument;
    IndependentOperationsNode* FunctionTree;
    
public:
    FunctionData(int ReturnType, VariableTable* Argument); // Done
    ~FunctionData(); // Done
    
    int GetReturnType(); // Done
    VariableTable* GetArgument(); // Done
    IndependentOperationsNode* GetFunctionTree(); // Done
    
    void SetFunctionTree(IndependentOperationsNode* FunctionTree); // Done
};

#endif /* FunctionData_hpp */
