//
//  main.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include <iostream>
#include "list_adv.h"
#include "hash.hpp"

using namespace std;

class ListOfDouble : protected List
{
public:
    ListOfDouble() : List(sizeof(double)) { };
    void add (double x) { List::add(&x); };
    double getDouble(int pos)
    {
        return *(double*) get(pos);
    };
    using List::sort;
    using List::error;
    using List::take;
    using List::take_last;
    using List::take_first;
protected:
    int compare(const void *a, const void *b)
    {
        double d1 = *(double*)a;
        double d2 = *(double*)b;
        if (d1 > d2)
            return 1;
        else if (d1 < d2)
            return -1;
        else
            return 0;
    }
};

int main()
{
    
    cout << "Hello world!" << endl;
    
    cout << "Stack: ";
    Stack stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << stack.pop() << " ";
    cout << stack.pop() << " ";
    cout << stack.pop() << endl;
    
    cout << "Queue: ";
    Queue queue;
    queue.put(1);
    queue.put(2);
    queue.put(3);
    cout << queue.get() << " ";
    cout << queue.get() << " ";
    cout << queue.get() << endl;
    
    cout << "Dequeue: " << endl;
    Deque deque;
    deque.put(1);
    deque.put(2);
    deque.put(3);
    deque.put(4);
    cout << "  First: " << deque.first() << endl;
    cout << "  Last: " << deque.last() << endl;
    cout << "  First: " << deque.first() << endl;
    cout << "  Last: " << deque.last() << endl;
    
    cout << "List: " << endl;
    ListOfDouble list;
    list.add(3);
    list.add(1);
    list.add(2);
    cout << "  Unsorted: ";
    cout << list.getDouble(0) << " ";
    cout << list.getDouble(1) << " ";
    cout << list.getDouble(2) << endl;
    list.sort();
    cout << "  Sorted: ";
    cout << list.getDouble(0) << " ";
    cout << list.getDouble(1) << " ";
    cout << list.getDouble(2) << endl;
    
    cout << "  Take: " << endl;
    double store;
    list.take(1, &store);
    cout << store << endl;
    list.take_last(&store);
    cout << store << endl;
    list.take_first(&store);
    cout << store << endl;
    
    cout << "Dictionary: " << endl;
    Diction diction;
    Article *article = new Article();
    article->word = "abc";
    diction.add(article);
    Article *article1 = new Article();
    article1->word = "bcd";
    diction.add(article1);
    Article *article2 = new Article();
    article2->word = "abd";
    diction.add(article2);
    article = diction.find("abc");
    cout << "  abc: " << article << endl;
    cout << "  abd: " << diction.find("abd") << endl;
    cout << "  bcd: " << diction.find("bcd") << endl;
    cout << "  Deleting abc.." << endl;
    diction.del("abc");
    cout << "  abc: " << (diction.find("abc") ? "Found" : "Not found") << endl;
    
    return 0;
}

