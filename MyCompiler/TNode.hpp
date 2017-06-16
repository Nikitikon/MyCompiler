//
//  TNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef TNode_hpp
#define TNode_hpp

#include "DefaultSetting.hpp"
#include "Scope.hpp"
#include "OperationList.cpp"
#include "Exceptions.h"

class TNode {
    
public:
    virtual TValue* Execute() = 0;
    
};


#endif /* TNode_hpp */
