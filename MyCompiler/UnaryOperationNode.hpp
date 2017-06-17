//
//  UnaryOperationNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef UnaryOperationNode_hpp
#define UnaryOperationNode_hpp

#include "TNode.hpp"
#include "UnaryOperationList.hpp"
#include "RealizUnarOperation.hpp"

class UnaryOperationNode : public TNode{
    
protected:
    int Type;
    TNode* Operand;
    RealizUnarOperation* Realization;
    
public:
    UnaryOperationNode(int Type, TNode* Operand); // Done
    ~UnaryOperationNode(); // Done
    
    TValue* Execute(); // Done
};

#endif /* UnaryOperationNode_hpp */
