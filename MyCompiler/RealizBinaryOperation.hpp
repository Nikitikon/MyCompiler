//
//  RealizBinaryOperation.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef RealizBinaryOperation_hpp
#define RealizBinaryOperation_hpp

#include "TValue.hpp"

class RealizBinaryOperation {
    
private:
    TValue* SquareBrackets(TValue* LeftOperand, TValue* RightOperand); // Done
    TValue* AssignmentOperation(TValue* LeftOperand, TValue* RightOperand); // Done
    TValue* ArithmeticOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand); // Done
    TValue* LogicalOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand); // Done
    TValue* ComparisonOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand); // Done
    TValue* BitOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand); // Done
    TValue* StandartOperation(char* Operation, TValue* LeftOperand, TValue* RightOperand); // Done

    
public:
    RealizBinaryOperation(){} // Done
    ~RealizBinaryOperation(){} // Done
    TValue* DoBinaryOpereation(char* Operation, TValue* LeftOperand, TValue* RightOperand); // Done
};

#endif /* RealizBinaryOperation_hpp */
