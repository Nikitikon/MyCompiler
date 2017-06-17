//
//  RealizBinaryOperation.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "RealizBinaryOperation.hpp"


TValue* RealizBinaryOperation::SquareBrackets(TValue* LeftOperand, TValue* RightOperand){

        if (LeftOperand->IsReference() && RightOperand->GetType() == TypeList::Instance().GetTypeIndex("int"))
        {
            return new TValue((LeftOperand->GetPointer() + (int)RightOperand->GetValue()), LeftOperand->GetType());
        }
        
        throw Exceptions::InvalidOperation;
}





TValue* RealizBinaryOperation::AssignmentOperation(TValue* LeftOperand, TValue* RightOperand){
    
    double Value = RightOperand->GetValue();
    LeftOperand->SetValue(Value);
    return new TValue(Value, LeftOperand->GetType());
}





TValue* RealizBinaryOperation::ArithmeticOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand){
    
    if (!strcmp(Operation, "+"))
    {
        return new TValue(LeftOperand->GetValue() + RightOperand->GetValue(), LeftOperand->GetType());
    }
    
    if (!strcmp(Operation, "-"))
    {
        return new TValue(LeftOperand->GetValue() - RightOperand->GetValue(), LeftOperand->GetType());
    }
    
    if (!strcmp(Operation, "*"))
    {
        return new TValue(LeftOperand->GetValue() * RightOperand->GetValue(), LeftOperand->GetType());
    }
    
    if (!strcmp(Operation, "/"))
    {
        int Type = TypeList::Instance().GetTypeIndex("int");
        
        if (LeftOperand->GetType() == Type && RightOperand->GetType() == Type)
            return new TValue((int)LeftOperand->GetValue() / (int)RightOperand->GetValue(), Type);
        
        return new TValue(LeftOperand->GetValue() / RightOperand->GetValue(), LeftOperand->GetType());
    }
    
    return new TValue((int)LeftOperand->GetValue() % (int)RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("int"));
}





TValue* RealizBinaryOperation::LogicalOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand){
    
    if (!strcmp(Operation, "&&"))
    {
        return new TValue(LeftOperand->GetValue() && RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
    }
    
    return new TValue(LeftOperand->GetValue() || RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
}




TValue* RealizBinaryOperation::ComparisonOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand){
    if (!strcmp(Operation, "=="))
    {
        return new TValue(LeftOperand->GetValue() == RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
    }
    
    if (!strcmp(Operation, "!="))
    {
        return new TValue(LeftOperand->GetValue() != RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
    }
    
    if (!strcmp(Operation, ">"))
    {
        return new TValue(LeftOperand->GetValue() > RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
    }
    
    if (!strcmp(Operation, "<"))
    {
        return new TValue(LeftOperand->GetValue() < RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
    }
    
    if (!strcmp(Operation, ">="))
    {
        return new TValue(LeftOperand->GetValue() >= RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
    }
    
    return new TValue(LeftOperand->GetValue() <= RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("bool"));
}






TValue* RealizBinaryOperation::BitOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand){
    if (!strcmp(Operation, "&"))
    {
        return new TValue((int)LeftOperand->GetValue() & (int)RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("int"));
    }
    
    if (!strcmp(Operation, "|"))
    {
        return new TValue((int)LeftOperand->GetValue() | (int)RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("int"));
    }
    
    if (!strcmp(Operation, "<<"))
    {
        return new TValue((int)LeftOperand->GetValue() << (int)RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("int"));
    }
    
    return new TValue((int)LeftOperand->GetValue() >> (int)RightOperand->GetValue(), TypeList::Instance().GetTypeIndex("int"));
}




TValue* RealizBinaryOperation::StandartOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand){
    
    if (!strcmp(Operation, "min"))
    {
        return new TValue(LeftOperand->GetValue() < RightOperand->GetValue() ? LeftOperand->GetValue() : RightOperand->GetValue(), LeftOperand->GetType());
    }
    
    if (!strcmp(Operation, "max"))
    {
        return new TValue(LeftOperand->GetValue() > RightOperand->GetValue() ? LeftOperand->GetValue() : RightOperand->GetValue(), LeftOperand->GetType());
    }
    
    return NULL;
}




TValue* RealizBinaryOperation::DoBinaryOpereation(char* Operation, TValue* LeftOperand, TValue* RightOperand){
    
    if (!strcmp(Operation, "[]"))
       return SquareBrackets(LeftOperand, RightOperand);
    
    if (!strcmp(Operation, "="))
        return AssignmentOperation(LeftOperand, RightOperand);
    
    if (!strcmp(Operation, "+") || !strcmp(Operation, "-") || !strcmp(Operation, "*") || !strcmp(Operation, "/") || !strcmp(Operation, "%"))
        return ArithmeticOperation(Operation, LeftOperand, RightOperand);
    
    if (!strcmp(Operation, "&&") || !strcmp(Operation, "||"))
        return LogicalOperation(Operation, LeftOperand, RightOperand);
    
    if (!strcmp(Operation, "==") || !strcmp(Operation, "!=") || !strcmp(Operation, ">") || !strcmp(Operation, "<") || !strcmp(Operation, ">=") || !strcmp(Operation, "<="))
        return ComparisonOperation(Operation, LeftOperand, RightOperand);
    
    if (!strcmp(Operation, "&") || !strcmp(Operation, "|") || !strcmp(Operation, "<<") || !strcmp(Operation, ">>"))
        return BitOperation(Operation, LeftOperand, RightOperand);
    
    if (!strcmp(Operation, "min") || !strcmp(Operation, "max"))
        return StandartOperation(Operation, LeftOperand, RightOperand);
    
    throw Exceptions::UnknownOperation;
}

























