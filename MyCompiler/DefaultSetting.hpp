//
//  DefaultSetting.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef DefaultSetting_hpp
#define DefaultSetting_hpp

#include <stddef.h>
#include <iostream>
#include "Exception.hpp"

#define SEGMENTSIZE 65536
#define LISTSIZE 64
#define LINESIZE 1025
#define MAX_TYPE_NAME_LENGHT 16
#define MAX_OPERATION_NAME_LENGHT 8
#define MAXRANGE 20
#define SEGMENTCOUNT 1024
#define var auto
#define MAX_VARIABLE_NAME 16

#define AUTOMAT "Automat.txt"
#define LOG "Log.txt"

inline void Copy(char* destination, char* source, int lenght)
{
    for (int i = 0; i < lenght; i++)
    {
        destination[i] = source[i];
    }
    destination[lenght] = '\0';
}


#endif /* DefaultSetting_hpp */
