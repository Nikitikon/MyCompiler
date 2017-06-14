//
//  TValue.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 14.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef TValue_hpp
#define TValue_hpp
#include "TypeList.hpp"
#include "Exceptions.h"

class TValue{

private:
    int type;
    double* pointer;
    bool referenceType;
    
public:
    TValue(double value, int type, int size = 0);
    TValue(double* pointer, int type);
    TValue();
    ~TValue();
    int GetType();
    double GetValue(int index = 0);
    void SetValue(double v, int index = 0);
    double* GetPointer();
    void SetPointer(double*);
    TValue* GetElementTValue(int index);
    bool IsReference();
    void Print();
};
#endif /* TValue_hpp */
