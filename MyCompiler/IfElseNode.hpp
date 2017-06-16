//
//  IfElseNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef IfElseNode_hpp
#define IfElseNode_hpp

#include "IndependentOperationsNode.hpp"

class IfElseNode : public TNode{
    
protected:
    TNode* Condition;
    IndependentOperationsNode* Then;
    IndependentOperationsNode* Else;
    
public:
    IfElseNode(TNode* Condition, IndependentOperationsNode* Then, IndependentOperationsNode* Else);
    ~IfElseNode();
    
    TValue* Execute();
};

#endif /* IfElseNode_hpp */
