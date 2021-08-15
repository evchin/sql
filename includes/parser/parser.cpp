#include "parser.h"

Parser::Parser()
{
    make_table();
}

Parser::Parser(char c[])
{
    make_table();
    strcpy(buffer, c);
}

void Parser::set_string(string s)
{
    strcpy(buffer, s.c_str());
}

mmap_ss Parser::parse_tree()
{
    vector<Token> tokens;
    STokenizer stk(buffer);
    mmap_ss m;
    Token t;
    string yes = "yes";
    stk >> t;
    int state;

    switch(t.type())
    {
        case MAKE:
        case CREATE:
            state = START_MAKE;
            break;
        case SELECT:
            state = START_SELECT;
            break;
        case INSERT:
            state = START_INSERT;
            break;
        default:
            assert(false && "Reached end of switch statement in parse_tree()");
            break;
    }

    while(stk.more())
    {
        // update state
        // cout << "Upadting state from " << state << " to _table[" << state << "][" << t.type() << "] = " << _table[state][t.type()] << endl;
        state = _table[state][t.type()];

        // depending on state, add to mmap_ss
        if (t.type() != SPACE)
        {
            switch(state)
            {
                case START_SELECT + 1:
                case START_MAKE + 1:
                case START_INSERT + 1:
                    m["command"] += t.token_str();
                    break;
                case START_SELECT + 2:
                case START_SELECT + 3:
                case START_MAKE + 5:
                    m["fields"] += t.token_str();
                    break;
                case START_SELECT + 6:
                case START_MAKE + 3:
                case START_INSERT + 3:
                    m["table"] += t.token_str();
                    break;
                case START_SELECT + 7:
                    m["where"] += yes;
                    break;
                case START_SELECT + 8:
                    m["conditions"] += t.token_str();
                    break;
                case START_INSERT + 5:
                    m["values"] += t.token_str();
                    break;
                default:
                    break;
            }
        }

        t = Token();
        stk >> t;
    }

    return m;
}

void Parser::make_table()
{
    init_table();

    // SELECT
    mark(START_SELECT, SELECT, START_SELECT + 1);
    mark(START_SELECT + 1, STAR, START_SELECT + 2);
    mark(START_SELECT + 1, SYMBOL, START_SELECT + 3);
    mark(START_SELECT + 3, COMMA, START_SELECT + 4);
    mark(START_SELECT + 4, SYMBOL, START_SELECT + 3);
    mark(START_SELECT + 3, FROM, START_SELECT + 5);
    mark(START_SELECT + 2, FROM, START_SELECT + 5);
    mark(START_SELECT + 5, SYMBOL, START_SELECT + 6);
    mark(START_SELECT + 6, WHERE, START_SELECT + 7);

    for (int i = 1; i < PARSER_NUM_COLS; i++)
    {
        mark(START_SELECT + 7, i, START_SELECT + 8);
        mark(START_SELECT + 8, i, START_SELECT + 8);
    }

    mark_success(START_SELECT + 6);
    mark_success(START_SELECT + 8);

    // MAKE
    mark(START_MAKE, CREATE, START_MAKE + 1);
    mark(START_MAKE, MAKE, START_MAKE + 1);
    mark(START_MAKE + 1, TABLE, START_MAKE + 2);
    mark(START_MAKE + 2, SYMBOL, START_MAKE + 3);
    mark(START_MAKE + 3, FIELDS, START_MAKE + 4);
    mark(START_MAKE + 4, SYMBOL, START_MAKE + 5);
    mark(START_MAKE + 5, COMMA, START_MAKE + 6);
    mark(START_MAKE + 6, SYMBOL, START_MAKE + 5);
    mark_success(START_MAKE + 5);

    // INSERT
    mark(START_INSERT, INSERT, START_INSERT + 1);
    mark(START_INSERT + 1, INTO, START_INSERT + 2);
    mark(START_INSERT + 2, SYMBOL, START_INSERT + 3);
    mark(START_INSERT + 3, VALUES, START_INSERT + 4);
    mark(START_INSERT + 4, SYMBOL, START_INSERT + 5);
    mark(START_INSERT + 5, COMMA, START_INSERT + 6);
    mark(START_INSERT + 6, SYMBOL, START_INSERT + 5);
    mark_success(START_INSERT + 5);

    // ALL
    for (int i = 0; i < PARSER_NUM_ROWS; i++)
        mark(i, SPACE, i);
}

void Parser::print(int row1, int row2, int c1, int c2)
{
    // make sure rows and columns are within table
    assert(row1 < PARSER_NUM_ROWS && row2 < PARSER_NUM_ROWS);
    assert(c1 < PARSER_NUM_COLS && c2 < PARSER_NUM_COLS);

    // print header row
    cout << "     ";
    for (int j = c1; j <= c2; j++)
        cout << setw(5) << j;
    cout << endl;

    // print each row
    for (int i = row1; i <= row2; i++)
    {
        cout << setw(5) << i;
        for (int j = c1; j <= c2; j++)
            cout << setw(5) << _table[i][j];
        cout << endl;
    }
}

void Parser::init_table()
{
    for (int i = 0; i < PARSER_NUM_ROWS; i++)
    {
        for (int j = 0; j < PARSER_NUM_COLS; j++)
        {
            // if first col, set to 0. else, set to -1.
            if (j == 0) _table[i][j] = 0;
            else _table[i][j] = -1;
        }
    }
}

void Parser::mark_success(int state)
{
    assert(state < PARSER_NUM_ROWS);
    _table[state][0] = 1;
}

void Parser::mark(int current_state, int col, int next_state)
{
    assert(current_state < PARSER_NUM_ROWS && col < PARSER_NUM_COLS);
    _table[current_state][col] = next_state;
}
