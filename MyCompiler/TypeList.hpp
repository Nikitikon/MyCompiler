//
//  TypeList.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 14.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef TypeList_hpp
#define TypeList_hpp

#include "list.hpp"
#include "DefaultSetting.hpp"
#include "Exceptions.h"

class TypeList{
private:
    List* Types;
    
    
    TypeList(); //Done
    ~TypeList(); //Done
    
    
    TypeList(TypeList const&) = delete;
    TypeList& operator= (TypeList const&) = delete;
    
    
    void AddPrimitiveTypes(); //Done
    
public:
    static TypeList& Instance(); //Done
    void AddUserType(char* Name); //Done
    bool IsType(char* Name); //Done
    int GetTypeIndex(char* Name); //Done
    char* GetTypeName(int Index); //Done
};
#endif /* TypeList_hpp */
