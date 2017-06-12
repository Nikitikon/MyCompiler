//
//  FileWriter.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef FileWriter_hpp
#define FileWriter_hpp

#include <fstream>

using namespace std;

class FileWritter
{
private:
    ofstream* fileIO;
    
public:
    FileWritter(char*);
    ~FileWritter();
    void CloseFile();
    void WriteLine(char*);
};

#endif /* FileWriter_hpp */
