//
//  FileReader.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <fstream>
#include "Exceptions.h"
#include "DefaultSetting.hpp"
#include <iostream>
#include <cstring>

using namespace std;

class FileReader
{
private:
    ifstream* fileIO;
    void OpenFile(char*);
    
public:
    FileReader(char*);
    ~FileReader();
    char* ReadLine();
    char* ReadFile();
    char* ReadSourceCode();
    void CloseFile();
};
#endif /* FileReader_hpp */
