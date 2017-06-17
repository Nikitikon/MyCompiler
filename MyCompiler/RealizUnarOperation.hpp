//
//  RealizUnarOperation.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef RealizUnarOperation_hpp
#define RealizUnarOperation_hpp

#include "UnaryOperationList.hpp"
#include "TValue.hpp"
#include <cmath>

class RealizUnarOperation {
    
private:
    TValue* UnaryPlasMinus(char* Operation, TValue* ResultOfOperand); // Done
    TValue* DecrOrIncr(char* Operation, TValue* ResultOfOperand); // Done
    TValue* NotLogicOperation(char* Operation, TValue* ResultOfOperand); // Done
    TValue* InputOperation(char* Operation, TValue* ResultOfOperand); // Done
    TValue* PrintOperation(char* Operation, TValue* ResultOfOperand); // Done
    TValue* StandartOperation(char* Operation, TValue* ResultOfOperand); // Done
    
public:
    RealizUnarOperation(){} // Done
    ~RealizUnarOperation(){} // Done
    TValue* DoUnarOpereation(char* Operation, TValue* ResultOfOperand); // Done
    
};

#endif /* RealizUnarOperation_hpp */
