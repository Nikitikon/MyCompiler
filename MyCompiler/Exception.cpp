//
//  Exception.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Exception.hpp"
Exception::Exception(char* message, double line)
{
    _message = message;
    _line = line;
}
Exception::~Exception()
{
}
char* Exception::GetMessage()
{
    return _message;
}
double Exception::GetLine()
{
    return _line;
}
