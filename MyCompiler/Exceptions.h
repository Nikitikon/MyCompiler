//
//  Exceptions.h
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef Exceptions_h
#define Exceptions_h

enum Exceptions
{
    CharError,						// 0
    StringError,
    FileReaderError,
    TypeNameLengthError,
    UnknownType,
    UnknownOperation,				// 5
    MissingBracket,
    ArgumentOutOfRange,
    InvalidOperation,
    NoTree,
    TokenNotFound,					//10
    VariableNameNotFound,
    VariableTypeNotFound,
    RedefinitionVariable,
    ConstInitializationError,
    VariableInitializationError,	//15
    ArrayInitializationError,
    InitializationError,
    InvalidCharacter,
    UninitializedConstant,
    VariableNameIsNotSpecified,		// 20
    InvalidVariableName,
    ArraySizeIsNotAConstant,
    ArraySizeIsNotAnInteger,
    IndexIsNotSpecified,
    ArrayIndexIsNotAnInteger,		// 25
    ConstantReinitialization,
    SystemFunctionIsNotSupported,
    MissingArguments,
    UnexpectedEndOfFile,
    NullObject
};

#endif /* Exceptions_h */
