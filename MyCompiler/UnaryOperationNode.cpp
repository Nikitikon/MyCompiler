//
//  UnaryOperationNode.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "UnaryOperationNode.hpp"


UnaryOperationNode::UnaryOperationNode(int Type, TNode* Operand){
    
    if (UnaryOperationList::Instance().GetOperationName(Type)) {
        this->Type = Type;
        this->Operand = Operand;
        Realization = new RealizUnarOperation();
    }
    else
        throw Exceptions::UnknownOperation;
}


UnaryOperationNode::~UnaryOperationNode(){
    if (Operand)
        delete Operand;
    
    if (Realization)
        delete Realization;
}


TValue* UnaryOperationNode::Execute(){
    if (Operand == NULL){
        if (Type == UnaryOperationList::Instance().GetOperationIndex("return"))
            return Realization->DoUnarOpereation("return", NULL);
        else
            throw new Exception("MissingOperand: пропущен операнд", 0);
    }
    TValue* resultOfOperand = Operand->Execute();
    
    char* operation = UnaryOperationList::Instance().GetOperationName(Type);
    
    if (resultOfOperand->IsReference() && strcmp(operation, "print"))
        throw Exceptions::InvalidOperation;
    
    return Realization->DoUnarOpereation(operation, resultOfOperand);
}














































