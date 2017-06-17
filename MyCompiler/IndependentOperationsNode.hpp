//
//  IndependentOperationsNode.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef IndependentOperationsNode_hpp
#define IndependentOperationsNode_hpp

#include "TNode.hpp"

class IndependentOperationsNode : public TNode{
    
private:
    struct ListOperation{
        TNode* Expression;
        IndependentOperationsNode* Next;
    };
    
protected:
    Scope scope;
    IndependentOperationsNode* First;
    
public:
    IndependentOperationsNode(IndependentOperationsNode* scope = NULL);
    ~IndependentOperationsNode();
    
    TValue* Execute();
    void  Push(TNode*);
    
    Scope* GetScope();
    
};
#endif /* IndependentOperationsNode_hpp */
