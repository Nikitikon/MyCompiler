//
//  BinaryOperationList.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef BinaryOperationList_hpp
#define BinaryOperationList_hpp

#include "DefaultSetting.hpp"
#include "list.hpp"

class BinaryOperationList{
    
private:
    List* binaryOperation;
    
    BinaryOperationList(); // Done
    ~BinaryOperationList(); // Done
    void LoadDefaultOperations(); // Done
    
    
    BinaryOperationList(BinaryOperationList const&) = delete;
    BinaryOperationList& operator= (BinaryOperationList const&) = delete;
    
public:
    static BinaryOperationList& Instance(); // Done
    
    bool IsBinaryOperation(char* Name); // Done
    int GetOperationIndex(char* Name); // Done
    char* GetOperationName(int Index); // Done
    
};
#endif /* BinaryOperationList_hpp */
