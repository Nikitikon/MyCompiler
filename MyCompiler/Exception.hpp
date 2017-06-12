//
//  Exception.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

class Exception
{
    char* _message;
    int _line;
    
public:
    Exception(char* message, int line);
    ~Exception();
    
    char* GetMessage();
    int GetLine();
};

#endif /* Exception_hpp */
