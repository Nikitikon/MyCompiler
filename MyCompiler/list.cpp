//
//  list.cpp
//  MyCompiler
//
//  Created by Nikita-Mac on 22.05.17.
//  Copyright © 2017 Nikita-Mac. All rights reserved.
//

#include "list.hpp"
extern Heap* _heap = new Heap();

List::~List()
{
    first_index = last_index = -1;
    Segment *cur = first;
    while (cur)
    {
        _heap->free_mem(cur->data);
        Segment *next = cur->next;
        _heap->free_mem(cur);
        cur = next;
    }
}

void List::sort(bool dir)
{
    if (first_index == -1 || first_index > last_index - 1)
    {
        _error = true;
        return;
    }
    _error = false;
    
    int _count = count();
    
    for (int i = 0; i < _count ; i++)
    {
        for (int j = i; j < _count; j++)
        {
            int comp = compare(calculate_position(i), calculate_position(j));
            if ((comp > 0 && dir) || (comp < 0 && !dir))
            {
                void* temp = malloc(element_size);
                memcpy(temp, get(i), element_size);
                memcpy(get(i), get(j), element_size);
                memcpy(get(j), temp, element_size);
                free(temp);
            }
        }
    }
}

int List::count()
{
    if (first_index == -1)
    {
        _error = true;
        return -1;
    }
    _error = false;
    return last_index - first_index + 1;
}

void List::take_last(void* store)
{
    if (first_index == -1 )
    {
        _error = true;
        return;
    }
    _error = false;
    memcpy(store, calculate_position(last_index - first_index), element_size);
    delete_element(last_index - first_index);
}

void List::take_first(void* store)
{
    if (first_index == -1 )
    {
        _error = true;
        return;
    }
    _error = false;
    memcpy(store, calculate_position(0), element_size);
    delete_element(0);
}

void List::take(int pos, void* store)
{
    if (first_index == -1 || pos + first_index >= last_index)
    {
        _error = true;
        return;
    }
    _error = false;
    void* datePos = calculate_position(pos);
    memcpy(store, datePos, element_size);
    delete_element(pos);
}

void List::delete_element(int index, int recursion_correction)
{
    for (int i = index; i < last_index - first_index; i++)
    {
        memcpy(calculate_position(i), calculate_position(i + 1), element_size);
    }
    last_index--;
    return;
}

void List::add(void* data)
{
    if (data == nullptr || data == NULL)
        return;
    
    if (first_index == -1)
    {
        _error = true;
        return;
    }
    _error = false;
    
    if (!first)
        new_segment();
    
    void* temp_ref = calculate_position(last_index + 1);
    
    if (!temp_ref)
    {
        new_segment();
        temp_ref = calculate_position(last_index + 1);
    }
    
    memcpy(temp_ref, data, (size_t)element_size);
    last_index++;
}

void* List::get(int pos)
{
    if (first_index == -1 || pos > last_index)
    {
        _error = true;
        return NULL;
    }
    _error = false;
    return calculate_position(pos);
}

void* List::calculate_position(int index)
{
    int offset = element_size*first_index;
    Segment* current = first;
    int cur_index = 0;
    while (current)
    {
        while (offset <= (element_count - 1)*element_size)
        {
            if (cur_index != index)
            {
                cur_index++;
                offset += element_size;
                continue;
            }
            else
            {
                return (void*)((size_t)current->data + offset);
            }
        }
        offset = 0;
        current = current->next;
    }
    return NULL;
}

void List::new_segment()
{
    Segment* tempSegment = new Segment();
    tempSegment->next = NULL;
    tempSegment->prev = NULL;
    tempSegment->data = _heap->get_mem(element_size * element_count);
    
    if (!first)
        first = tempSegment;
    if (!last)
        last = tempSegment;
    else
    {
        last->next = tempSegment;
        tempSegment->prev = last;
        last = tempSegment;
    }
}

void List::delete_segment(Segment* seg)
{
    if (seg == NULL)
    {
        _error = true;
        return;
    }
    
    _error = false;
    
    if (seg == first && seg == last)
    {
        first = last = NULL;
    }
    else
    {
        if (seg == last)
        {
            last = seg->prev;
            seg->prev->next = seg->next;
            last->next = NULL;
        }
        if (seg == first)
        {
            first = seg -> next;
            seg->next->prev = seg->prev;
            first->prev = NULL;
        }
        else
        {
            seg->next->prev = seg->prev;
            seg->prev->next = seg->next;
        }
    }
    
    _heap->free_mem(seg->data);
    _heap->free_mem(seg);
    
}

