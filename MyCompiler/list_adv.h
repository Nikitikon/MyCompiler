//
//  list_adv.h
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#ifndef list_adv_h
#define list_adv_h


#include "list.hpp"

class Stack : List
{
public:
    Stack() : List(sizeof(double)) { };
    ~Stack() { List::~List(); }
    
    void   push(double x) { add(&x); };
    double pop() { double res; take_last(&res); return res; };
};

class Queue : List
{
public:
    Queue() : List(sizeof(double)) { };
    ~Queue() { List::~List(); }
    
    void   put(double x) { add(&x); };
    double get() { double res; take_first(&res); return res; };
};

class Deque : protected List
{
public:
    Deque() : List(sizeof(double)) { };
    ~Deque() { List::~List(); }
    
    void   put(double x) { add(&x); };
    double first() { double res; take_first(&res); return res; };
    double last()  { double res; take_last(&res); return res; };
    
};
#endif /* list_adv_h */
