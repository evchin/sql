#ifndef PARSER_H
#define PARSER_H

#include "../table/typedefs.h"
#include "../tokenizer/stokenize.h"
#include <cstring>
#include <cassert>

class Parser
{
public:
    Parser();
    Parser(char c[]);
    mmap_ss parse_tree();
    void set_string(string s);
private:
    void make_table();
    void init_table();
    void mark_success(int state);
    void mark(int current_state, int col, int next_state);
    void print(int row1, int row2, int c1, int c2);

    const static int CAPACITY = 300;
    char buffer[CAPACITY];
    int _table[PARSER_NUM_ROWS][PARSER_NUM_COLS];
};

#endif // PARSER_H