//
//  Builder.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 17.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Builder.hpp"

Builder::Builder(char* sourceCode){
    Automat* automat = new Automat(AUTOMAT);
    FileReader* fileReader = new FileReader(sourceCode);
    
    try {
        Tokens = automat->Work(fileReader->ReadSourceCode());
    } catch (Exceptions e) {
        throw new Exception("Ошибка конечного автомата", 0);
    }
    
    if (automat)
        delete automat;
    
    if (fileReader)
        delete fileReader;
    
    Tokens = OldTokenToNewToken(Tokens);
    
    PrintList(Tokens);
    
    Prioritize(Tokens);
    
    Root = NULL;
    CurrentList = NULL;
    CurrentScope = NULL;
}
