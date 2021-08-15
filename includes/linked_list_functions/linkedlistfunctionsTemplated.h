/*
 * Author: Evelyn Chin
 * Project: 8.0 Stacks and Queues.
 * Purpose: A collection of linked list functions.
 */

#ifndef LINKED_LIST_FUNCTIONS_TEMPLATED_H
#define LINKED_LIST_FUNCTIONS_TEMPLATED_H

#include "../node/node.h"
#include "assert.h"

// PURPOSE: Print a linked list of nodes
template <typename T>
void _print_list(node<T>* head)
{
    cout << "Head->";
    while (head != nullptr)
    {
        cout << *head;
        head = head->_next;
    }
    cout << "|||";
}

// PURPOSE: Print a linked list backwards
template <typename T>
void _print_list_backwards(node<T>* head)
{
    // if list is empty
    if (head == nullptr)
    {
        cout << "|||";
        return;
    }
    // if last element in list
    if (head->_next == nullptr)
        cout << *head;
    // if not the last element in list, recursive call
    else 
    {
        _print_list_backwards(head->_next);
        cout << *head;
    }
}

// PURPOSE: Search list for the FIRST node with an item equal to 'key'
// NOTE: Either returns a pointer to node with key or nullptr
template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    // iterate until nullptr reached
    while (head != nullptr)
    {
        if (head->_item == key)
            return head;
        head = head->_next;
    }
    // if key not found
    return nullptr;
}

// PURPOSE: Make insert_this the head of the list
template <typename T>
node<T>* _insert_head(node<T>* &head, T insert_this)
{
    // create new node
    node<T>* temp = new node<T>;
    temp->_item = insert_this;

    // if list is not empty
    if (head != nullptr)
    {
        head->_prev = temp;
        temp->_next = head;
    }

    head = temp;
    return temp;
}

// PURPOSE: Insert node of value 'insert_this' after node 'after_this'.
// If after_this is null, insert after head instead.
// Return new inserted node
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this)
{
    // create new node temp
    node<T>* temp = new node<T>(insert_this);

    // if after_this is null, insert temp after head
    if (after_this == nullptr)
    {
        // if head is null, make temp head
        if (head == nullptr)
            temp = _insert_head(head, insert_this);
        else
        {
            // if head's next is not null
            if (head->_next != nullptr)
            {
                head->_next->_prev = temp;
                temp->_next = head->_next;
            }
            head->_next = temp;
            temp->_prev = head;
        }
    }

    // if after_this is not null, insert temp after after_this
    else
    {
        if (after_this->_next != nullptr)
        {
            after_this->_next->_prev = temp;
            temp->_next = after_this->_next;
        }
        after_this->_next = temp;
        temp->_prev = after_this;
    }

    return temp;
}

// PURPOSE: Insert node of value 'insert_this' before node 'before_this'.
// If before_this is null, insert before head instead.
// Return new inserted node
template <typename T>
node<T>* _insert_before(node<T>* &head, node<T>* before_this, T insert_this)
{
    // create new node temp
    node<T>* temp;

    // if before_this is null, insert temp before head
    if (before_this == nullptr)
        temp = _insert_head(head, insert_this);

    // if before_this is not null, insert temp before before_this
    else
    {
        temp = new node<T>;
        temp->_item = insert_this;
        temp->_prev = nullptr;

        // if before_this has a prev node
        if (before_this->_prev != nullptr)
        {
            before_this->_prev->_next = temp;
            temp->_prev = before_this->_prev;
        }
        // if before_this is head node, update head node
        else 
        {
            head = temp;
        }
        before_this->_prev = temp;
        temp->_next = before_this;
    }

    return temp;
}

// PURPOSE: return a pointer to the previous node
// PREREQS: prev_to_this cannot be a nullptr
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this)
{
    assert(prev_to_this != nullptr);
    return prev_to_this->_prev;
}

// PURPOSE: Delete an item and return it
// PREREQS: Delete_this cannot be a nullptr
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this)
{
    // make sure delete_this is a valid node
    assert(delete_this != nullptr);
    T item = delete_this->_item;

    // if only one item in list, set head to nullptr
    if (delete_this->_next == nullptr && delete_this->_prev == nullptr)
    {
        delete delete_this;
        head = nullptr;
        return item;
    }
    // if delete_this is a head
    if (delete_this->_prev == nullptr)
    {
        delete_this->_next->_prev = nullptr;
        head = delete_this->_next;
    }
    // if delete_this is a tail
    else if (delete_this->_next == nullptr)
        delete_this->_prev->_next = nullptr;
    // else if normal node
    else
    {
        delete_this->_prev->_next = delete_this->_next;
        delete_this->_next->_prev = delete_this->_prev;
    }
    
    delete delete_this;
    return item;
}

// PURPOSE: duplicate a linkedlist and return the HEAD of the copied list
template <typename T>
node<T>* _copy_list(node<T>* head)
{
    // if list is empty
    if (head == nullptr) return nullptr;

    // if list is not empty
    // create newHead and newIter
    node<T>* newHead = new node<T>;
    newHead->_item = head->_item;
    node<T>* newIter = newHead;
    
    // iterate through head and copy data into newIter
    while (head->_next != nullptr)
    {
        head = head->_next;
        node<T>* temp = new node<T>;
        newIter->_next = temp;

        temp->_item = head->_item;
        temp->_prev = newIter;
        temp->_next = head->_next;
        newIter = temp;
    }

    return newHead;
}

// PURPOSE: duplicate a linkedlist and return the END of the copied list
template <typename T>
node<T>* _copy_list(node<T>*& dest_head, node<T>* src_head)
{
    // clear destination list
    _clear_list(dest_head);

    // if list is empty
    if (src_head == nullptr) return nullptr;

    // if list is not empty
    // create newHead and newIter
    dest_head = new node<T>(src_head->_item);
    node<T>* newIter = dest_head;
    
    // iterate through head and copy data into newIter
    while (src_head->_next != nullptr)
    {
        src_head = src_head->_next;
        node<T>* temp = new node<T>;
        newIter->_next = temp;

        temp->_item = src_head->_item;
        temp->_prev = newIter;
        temp->_next = src_head->_next;
        newIter = temp;
    }

    return newIter;
}

// PURPOSE: delete all nodes
template <typename T>
void _clear_list(node<T>*& head)
{
    while (head != nullptr)
    {
        // set temp to head
        node<T>* temp = head;
        // set head to head->next
        head = head->_next;
        // delete temp
        delete temp;
    }
}

// PURPOSE: Return _item at location 'pos'
// PREREQS: List cannot be empty and pos must be within list size
template <typename T>
T& _at(node<T>* head, int pos)
{
    assert(head != nullptr);
    // make sure pos is within list size
    for (int i = 0; i < pos; i++)
    {
        // make sure node is not null, otherwise invalid
        assert(head != nullptr);
        head = head->_next;
    }
    return head->_item;
}

#endif