//
//  Parser.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "DefaultSetting.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "list.hpp"

class Parser{
private:
    
    FileReader* fileReader;
    FileWritter* fileWritter;
    
    List* ParseConditions;
    List* StartConditions;
    int StartConditionIndex;
    
    struct Condition{
        char* before;
        char* after;
        char* word;
        
        Condition(char* before, char* after, char* word)
        {
            this->before = new char[strlen(before) + 1];
            this->after = new char[strlen(after) + 1];
            this->word = new char[strlen(word) + 1];
            
            Copy(this->before, before, strlen(before));
            Copy(this->after, after, strlen(after));
            Copy(this->word, word, strlen(word));
        }
    };
    
    void AddCondition(char* before, char* after, char* word); //done
    List* SplitWords(char* Str); //done
    char* CreateThreeConcat(char* str1, char* str2, char* str3); //done
    void ParseString(char* str); //done
    
    
public:
    Parser(char* FileName); //done
    ~Parser(); //done
    char* Find(char* ConditionNow, char* Word); //done
    char* GetStartCondition();//done
    void RestartConditionIndex();//done
    
};

#endif /* Parser_hpp */
