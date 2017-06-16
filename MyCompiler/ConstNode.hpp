//
//  TConst.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef TConst_hpp
#define TConst_hpp

#include "TNode.hpp"

class ConstNode : public TNode{
    
protected:
    TValue* Const;
    
public:
    ConstNode(TValue* Const);
    ~ConstNode();
    
    TValue* GetTValue();
    double GetValue();
    int GetType();
    
    TValue* Execute();
    
};

#endif /* TConst_hpp */
