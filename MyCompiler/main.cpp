//
//  main.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "DefaultSetting.hpp"
#include <iostream>
#include "Builder.hpp"
#include <ctime>

#define R "test.cpp"
//#define R "bullsAndCows.cpp"

using namespace std;

static char* messages[] =
{
    "CharError: ошибка конечного автомата.",
    "StringError: ошибка конечного автомата.",
    "FileReaderError: ошибка чтения файла.",
    "TypeNameLengthError: слишком длинное имя типа.",
    "UnknownType: неподдерживаемый тип данных.",
    "UnknownOperation: неподдерживаемая операция.",
    "MissingBracket: пропущена скобка.",
    "ArgumentOutOfRange: значение аргумента находится вне допустимого диапазона значений.",
    "InvalidOperation: недопустимая операция.",
    "NoTree: необходимо построить синтексное дерево до выполнения.",
    "TokenNotFound: токен не найден.",
    "VariableNameNotFound: необъявленная переменная или константа.",
    "VariableTypeNotFound: неподдерживаемый тип данных.",
    "RedefinitionVariable: недопустимое переопределение переменной.",
    "ConstInitializationError: ошибка инициализации константы.",
    "VariableInitializationError: ошибка объявления константы.",
    "ArrayInitializationError: ошибка объявления массива.",
    "InitializationError: ошибка объявления или инициализации.",
    "InvalidCharacter: недопустимый символ.",
    "UninitializedConstant: неинициализированная константа.",
    "VariableNameIsNotSpecified: не указано имя переменной.",
    "InvalidVariableName: недопустимое имя переменной.",
    "ArraySizeIsNotAConstant: размер массива должен быть задан константой.",
    "ArraySizeIsNotAnInteger: размер массива должен быть целым положительным числом.",
    "IndexIsNotSpecified: не указан индекс элемента массива.",
    "ArrayIndexIsNotAnInteger: индекс массива не является целым числом.",
    "ConstantReinitialization: изменение значения константы невозможно.",
    "SystemFunctionIsNotSupported: неподдерживаемая системная функция.",
    "MissingArguments: пропущены аргументы при вызове функции.",
    "UnexpectedEndOfFile: неожиданный конец файла.",
    "Null Object: Объект не существует"
};

class ClassName{
public:
    char* s;
    ClassName(){
    cout << "classname_constructor" << endl;
}
ClassName(const ClassName &obj){
    cout << "copy_object";
}
~ClassName(){
    cout <<"~classname_destructor" << endl;
}
};

int main()
{
    try{
        Builder* builder = new Builder(R);
        //builder->FindFunction();
        builder->Build();
        builder->Run();

    }
    catch (Exceptions e){
        setlocale(LC_ALL, "Russian");
    }
    catch (Exception* eline){
        setlocale(LC_ALL, "Russian");
        cout << eline->GetMessage() << " Строка: " << eline->GetLine() << "." << endl;
    }
    

    return 0;
}
