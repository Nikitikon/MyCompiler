//
//  FileWriter.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FileWriter.hpp"

FileWritter::FileWritter(char* FileName){
    fileIO = new ofstream();
    
    if (FileName != NULL)
        fileIO->open(FileName);
}

FileWritter::~FileWritter(){
    CloseFile();
}

void FileWritter::CloseFile(){
    if(fileIO) fileIO->close();
}

void FileWritter::WriteLine(char* String){
    *fileIO << String << endl;
}
