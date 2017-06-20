//
//  TNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef TNode_hpp
#define TNode_hpp

#include "DefaultSetting.hpp"
#include "Scope.hpp"
#include "OperationList.hpp"
#include "Exceptions.h"

class TNode {
    
protected:
    
public:
    virtual TValue* Execute() = 0;
    
};
#endif /* TNode_hpp */
