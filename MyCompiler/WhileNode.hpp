//
//  WhileNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef WhileNode_hpp
#define WhileNode_hpp

#include "IndependentOperationsNode.hpp"

class WhileNode : public TNode{
    
private:
    TNode* Condition;
    IndependentOperationsNode* Body;
    
public:
    WhileNode(TNode* Condition, IndependentOperationsNode* Body);
    ~WhileNode();
    
    TValue* Execute();
};

#endif /* WhileNode_hpp */
