//
//  BinaryOperationNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef BinaryOperationNode_hpp
#define BinaryOperationNode_hpp

#include "TNode.hpp"
#include "BinaryOperationList.hpp"
#include "RealizBinaryOperation.hpp"

class BinaryOperationNode : public TNode{
    
protected:
    int Type;
    TNode* LeftOperand;
    TNode* RightOperand;
    RealizBinaryOperation* Realization;
    int Line;
    
public:
    BinaryOperationNode(int Type, TNode* LeftOperand, TNode* RightOperand, int Line); // Done
    ~BinaryOperationNode(); // Done
    
    TValue* Execute(); // Done
    
};


#endif /* BinaryOperationNode_hpp */
