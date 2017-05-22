//
//  list.hpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "heap.hpp"

#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;
#define LISTSIZE 64
class List
//Û‰‡ÎˇÚ¸, Ò‡ÁÛ ÒÊËÏ‡Ú¸
//first_index ‡·ÓÚ‡ÂÚ Í‡Í ÌÛÎÂ‚ÓÈ ˝ÎÂÏÂÌÚ Ï‡ÒÒË‚‡
{
public:
    List(int _element_size, int _element_count = LISTSIZE)
    {
        element_count = _element_count;
        element_size = _element_size;
        first_index = 0;
        last_index = -1;
        first = NULL;
        last = NULL;
    }
    ~List();
    
    void*		get(int pos);			//done
    void		add(void* data);		//done
    
    // returns and deletes elements
    void		take_first(void* store);	//
    void		take_last(void* store);		//
    void		take(int pos, void* store);		//
    void		sort(bool dir = true);		//done
    virtual int		compare(const void* op1, const void* op2)
    {
        return 0;
    }
    int			count();// done
    bool		error() { return _error; } // true if error in last operation
    
    //private:
public:	//while debug
    struct Segment
    {
        void*    data;
        Segment* prev = NULL;
        Segment* next = NULL;
    };
    
    Segment*	first;
    Segment*	last;
    int			first_index;
    int			last_index;
    
    int			element_size;
    int			element_count;
    bool		_error = false;
    
    void		delete_element(int index, int recursion_correction = 0);	//need del
    void		new_segment();					//done
    void		delete_segment(Segment* seg);	// done
    void*		calculate_position(int index);	//done
};

#endif
