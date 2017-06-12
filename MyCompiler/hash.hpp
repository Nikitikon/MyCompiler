//
//  hash.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "heap.hpp"
#include "list.hpp"
#include "DefaultSetting.hpp"

class Hash
{
    
public:
    Hash(int _n1, int _n2, int _n3, int _n4, int _n5)
    {
        n1 = abs(_n1) % MAXRANGE + 1;
        n2 = abs(_n2) % MAXRANGE + 1;
        n3 = abs(_n3) % MAXRANGE + 1;
        n4 = abs(_n4) % MAXRANGE + 1;
        n5 = abs(_n5) % MAXRANGE + 1;
        size_t memsize = n1 * n2 * n3 * n4 * n5 * sizeof(List*);
        table = (List**) heap.get_mem(memsize);
        memset(table, 0, memsize);
    };
    
    
    List* find_list(char* key_word) { return table[combine_keys(key_word)]; };
    
    virtual int key1(char* key_word) { return 0; };
    virtual int key2(char* key_word) { return 0; };
    virtual int key3(char* key_word) { return 0; };
    virtual int key4(char* key_word) { return 0; };
    virtual int key5(char* key_word) { return 0; };
    
protected:
    int combine_keys(char* key_word)
    {
        return
        abs(key5(key_word)) % n5 +
        abs(key4(key_word)) % n4 * n4 +
        abs(key3(key_word)) % n3 * n3 * n4 +
        abs(key2(key_word)) % n2 * n2 * n3 * n4 +
        abs(key1(key_word)) % n1 * n1 * n2 * n3 * n4;
    }
    
    void setList(char* key_word, List* list)
    {
        table[combine_keys(key_word)] = list;
    }
    
    virtual ~Hash()
    {
        heap.free_mem(table);
    }
    
private:
    Heap heap;
    List** table;
    int    n1, n2, n3, n4, n5;
};


struct Article
{
    char* word;
    char* description;
};


class Diction_list : public List
{
public:
    Diction_list() : List(sizeof(Article)) {};
    
    // allocate memory for word & description
    void put(Article* article) { add(article); }
    
    Article* find(char* word)
    {
        for(int i = 0; i < count(); i++)
        {
            Article* article = (Article*) get(i);
            if(strcmp(word, article->word))
            {
                return article;
            }
        }
        return NULL;
    }
    
    // free memory from word & decription
    void del(char* word)
    {
        Article* article = find(word);
        if(article != NULL)
        {
            take_first(article);
        }
    }
    
    void del(Article* article) { take_first(article); }
    
protected:
    // purge all Article data
};


class Diction : public Hash
{
public:
    Diction() : Hash(26, 26, 0, 0, 0) {  }
    
    
    int key1(char* key_word)
    {
        int f = key_word[0] - 'A';
        if (f >= 0 && f < 26)
            return f;
        else
            return 0;
    }
    
    int key2(char* key_word) { return key_word[1] % 26; }
    
    Article* find (char* word)
    {
        Diction_list* list = (Diction_list*) find_list(word);
        return list ? list->find(word) : NULL;
    }
    
    void add(Article* article)
    {
        Diction_list* list = (Diction_list*) find_list(article->word);
        if(list == NULL)
        {
            list = new Diction_list();
            setList(article->word, list);
        }
        list->add(article);
    }
    
    void del(char* word)
    {
        Diction_list* list = (Diction_list*) find_list(word);
        if (list != NULL) {
            setList(word, NULL);
        }
    }
};

