//
//  IfElseNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
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
    IfElseNode(TNode* Condition, IndependentOperationsNode* Then,IndependentOperationsNode* Else); // Done
    ~IfElseNode(); // Done
    
    TValue* Execute(); // Done
};
#endif /* IfElseNode_hpp */
