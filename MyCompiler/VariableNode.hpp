//
//  VariableNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef VariableNode_hpp
#define VariableNode_hpp

#include "TNode.hpp"

class VariableNode : public TNode{
protected:
    TValue* Variable;
    
public:
    VariableNode(TValue* Variable); // Done
    ~VariableNode(); // Done
    
    TValue* GetTValue(); // Done
    double GetValue(); // Done
    int GetType(); // Done
    
    void SetValue(double Value); // Done
    
    TValue* Execute(); // 
};
#endif /* VariableNode_hpp */
