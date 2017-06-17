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

class BinaryOperationNode : public TNode{
    
protected:
    int Type;
    TNode* LeftOperand;
    TNode* RightOperand;
    
public:
    BinaryOperationNode(int Type, TNode* LeftOperand, TNode* RightOperand);
    ~BinaryOperationNode();
    
    TValue* Execute();
    
};


#endif /* BinaryOperationNode_hpp */
