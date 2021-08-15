/*
 * Author: Evelyn Chin
 * Project: 8.0 Stacks and Queues.
 * Purpose: Node struct that contains an item, a next node, and a prev node.
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <class T>
struct node
{
    T _item;
    node<T>* _next;
    node<T>* _prev;

    node(const T& item = T(), node<T>* next = nullptr, node<T>* prev = nullptr):
        _item(item), _next(next), _prev(prev) {}

    friend ostream& operator << (ostream& outs, const node<T>& print_me)
    {
        outs << "<-[" << print_me._item << "]->";
        return outs;
    }
};

#endif