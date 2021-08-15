/*
 * Author: Evelyn Chin
 * Project: 8.0 Stacks and Queues.
 * Purpose: Implements a queue data structure using linked list functions.
 */

#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include "../linked_list_functions/linkedlistfunctionsTemplated.h"

template <class T>
class Queue
{
public:

    class Iterator
    {
    public:
        // PURPOSE: allow queue to access _ptr
        friend class Queue;

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

    // PURPOSE: points Iterator to the head node
    Iterator begin() const 
    {
        return Iterator(_head);
    }

    // PURPOSE: points Iterator to nullptr
    Iterator end() const 
    {
        return Iterator(_tail->_next);
    }

    Queue():_head(nullptr), _tail(nullptr), _size(0){}

    // PURPOSE: Queue deconstructor
    ~Queue()
    {
        _clear_list(_head);
    }

    // PURPOSE: instantiate a copy of other 
    Queue(const Queue<T>& other) : Queue()
    {
        _tail = _copy_list(_head, other._head);
    }

    // PURPOSE: return a copy of rhs
    Queue<T>& operator =(const Queue<T>& rhs)
    {
        // clear queue
        _clear_list(_head);
        // copy queue
        _tail = _copy_list(_head, rhs._head);
        return *this;
    }

    // PURPOSE: Push node to back of queue
    void push(T item)
    {
        _size++;
        _tail = _insert_after(_head, _tail, item);
    }

    // PURPOSE: Delete queue's head and return its value
    // PREREQ: Queue cannot be empty
    T pop()
    {
        assert(!empty());
        _size--;
        T out = _delete_node(_head, _head);
        if (_head == nullptr) _tail = nullptr;
        return out;
    }

    // PURPOSE: Return if queue is empty
    bool empty()
    {
        return _head == nullptr;
    }

    // PURPOSE: Return item of head
    // PREREQ: Queue cannot be empty
    T front()
    {
        assert(!empty());
        return _at(_head, 0);
    }

    // PURPOSE: Return item of tail
    // PREREQ: Queue cannot be empty
    T back()
    {
        assert(!empty());
        return _at(_head, size() - 1);
    }

    // PURPOSE: Return size of queue
    int size() const
    {
        return _size;
    }

    // PURPOSE: print a queue
    template <class S>
    friend ostream& operator <<(ostream& outs, const Queue<S>& q)
    {
        outs << "Queue: ";
        _print_list(q._head);
        return outs;
    }

private:
    node<T>* _head;
    node<T>* _tail;
    int _size;
};

#endif