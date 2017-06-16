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
    TValue(double value, int type, int size = 0); // Done
    TValue(double* pointer, int type); // Done
    TValue(); // Done
    ~TValue(); // Done
    int GetType(); // Done
    double GetValue(int index = 0); // Done
    void SetValue(double v, int index = 0); // Done
    double* GetPointer(); // Done
    void SetPointer(double*); // Done
    TValue* GetElementTValue(int index); // Done
    bool IsReference(); // Done
    void Print(); // Done
};
#endif /* TValue_hpp */
