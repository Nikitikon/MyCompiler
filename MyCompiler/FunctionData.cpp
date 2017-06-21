//
//  FunctionData.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 20.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FunctionData.hpp"

FunctionData::FunctionData(int ReturnType, List* ArgumentNameList, List* ArgumentTypeList){
    this->ReturnType = ReturnType;
    this->ArgumentNameList = ArgumentNameList;
    this->ArgumentTypeList = ArgumentTypeList;
}


FunctionData::~FunctionData(){
    if (ArgumentTypeList)
        delete ArgumentTypeList;
    
    if (ArgumentNameList)
        delete ArgumentNameList;
}


int FunctionData::GetReturnType(){
    return ReturnType;
}
























