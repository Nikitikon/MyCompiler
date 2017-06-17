//
//  ConstNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef ConstNode_hpp
#define ConstNode_hpp

#include "TNode.hpp"

class ConstNode : public TNode{
    
protected:
    TValue* Const;
    
public:
    ConstNode(TValue* Const); // Done
    ~ConstNode(); // Done
    
    TValue* GetTValue(); // Done
    double GetValue(); // Done
    int GetType(); // Done
    
    TValue* Execute(); // Done
    
};

#endif /* ConstNode_hpp */
