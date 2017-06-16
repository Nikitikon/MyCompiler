//
//  UnaryOperationList.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 16.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef UnaryOperationList_hpp
#define UnaryOperationList_hpp

#include "DefaultSetting.hpp"
#include "list.hpp"

class UnaryOperationList{
    
private:
    List* unaryOperation;
    
    UnaryOperationList(); //
    ~UnaryOperationList(); //
    void LoadDefaultOperations(); //
    
    
    UnaryOperationList(UnaryOperationList const&) = delete;
    UnaryOperationList& operator= (UnaryOperationList const&) = delete;
    
public:
    static UnaryOperationList& Instance(); //
    
    bool IsUnaryOperation(char* Name); //
    int GetOperationIndex(char* Name); //
    char* GetOperationName(int Index); // 
    
};


#endif /* UnaryOperationList_hpp */
