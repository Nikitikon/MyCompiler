//
//  VariableNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef VariableNode_hpp
#define VariableNode_hpp

#include "TNode.hpp"

class VariableNode : public TNode{
protected:
    TValue* Variable;
    
public:
    VariableNode(TValue* Variable);
    ~VariableNode();
    
    TValue* GetTValue();
    double GetValue();
    int GetType();
    
    void SetValue(double Value);
    
    TValue* Execute();
};

#endif /* VariableNode_hpp */
