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
    struct ListNode{
        TNode* Expression;
        ListNode* Next;
    };
    
protected:
    Scope* scope;
    ListNode* Current;
    
public:
    IndependentOperationsNode(IndependentOperationsNode* ParentScope = NULL); // Done
    ~IndependentOperationsNode(); // Done
    
    TValue* Execute(); // Done
    void  Push(TNode* Node); // Done
    
    Scope* GetScope(); // Done
    
};
#endif /* IndependentOperationsNode_hpp */
