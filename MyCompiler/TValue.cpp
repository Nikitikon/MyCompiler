//
//  TValue.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 14.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "TValue.hpp"

// Для выделения памяти под переменную или массив.
// Value - Значение для переменной, значение для элементов для массива
// type - Тип переменной или тип элементов массива
// size - Размер массива, 0 для переменной
TValue::TValue(double value, int type, int size){
    if (TypeList::Instance().GetTypeName(type)) {
            
        this->type = type;
        
        if (size > 0)
        {
            this->pointer = new double[size];
            
            for (int i = 0; i < size; i++)
                this->pointer[i] = value;
            
            referenceType = true;
        }
        else
        {
            pointer = new double[1];
            *(this->pointer) = value;
            
            referenceType = false;
        }
    }
    else
        throw Exceptions::UnknownType;
}

// Создание TValue для переменной в уже выделенной памяти.
// pointer - Указатель для выделенной памяти
// type - Тип переменной, на которую указывает поинтер, или тип элементов массива
TValue::TValue(double* pointer, int type)
{
    if (TypeList::Instance().GetTypeName(type))
    {
        this->pointer = pointer;
        this->type = type;
        this->referenceType = false;
    }
    else
        throw Exceptions::UnknownType;
}

// Создание указателя на nullptr типа void*.
TValue::TValue()
{
    this->pointer = nullptr;
    if ((this->type = TypeList::Instance().GetTypeIndex("void") < 0))
        throw Exceptions::UnknownType;
}

TValue::~TValue()
{
    if (pointer && referenceType)
        delete pointer;
    
    pointer = nullptr;
}

// Получает тип переменной или массива.
int TValue::GetType()
{
    return type;
}

// Получает значение переменной или элемента массива.
double TValue::GetValue(int index)
{
    if (referenceType)
    {
        return pointer[index];
    }
    
    return *pointer;
}

// Устанавливает значение переменной или элемента массива.
void TValue::SetValue(double v, int index)
{
    if (referenceType)
    {
        pointer[index] = v;
    }
    
    *pointer = v;
}

// Получает адрес переменной или первого элемента массива.
double* TValue::GetPointer()
{
    return pointer;
}

// Устанавливает адрес переменной или первого элемента массива.
void TValue::SetPointer(double* pointer)
{
    this->pointer = pointer;
}

// Вовзращает переменную, хранащую элемент массива.
TValue* TValue::GetElementTValue(int index)
{
    if (referenceType)
        return new TValue(pointer + index, type);
    
    throw Exceptions::InvalidOperation;
}


bool TValue::IsReference()
{
    return referenceType;
}

void TValue::Print()
{
    if (referenceType)
    {
        std::cout << pointer << " " << TypeList::Instance().GetTypeName(type) << std::endl;
    }
    else
    {
        std::cout << *pointer << " " << TypeList::Instance().GetTypeName(type) << std::endl;
    }
}
