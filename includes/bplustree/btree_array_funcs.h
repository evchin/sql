/*
 * Author: Evelyn Chin
 * Project: BPlusTree
 * Project Purpose: A BPlusTree class.
 * File Purpose: Templated Interface for B+ Tree's array functions 
 */

#ifndef BTREE_ARRAY_FUNCTIONS_H
#define BTREE_ARRAY_FUNCTIONS_H

#include <iostream>
#include <cassert>
#include <vector>

// Return the larger of the two items
template <class T>
T maximal(const T& a, const T& b)
{
    if (a > b) return a;
    return b;
}

// Swap the two items
// template <class T>
// void swap(T& a, T& b)
// {
//     T temp = a;
//     a = b;
//     b = temp;
// }

// Return index of the largest item in data
template <class T>
int index_of_maximal(T data[ ], int n)
{
    assert(n != 0);
    int max = 0;
    for (int i = 0; i < n; i++)
        if (data[max] < data[i]) max = i;
    return max;
}

// Return the first element in data that is not less than entry
template <class T>
int first_ge(const T data[ ], int n, const T& entry)
{
    for (int i = 0; i < n; i++)
        if (data[i] >= entry) return i;
    return n;
}

// Insert entry at index i in data
template <class T>
void insert_item(T data[ ], int i, int& n, T entry)
{
    for (int index = n-1; index >= i; index--)
        data[index + 1] = data[index];
    data[i] = entry;
    n++;
}

// Insert entry into sorted array
template <class T>
void ordered_insert(T data[ ], int& n, T entry)
{
    int index = first_ge(data, n, entry);
    insert_item(data, index, n, entry);
}

// Append entry to the right of data
template <class T>
void attach_item(T data[ ], int& n, const T& entry)
{
    data[n++] = entry;
}

// Remove the last element in data and place it in entry
template <class T>
void detach_item(T data[ ], int& n, T& entry)
{
    assert(n != 0);
    entry = data[--n];
}

// Delete item at index i and place it in entry
template <class T>
void delete_item(T data[ ], int i, int& n, T& entry)
{
    entry = data[i];
    for (int index = i+1; index < n; index++)
        data[index-1] = data[index];
    n--;
}

// Append data2 to the right of data1
template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)
{
    int i2 = 0;
    for (int i = n1; i < n1 + n2; i++)
        data1[i] = data2[i2++];
    n1 += n2;
    n2 = 0;
}

// Move n/2 elements from the right of data1 and move to data2
template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)
{
    n2 = n1/2;
    int index = 0;
    for (int i = n1 - n2; i < n1; i++)
        data2[index++] = data1[i];
    n1 -= n2;
}

// Copy src[] into dest[]
template <class T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size)
{
    for (int i = 0; i < src_size; i++)
        dest[i] = src[i];
    dest_size = src_size;
}

// Print array data
template <class T>
void print_array(const T data[], int n, int pos = -1)
{
    std::cout << "[";
    if (pos == -1) pos = 0;
    for (int i = pos; i < n; i++)
    {
        if (i == n - 1) std::cout << data[i];
        else std::cout << data[i] << ", ";
    }
    std::cout << "]";
}

// item > all data[i]
template <class T>
bool is_gt(const T data[], int n, const T& item)
{
    assert(n != 0);
    for (int i = 0; i < n; i++)
        if (data[i] >= item) return false;
    return true;
}

// item <= all data[i]
template <class T>
bool is_le(const T data[], int n, const T& item)
{
    assert(n != 0);
    for (int i = 0; i < n; i++)
        if (data[i] < item) return false;
    return true;
}

// return if array is sorted
template <class T>
bool is_sorted(const T data[], int n)
{
    for (int i = 0; i < n - 1; i++)
        if (data[i] > data[i + 1]) return false;
    return true;
}

// return if vector is sorted
template<typename T>
bool is_sorted(const std::vector<T> v)
{
    for (int i = 0; i < v.size() - 1; i++)
        if (v[i] > v[i + 1]) return false;
    return true;
}

// Print vector list
template <typename T>
std::ostream& operator <<(std::ostream& outs, const std::vector<T>& list)
{
    outs << "[";
    for (int i = 0; i < list.size(); i++)
    {
        if (i == list.size() - 1) outs << list[i];
        else outs << list[i] << ", ";
    }
    outs << "]";
    return outs;
}

// list.push_back addme
template <typename T>
std::vector<T>& operator +=(std::vector<T>& list, const T& addme)
{
    list.push_back(addme);
    return list;
}

// // list.push_back addme
template <typename T>
std::vector<T>& operator +=(std::vector<T>& list, const std::vector<T>& append_me)
{
    list.insert(list.end(), append_me.begin(), append_me.end());
    return list;
}

#endif // BTREE_ARRAY_FUNCTIONS_H