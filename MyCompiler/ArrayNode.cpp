//
//  ArrayNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "ArrayNode.hpp"
ArrayNode::ArrayNode(TValue* Array, TNode* Index){
    this->Array = Array;
    this->Index = Index;
}

ArrayNode::~ArrayNode(){
    if (Array)
        delete Array;
    
    if (Index)
        delete Index;
}

TValue* ArrayNode::Execute(){
    if (!Array || !Index)
        return NULL;
    
    return Array->GetElementTValue((int)Index->Execute()->GetValue());
}



