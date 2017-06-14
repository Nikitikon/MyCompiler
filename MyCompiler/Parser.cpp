//
//  Parser.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 12.06.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "Parser.hpp"


using namespace std;


Parser::Parser(char* FileName){

    StartConditionIndex = 0;
    ParseConditions = new List(sizeof(Condition));
    StartConditions = new List(MAXRANGE);
    
    fileWritter = new FileWritter(LOG);
    fileReader = new FileReader(FileName);
    
    char* str;
    while ((str = fileReader->ReadLine()) != NULL) {
        ParseString(str);
    }

   delete fileReader;
}

Parser::~Parser(){
    if(ParseConditions)
        delete ParseConditions;
    
    if(fileWritter)
        delete fileWritter;
    
    if(StartConditions)
        delete StartConditions;
}

void Parser::AddCondition(char* before, char* after, char* word){ // Добавляем состояние в список
    
    var tempCondition = new Condition(before, after, word);
    ParseConditions->add(tempCondition);

}

char* Parser::CreateThreeConcat(char* str1, char* str2, char* str3){ // Для красивого вывода
    
    var WorkStr = new char[strlen(str1) + strlen(str2) + strlen(str3) + 1];
    strncat(WorkStr, str1, strlen(str1));
    strncat(WorkStr, "\t", 1);
    strncat(WorkStr, str2, strlen(str2));
    strncat(WorkStr, "\t", 1);
    strncat(WorkStr, str3, strlen(str3));
    
    return WorkStr;
}


List* Parser::SplitWords(char* Str){ // Разделяет правило на несколько лексем
    
    char* word = new char[MAXRANGE];
    memset(word, '\0', strlen(word));
    List* wordList = new List(MAXRANGE); //Список разделенных лексем
    
    if (strlen(Str) == 1 && Str[0] == ',') { // если лексема запятая
        word[0] = ',';
        wordList->add(word);
        return wordList;
    }
    
    if (strlen(Str) == 2 && Str[0] == '\\') { // если лексема - escape-последовательность
        if (Str[1] == 'n')
            word[0] = '\n';
        if (Str[1] == 't')
            word[0] = '\t';
        
        wordList->add(word);
        return wordList;
    }
    
    //если лексемы соединены в одну запись и идут через запятую
    int wordPosition = 0;
    for (int i = 0; i < strlen(Str); i++) {
        if (Str[i] == ',') {
            Copy(word, Str + wordPosition, i - wordPosition);
            wordPosition = i + 1;
            wordList->add(word);
        }
    }
    Copy(word, Str + wordPosition, strlen(Str) - wordPosition);
    wordList->add(word);
    
    return wordList;
}

void Parser::ParseString(char* Str){ // Парсит файл с инструкциями и помещает их в лист
    
    if (strlen(Str) == 0)
        return;
    
    if (Str[0] == '#') // комментарий
        return;
    
    if (strlen(Str)>5) // находим начальные состояния
    {
        char* start = new char[6];
        Copy(start, Str, 5);
        
        if (!strcmp(start, "start"))
        {
            char* startCondition = new char[strlen(Str) - 6];
            Copy(startCondition, Str+6, strlen(Str)-6);
            StartConditions->add(startCondition);
            return;
        }
    }
    
    int tabulationPosition[2]; // в файле все разделено на табуляции
    for (int i = 0, j = 0; i < 2; j++) {
        if(Str[j] == '\t')
            tabulationPosition[i++] = j + 1;
    }
    
    char* before = new char[tabulationPosition[0]];
    Copy(before, Str, tabulationPosition[0] - 1);
    
    char* word = new char[tabulationPosition[1] - tabulationPosition[0]];
    Copy(word, Str + tabulationPosition[0], tabulationPosition[1] - tabulationPosition[0] - 1);
    
    char* after = new char[strlen(Str) - tabulationPosition[1]];
    Copy(after, Str + tabulationPosition[1], strlen(Str) - tabulationPosition[1]);
    
    List* wordList = SplitWords(word);
    
    int wordListCount = wordList->count();
    for (int i = 0; i < wordListCount; i++) {
        char* word = (char*)wordList->get(i);
        AddCondition(before, after, word);
        
    }
    
    delete wordList;
    
}

char* Parser::Find(char* ConditionNow, char* Word){ // находим требуемую инструкцию по состоянию на текущий момент и последовательности символов
    Condition* tempCondition = NULL;
    
    int ConditionListCount = ParseConditions->count();
    
    for (int i = 0; i < ConditionListCount; i++) {
        tempCondition = (Condition*)ParseConditions->get(i);
        
        // если мы нашли подходящую инструкцию
        if (!strcmp(Word, tempCondition->word) && !strcmp(ConditionNow, tempCondition->before)) {
            
            if (fileWritter){
                char* StrForWrite = CreateThreeConcat(tempCondition->before, tempCondition->word, tempCondition->after);
                fileWritter->WriteLine(StrForWrite);
            }
            
            return tempCondition->after;
        }
        
        // если для данного состояния можно ввести любую последоватьельность символов
        if (!strcmp("...", tempCondition->word) && !strcmp(ConditionNow, tempCondition->before)) {
            
            if (fileWritter){
                char* StrForWrite = CreateThreeConcat(tempCondition->before, Word, tempCondition->after);
                fileWritter->WriteLine(StrForWrite);
            }

            return tempCondition->after;
        }
    }
    
    return  NULL;
}


char* Parser::GetStartCondition(){ // возвращает стартовое состояние по текущему индексу и увеличивает индекс
    
    if (StartConditionIndex < StartConditions->count())
        return ((char*)StartConditions->get(StartConditionIndex++));
    
    return NULL;
}

void Parser::RestartConditionIndex(){ // обнуляет индекс
    StartConditionIndex = 0;
}














