/*
 * Author: Evelyn Chin
 * Project: 8.0 Stacks and Queues.
 * Purpose: Implements a stack data structure using linked list functions.
 */

#ifndef MY_STACK_H
#define MY_STACK_H

#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <class T>
class Stack
{
public:
    class Iterator
    {
    public:
        // PURPOSE: allow queue to access _ptr
        friend class Stack;

        // PURPOSE: default constructor
        Iterator() : _ptr(nullptr) {}

        // PURPOSE: constructor pointing Iterator to p's data
        Iterator(node<T>* p)
        {
            _ptr = p;
        }

        // PURPOSE: dereferencing operator
        // PREREQ: _ptr cannot be nullptr
        T operator *()
        {
            assert(_ptr != nullptr);
            return _ptr->_item;
        }

        // PURPOSE: return if _ptr is nullptr
        bool is_null()
        {
            return _ptr == nullptr;
        }
        
        // PURPOSE: returns if left != right
        friend bool operator !=(const Iterator& left, const Iterator& right)
        {
            return left._ptr != right._ptr;
        }
        
        // PURPOSE: returns if left == right
        friend bool operator ==(const Iterator& left, const Iterator& right)
        {
            return left._ptr == right._ptr;
        }
        
        // PURPOSE: member operator ++it
        Iterator& operator++()
        {
            _ptr = _ptr->_next;
            return this;
        }
        
        // PURPOSE: friend operator it++
        friend Iterator operator++(Iterator& it, int unused)
        {
            Iterator hold = it;
            it._ptr = it._ptr->_next;
            return hold;
        }
    private:
        node<T>* _ptr;
    };

    // PURPOSE: points Iterator to the top of the stack
    Iterator begin() const 
    {
        return Iterator(_top);
    }

    // PURPOSE: points Iterator to nullptr
    Iterator end() const 
    {
        node<T>* temp = _top;
        while (temp != nullptr)
            temp = temp->_next;
        return Iterator(temp);
    }

    Stack():_top(nullptr), _size(0){}
    
    ~Stack()
    {
        _clear_list(_top);
    }

    Stack(const Stack<T>& other) : Stack()
    {
        // copy list
        _top = _copy_list(other._top);
    }
    
    // PURPOSE: set this stack equal to a copy of rhs
    Stack<T>& operator =(const Stack<T>& rhs)
    {
        // clear stack
        _clear_list(_top);
        // copy list
        _top = _copy_list(rhs._top);

        return *this;
    }
    
    // PURPOSE: Push node to top of stack
    void push(T item)
    {
        _size++;
        _insert_head(_top, item);
    }
    
    // PURPOSE: Delete queue's head and return its value
    // PREREQ: Stack cannot be empty
    T pop()
    {
        assert(!empty());
        _size--;
        return _delete_node(_top, _top);
    }
    
    // PURPOSE: Return item at the top
    // PREREQ: Stack cannot be empty
    T top()
    {
        assert(!empty());
        return _at(_top, 0);
    }
    
    // PURPOSE: Return if stack is empty
    bool empty()
    {
        return _top == nullptr;
    }
    
    // PURPOSE: Return size of queue
    int size() const
    {
        return _size;
    }

    // PURPOSE: print a stack
    friend ostream& operator << (ostream& outs, const Stack& s)
    {
        outs << "Stack: ";
        _print_list(s._top);
        return outs;
    }
private:
    node<T>* _top;
    int _size;
};

#endif