//
//  IndependentOperationsNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "IndependentOperationsNode.hpp"


IndependentOperationsNode::IndependentOperationsNode(IndependentOperationsNode* ParentScope){
    Current = NULL;
    scope = ParentScope ? new Scope(ParentScope->GetScope()) : new Scope();
}

IndependentOperationsNode::~IndependentOperationsNode(){
    ListNode* Clear;
    while (Current)
    {
        Clear = Current;
        Current = Current->Next;
        delete Clear;
        Clear = NULL;
    }
    
    if (scope)
        delete scope;
    
    scope = NULL;
}


Scope* IndependentOperationsNode::GetScope(){
    return scope;
}


void IndependentOperationsNode::Push(TNode* Node){
    ListNode* NewNode = new ListNode();
    NewNode->Expression = Node;
    NewNode->Next = NULL;
    
    if (Current == NULL) {
        Current = NewNode;
        return;
    }
    
    ListNode* WorkListNode = Current;
    while(WorkListNode->Next)
        WorkListNode = WorkListNode->Next;
    
    WorkListNode->Next = NewNode;
}


TValue* IndependentOperationsNode::Execute(){
    ListNode* WorkListNode = Current;
    
    while (WorkListNode) {
        WorkListNode->Expression->Execute();
        WorkListNode = WorkListNode->Next;
    }
    
    return NULL;
}


























