//
//  TValueKeeper.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 15.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef TValueKeeper_hpp
#define TValueKeeper_hpp

#include "TValue.hpp"

class TValueKeeper{
    
private:
    char* Name;
    TValue* Value;
    bool Const;
    
public:
    
    TValueKeeper(char* Name, TValue* Value, bool Const = false); // Done
    
    ~TValueKeeper(); // Done
    
    
    char* GetName(); // Done
    TValue* GetValue(); // Done
    
    void SetValue(TValue* Value); // Done
    
    bool IsReference(); // Done
    bool IsConst(); // Done
};

#endif /* TValueKeeper_hpp */
