//
//  ArrayNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef ArrayNode_hpp
#define ArrayNode_hpp

#include "TNode.hpp"

class ArrayNode : public TNode{
    
protected:
    TValue* Array;
    TNode* Index;
    
public:
    ArrayNode(TValue* Array, TNode* Index); // Done
    ~ArrayNode(); // Done
    
    
    TValue* Execute(); // Done
};
#endif /* ArrayNode_hpp */
