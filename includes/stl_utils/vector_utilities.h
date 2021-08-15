#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H

#include "../bplustree/map.h"

template <typename T>
vector<T> vector_intersection(vector<T>& v1, vector<T>& v2)
{
    vector<T> out;
    // if v2 is the smaller vector
    if (v1.size() > v2.size())
    {
        // create a map of v2
        Map<T, bool> exists;
        for (T obj : v2) exists[obj] = true;

        // loop over v1 and check for elemetns
        for (T obj : v1) 
            if (exists[obj]) out += obj;
    }
    else
    {
        // create a map of v1
        Map<T, bool> exists;
        for (T obj : v1) exists[obj] = true;

        // loop over v2 and check for elemetns
        for (T obj : v2) 
            if (exists[obj]) out += obj;
    }
    return out;
}

template <typename T>
vector<T> vector_union(vector<T>& v1, vector<T>& v2)
{
    vector<T> out;

    Map<T, bool> exists;
    for (T obj : v1) 
    {
        out += obj;
        exists[obj] = true;
    }
    for (T obj : v2) 
        if (!exists[obj]) 
            out += obj;

    return out;
}

#endif // VECTOR_UTILITIES_H