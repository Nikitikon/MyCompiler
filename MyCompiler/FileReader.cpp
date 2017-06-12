//
//  FileReader.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "FileReader.hpp"

FileReader::FileReader(char* FileName){
    fileIO = new ifstream();
    OpenFile(FileName);
}

FileReader::~FileReader(){
    CloseFile();
}

void FileReader::OpenFile(char* FileName){
    if (FileName != NULL)
        fileIO->open(FileName);
    
    if (!fileIO->is_open())
        throw Exceptions::FileReaderError;
}

void FileReader::CloseFile(){
    if(fileIO)
        fileIO->close();
}

char* FileReader::ReadLine(){
    
    if (!fileIO || fileIO->eof())
        return NULL;
    
    char* result = new char[LINESIZE];
    fileIO->getline(result, LINESIZE);
    
    return result;
}

char* FileReader::ReadFile(){
    if (!fileIO || fileIO->eof())
        return NULL;
    
    char* line = ReadLine();
    char* file = new char[1];
    file[0] = '\0';
    
    while (line)
    {
        char* temp = new char[strlen(file) + strlen(line) + 2];
        Copy(temp, file, (int)strlen(file));
        Copy(temp + strlen(file), line, (int)strlen(line));
        Copy(temp + strlen(temp), "\n", 1);
        delete[] file;
        delete[] line;
        file = temp;
        line = ReadLine();
    }
    
    return file;
}

char* FileReader::ReadSourceCode(){
    if (!fileIO || fileIO->eof())
        return NULL;
    
    char* file = ReadFile();
    
    char* workStr = new char[strlen(file) + 1];
    
    int i, j;
    for (i = 0, j = 0; i < strlen(file); i++)
    {
        if (file[i] == '\t')
        {
            workStr[j++] = ' ';
        }
        
        else if (file[i] == '\\' && i + 1 < strlen(file) && file[i + 1] == 'n')
        {
            workStr[j++] = '\n';
            i++;
        }
        else
        {
            workStr[j++] = file[i];
        }
    }
    workStr[j] = '\0';
    
    return workStr;
}














