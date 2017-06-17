//
//  ConstNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef ConstNode_hpp
#define ConstNode_hpp

#include "TNode.hpp"

class ConstNode : public TNode{
    
protected:
    TValue* Const;
    
public:
    ConstNode(TValue* Const);
    ~ConstNode();
    
    TValue* GetTValue();
    double GetValue();
    int GetType();
    
    TValue* Execute();
    
};

#endif /* ConstNode_hpp */
