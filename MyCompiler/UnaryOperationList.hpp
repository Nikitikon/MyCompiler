//
//  UnaryOperationList.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef UnaryOperationList_hpp
#define UnaryOperationList_hpp

#include "DefaultSetting.hpp"
#include "list.hpp"

class UnaryOperationList{
    
private:
    List* unaryOperation;
    
    UnaryOperationList(); // Done
    ~UnaryOperationList(); // Done
    void LoadDefaultOperations(); // Done
    
    
    UnaryOperationList(UnaryOperationList const&) = delete;
    UnaryOperationList& operator= (UnaryOperationList const&) = delete;
    
public:
    static UnaryOperationList& Instance(); // Done
    
    bool IsUnaryOperation(char* Name); // Done
    int GetOperationIndex(char* Name); // Done
    char* GetOperationName(int Index); // Done
    
};

#endif /* UnaryOperationList_hpp */
