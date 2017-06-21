//
//  RealizUnarOperation.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "RealizUnarOperation.hpp"

TValue* RealizUnarOperation::UnaryPlasMinus(char* Operation, TValue* ResultOfOperand){
    if (!strcmp(Operation, "+"))
        return new TValue(ResultOfOperand->GetValue(), ResultOfOperand->GetType());
    else
        return new TValue(-(ResultOfOperand->GetValue()), ResultOfOperand->GetType());
}




TValue* RealizUnarOperation::DecrOrIncr(char* Operation, TValue* ResultOfOperand){
    if (!strcmp(Operation, "î++"))
    {
        double temp = ResultOfOperand->GetValue();
        ResultOfOperand->SetValue(temp + 1);
        return new TValue(temp, ResultOfOperand->GetType());
    }
    
    if (!strcmp(Operation, "î--"))
    {
        double temp = ResultOfOperand->GetValue();
        ResultOfOperand->SetValue(temp - 1);
        return new TValue(temp, ResultOfOperand->GetType());
    }
    
    if (!strcmp(Operation, "++î"))
    {
        double temp = ResultOfOperand->GetValue() + 1;
        ResultOfOperand->SetValue(temp);
        return new TValue(temp, ResultOfOperand->GetType());
    }
    
    double temp = ResultOfOperand->GetValue() - 1;
    ResultOfOperand->SetValue(temp);
    return new TValue(temp, ResultOfOperand->GetType());
}





TValue* RealizUnarOperation::NotLogicOperation(char* Operation, TValue* ResultOfOperand){
    return new TValue(!(ResultOfOperand->GetValue()), ResultOfOperand->GetType());
}




TValue* RealizUnarOperation::InputOperation(char* Operation, TValue* ResultOfOperand){
    double temp;
    std::cin >> temp;
    
    return new TValue(temp, TypeList::Instance().GetTypeIndex("double"));
}




TValue* RealizUnarOperation::PrintOperation(char* Operation, TValue* ResultOfOperand){
    if (!ResultOfOperand->IsReference())
    {
        
        char* typeName = TypeList::Instance().GetTypeName(ResultOfOperand->GetType());
        
        if (!strcmp(typeName, "double"))
        {
            cout << ResultOfOperand->GetValue();
        }
        else if (!strcmp(typeName, "float"))
        {
            cout << (float)ResultOfOperand->GetValue();
        }
        else if (!strcmp(typeName, "int"))
        {
            cout << (int)ResultOfOperand->GetValue();
        }
        else if (!strcmp(typeName, "bool"))
        {
            cout << (bool)ResultOfOperand->GetValue();
        }
        else if (!strcmp(typeName, "char"))
        {
            cout << (char)ResultOfOperand->GetValue();
        }
        
    }
    else
    {
        double* pointer = ResultOfOperand->GetPointer();
        
        char i = (char)(*pointer++);
        
        while (i)
        {
            cout << i;
            i = (char)(*pointer++);
        }
    }
    
    return nullptr;
}


TValue* RealizUnarOperation::StandartOperation(char* Operation, TValue* ResultOfOperand){
    if (!strcmp(Operation, "sin"))
    {
        return new TValue(sin(ResultOfOperand->GetValue()), TypeList::Instance().GetTypeIndex("double"));
    }
    
    if (!strcmp(Operation, "cos"))
    {
        return new TValue(cos(ResultOfOperand->GetValue()), TypeList::Instance().GetTypeIndex("double"));
    }
    
    if (!strcmp(Operation, "rand"))
    {
        int random = rand();
        return new TValue(random % (int)ResultOfOperand->GetValue(), TypeList::Instance().GetTypeIndex("int"));
    }
    
    return NULL;
}


TValue* RealizUnarOperation::BreakOperation(char* Operation, TValue* ResultOfOperand){
    if (ResultOfOperand != NULL)
        throw new Exception("return", ResultOfOperand->GetValue());
    
    throw new Exception("return", NULL);
}



TValue* RealizUnarOperation::DoUnarOpereation(char* Operation, TValue* ResultOfOperand){
    if (!strcmp(Operation, "+") || !strcmp(Operation, "-")){
        return UnaryPlasMinus(Operation, ResultOfOperand);
    }
    
    if (!strcmp(Operation, "!")){
        return NotLogicOperation(Operation, ResultOfOperand);
    }
    
    if (!strcmp(Operation, "î++") || !strcmp(Operation, "î--") || !strcmp(Operation, "++î") || !strcmp(Operation, "--î")){
        return DecrOrIncr(Operation, ResultOfOperand);
    }
    
    if (!strcmp(Operation, "input")){
        return InputOperation(Operation, ResultOfOperand);
    }
    
    if (!strcmp(Operation, "print")){
        return PrintOperation(Operation, ResultOfOperand);
    }
    
    if (!strcmp(Operation, "sin") || !strcmp(Operation, "cos") || !strcmp(Operation, "rand")){
        return StandartOperation(Operation, ResultOfOperand);
    }
    
    if (!strcmp(Operation, "return")){
        return BreakOperation(Operation, ResultOfOperand);
    }
    
    throw Exceptions::UnknownOperation;
}


























