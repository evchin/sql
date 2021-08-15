#ifndef TABLE_H
#define TABLE_H

#include "../binary_files/file_record.h"
#include "../binary_files/utilities.h"
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../token/token.h"
#include "../stl_utils/vector_utilities.h"
#include "typedefs.h"
#include <sstream>

const int width = 25;
extern int serial;

class Table
{
public:
    Table();
    Table(string table);
    Table(string table, vectorstr fields);
    Table(string table, vector<long> recnos);
    void insert_into(vectorstr v);
    Table select(vectorstr fields, string field, string op, string value);
    Table select(vectorstr fields, Queue<Token*> q);
    Table select(vectorstr fields, vectorstr conditions);
    Table select_all();
    Table select_fields(vectorstr fields);
    vector<long> select_recnos();
    vectorstr get_field_names();
    friend ostream& operator<<(ostream& os, const Table& t);
private:
    Queue<Token*> infix_to_postfix(vectorstr infix);
    vectorstr get_fields(string table);
    string name;
    vectorstr field_names;
    vector<long> _select_recnos;
    vector<MMap<string, long> > indices;
    Map<string, int> field_name_indices;
};

#endif // TABLE_H