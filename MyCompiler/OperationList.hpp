//
//  OperationList.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 14.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef OperationList_hpp
#define OperationList_hpp

#include "list.hpp"
#include "DefaultSetting.hpp"

class OperationList{
    
private:
    List* operations;
    
    OperationList(); // Done
    void LoadDefaultOperations(); // Done
    ~OperationList(); // Done
    
    OperationList(OperationList const&) = delete;
    OperationList& operator= (OperationList const&) = delete;
    
public:
    static OperationList& Instance(); // Done
    bool IsOperation(char* Name); // Done
    int GetOperationIndex(char* Name); // Done
    char* GetOperationName(int index); // Done
};
#endif /* OperationList_hpp */
