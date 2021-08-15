#ifndef SQL_H
#define SQL_H

#include "../table/table.h"
#include "../parser/parser.h"

class SQL
{
public:
    SQL();
    void batch(string file, bool verbose = false);
    Table command(char* s);
    Table command(const string& s);
    vector<long> select_recnos();
private:
    Parser parser;
    Map<string, Table> tables;
    vector<long> _select_recnos;
};

#endif // SQL_H