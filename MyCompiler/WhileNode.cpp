//
//  WhileNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "WhileNode.hpp"

WhileNode::WhileNode(TNode* Condition, IndependentOperationsNode* Body){
    this->Condition = Condition;
    this->Body = Body;
}

WhileNode::~WhileNode(){
    if (Condition)
        delete Condition;
    
    if (Body)
        delete Body;
}


TValue* WhileNode::Execute(){
    while (Condition->Execute()->GetValue()) {
        Body->Execute();
    }
    
    return NULL;
}
