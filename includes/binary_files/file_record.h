#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include "../bplustree/btree_array_funcs.h"
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
using namespace std;

struct FileRecord
{
    // constructor
    FileRecord()
    {
        _record[0] = '\0';
        recno = -1;
    }

    // constructor with char array
    FileRecord(char str[])
    {
        strncpy(_record, str, MAX);
    }

    // constructor with string
    FileRecord(string s)
    {
        strncpy(_record, s.c_str(), MAX);
    }

    // constructor with vector of strings
    FileRecord(vector<string> v)
    {
        string all = "";
        for(int i = 0; i < v.size() - 1; i++) 
            all += v[i] + ", ";
        all += v[v.size() - 1];
        strncpy(_record, all.c_str(), MAX);
    }

    // returns the record number
    long write(fstream& outs);
    
    // returns the number of bytes | read = MAX, or zero if read passed the end of file
    long read(fstream& ins, long recno);

    // return current stored data as vectorstr
    vector<string> to_vectorstr();

    // print overload
    friend ostream& operator<<(ostream& outs,const FileRecord& r);

    static const int MAX = 500;
    int recno;
    char _record[MAX+1];
};

#endif // FILE_RECORD_H