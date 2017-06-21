//
//  BinaryOperationNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "BinaryOperationNode.hpp"

BinaryOperationNode::BinaryOperationNode(int Type, TNode* LeftOperand, TNode* RightOperand, int Line){
    if (BinaryOperationList::Instance().GetOperationName(Type))
    {
        this->Type = Type;
        this->LeftOperand = LeftOperand;
        this->RightOperand = RightOperand;
        this->Line = Line;
        Realization = new RealizBinaryOperation();
    }
    else
    {
        throw Exceptions::UnknownOperation;
    }
}

BinaryOperationNode::~BinaryOperationNode()
{
    if (LeftOperand)
        delete LeftOperand;
    
    if (RightOperand)
        delete RightOperand;
    
    if (Realization)
        delete Realization;
}


TValue* BinaryOperationNode::Execute(){
    
    TValue* ResultLeftOperand = LeftOperand->Execute();
    TValue* ResultRightOperand = RightOperand->Execute();
    char* Operation = BinaryOperationList::Instance().GetOperationName(Type);
    
    if (ResultLeftOperand == NULL || ResultRightOperand == NULL)
        throw new Exception("InvalideOperation: невозможно выполнить операцию", Line);
    
    if (ResultLeftOperand->IsReference() && strcmp(Operation, "[]"))
    {
        throw Exceptions::InvalidOperation;
    }
    
    if (ResultRightOperand->IsReference())
    {
        throw Exceptions::InvalidOperation;
    }
    
    return Realization->DoBinaryOpereation(Operation, ResultLeftOperand, ResultRightOperand);
}
