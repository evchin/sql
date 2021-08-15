/*
 * Author: Evelyn Chin
 * Project: STokenizer.
 * Purpose: Apply token encoding to any given string.
 * File Purpose: Implementation of class STokenizer
 */

#include <iomanip>
#include <cassert>
#include "stokenize.h"

// PURPOSE: default constructor
STokenizer::STokenizer() 
{
    char s[1] = {'\0'};
    make_table();
    set_string(s);
}

// PURPOSE: sets up table and copies s into _buffer
STokenizer::STokenizer(char s[])
{
    make_table();
    set_string(s);
}

// PURPOSE: create and set up table
void STokenizer::make_table()
{
    init_table();
    setup_symbol_token();
    setup_space_token();
    setup_unary_token();
    setup_relational_token();
    setup_quote_token();
}

// PURPSOSE: set str as the input string
void STokenizer::set_string(char str[])
{
    for (int i = 0; i < MAX_BUFFER - 1; i++)
    {
        _buffer[i] = str[i];
        if (str[i] == '\0') break;
        if (i == MAX_BUFFER - 2)
            _buffer[i + 1] = '\0';
    }
    _pos = 0;
}

// PURPOSE: return boolean indicating valid token
bool STokenizer::get_token(int state, string &token)
{
    if (get_pos_char() < 0) return false;

    token = "";
    int init_pos = _pos;
    char c = _buffer[_pos];
    int last_successful_pos = -1;

    while (c != '\0')
    {
        if (DEBUG) print(state, state + 1, c - 1, c + 1);
        state = _table[state][c];
        if (state == -1) break;
        if (is_success_state(state))
            last_successful_pos = _pos;
        c = _buffer[++_pos];
    }

    if (DEBUG) 
    {
        cout << "Current Token String: " << token << endl;
        cout << "Current State: " << state << endl;
        cout << "Current Position: " << _pos << endl;
        cout << "Buffer[POS]: " << _buffer[_pos] << endl;
        cout << "Last Successful Position: " << last_successful_pos << endl;
    }

    for (int i = init_pos; i <= last_successful_pos; i++)
        token += _buffer[i];

    if (last_successful_pos != -1)
    {
        _pos = last_successful_pos + 1;
        return true;
    }
    _pos = init_pos;
    return false;
}

// PURPOSE: get next token
STokenizer& operator>>(STokenizer& stk, Token& token)
{
    string tk = "";
    if (stk.get_token(START_QUOTES, tk))
    {
        if (DEBUG) cout << "FOUND QUOTE TOKEN" << endl;
        tk = tk.substr(1, tk.length() - 2);     // remove quotes
        token = Token(tk, SYMBOL);
    }
    else if (stk.get_token(START_SYMBOL, tk))
    {
        if (DEBUG) cout << "FOUND SYMBOL TOKEN" << endl;
        int type = SYMBOL;
        if (keywords.contains(tk))
            type = keywords[tk];
        token = Token(tk, type);
    }
    else if (stk.get_token(START_SPACES, tk))
    {
        if (DEBUG) cout << "FOUND SPACE TOKEN" << endl;
        token = Token(tk, SPACE);
    }
    else if (stk.get_token(START_UNARIES, tk))
    {
        if (DEBUG) cout << "FOUND UNARY TOKEN" << endl;
        int type = UNARY;
        if (keywords.contains(tk))
            type = keywords[tk];
        token = Token(tk, type);
    }
    else if (stk.get_token(START_RELATIONAL, tk))
    {
        if (DEBUG) cout << "FOUND PUNCTUATION TOKEN" << endl;
        token = Token(tk, RELATIONAL);
    }
    else
    {
        if (stk.get_pos_char() == '\0') 
        {
            token = stk.get_end_token();
            if (DEBUG) cout << "RETURNING END TOKEN " << token << endl;
        }
        else
        {
            if (DEBUG) cout << "RETURNING UNKNOWN TOKEN" << endl;
            token = stk.get_unknown_token();
        } 
    }
    return stk;
}

// PURPOSE: set up table for word tokens
void STokenizer::setup_symbol_token()
{
    // ALPHA
    for (int i = 'A'; i <= 'Z'; i++)
    {
        // 0 -> 1 | 1 -> 1 when A-Z
        mark(START_SYMBOL, i, START_SYMBOL + 1);
        mark(START_SYMBOL + 1, i, START_SYMBOL + 1);
    }
    for (int i = 'a'; i <= 'z'; i++)
    {
        // 0 -> 1 | 1 -> 1 when a-z
        mark(START_SYMBOL, i, START_SYMBOL + 1);
        mark(START_SYMBOL + 1, i, START_SYMBOL + 1);
    }

    // NUMBER
    for (int i = '0'; i <= '9'; i++)
    {
        // 0 -> 1 | 1 -> 1 | 2 -> 3 | 3 -> 3 when 0-9
        mark(START_SYMBOL, i, START_SYMBOL + 1);
        mark(START_SYMBOL + 1, i, START_SYMBOL + 1);
    }

    // PUNC
    for (int i = 0; i < 23; i++)
    {
        // 0 -> 1 and 1 -> 1 when in PUNC[]
        mark(START_SYMBOL, PUNC[i], START_SYMBOL + 1);
        mark(START_SYMBOL + 1, PUNC[i], START_SYMBOL + 1);
    }

    mark_success(START_SYMBOL + 1);
}

// PURPOSE: set up table for space tokens
void STokenizer::setup_space_token()
{
    // 0 -> 1 and 1 -> 1 when sp, \t, or \n
    for (int i = 0; i < 3; i++)
    {
        mark(START_SPACES, SPACES[i], START_SPACES + 1);
        mark(START_SPACES + 1, SPACES[i], START_SPACES + 1);
    }
    mark_success(START_SPACES + 1);
}

// PURPOSE: set up table for unary tokens
void STokenizer::setup_unary_token()
{
    // 0 -> 1 and 1 -> 1 when sp, \t, or \n
    for (int i = 0; i < 6; i++)
        mark(START_UNARIES, UNARIES[i], START_UNARIES + 1);
    mark_success(START_UNARIES + 1);
}

// PURPOSE: set up table for relational tokens
void STokenizer::setup_relational_token()
{
    // 0 -> 1 and 1 -> 1 when sp, \t, or \n
    for (int i = 0; i < 3; i++)
    {
        mark(START_RELATIONAL, RELATIONALS[i], START_RELATIONAL + 1);
        mark(START_RELATIONAL + 1, RELATIONALS[i], START_RELATIONAL + 1);
    }
    // state 1 = success
    mark_success(START_RELATIONAL + 1);
}

// PURPOSE: set up table for quotation tokens
void STokenizer::setup_quote_token()
{
    // 0 -> 1 and 1 -> 1 when sp, \t, or \n
    mark(START_QUOTES, '\"', START_QUOTES + 1);

    // ALPHA
    for (int i = 'A'; i <= 'Z'; i++)
    {
        // 1 -> 2 | 2 -> 2 when A-Z
        mark(START_QUOTES + 1, i, START_QUOTES + 2);
        mark(START_QUOTES + 2, i, START_QUOTES + 2);
    }
    for (int i = 'a'; i <= 'z'; i++)
    {
        // 1 -> 2 | 2 -> 2 when A-Z
        mark(START_QUOTES + 1, i, START_QUOTES + 2);
        mark(START_QUOTES + 2, i, START_QUOTES + 2);
    }

    // NUMBER
    for (int i = '0'; i <= '9'; i++)
    {
        // 1 -> 2 | 2 -> 2 when A-Z
        mark(START_QUOTES + 1, i, START_QUOTES + 2);
        mark(START_QUOTES + 2, i, START_QUOTES + 2);
    }

    // PUNC
    for (int i = 0; i < 23; i++)
    {
        // 1 -> 2 | 2 -> 2 when A-Z
        mark(START_QUOTES + 1, PUNC[i], START_QUOTES + 2);
        mark(START_QUOTES + 2, PUNC[i], START_QUOTES + 2);
    }

    // SPACES
    for (int i = 0; i < 4; i++)
    {
        // 1 -> 2 | 2 -> 2 when A-Z
        mark(START_QUOTES + 1, SPACES[i], START_QUOTES + 2);
        mark(START_QUOTES + 2, SPACES[i], START_QUOTES + 2);
    }

    mark(START_QUOTES + 2, '\"', START_QUOTES + 3);
    mark_success(START_QUOTES + 3);
}

// PURPOSE: initialize all states as non-successes and all next_states to -1
void STokenizer::init_table()
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < NUM_COLUMNS; j++)
        {
            // if first col, set to 0. else, set to -1.
            if (j == 0) _table[i][j] = 0;
            else _table[i][j] = -1;
        }
    }
}

// PURPOSE: Mark state 'state' to become a success state
void STokenizer::mark_success(int state)
{
    assert(state < NUM_ROWS);
    _table[state][0] = 1;
}

// PURPOSE: Mark current_state to go to next_state if character c received
void STokenizer::mark(int current_state, char c, int next_state)
{
    assert(current_state < NUM_ROWS && c < NUM_COLUMNS);
    _table[current_state][c] = next_state;
}

// PURPOSE: Print rows row1 to row2 and columns c1 to c2 inclusive
void STokenizer::print(int row1, int row2, char c1, char c2)
{
    // make sure rows and columns are within table
    assert(row1 < NUM_ROWS && row2 < NUM_ROWS);
    assert(c1 < NUM_COLUMNS && c2 < NUM_COLUMNS);

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

// PURPOSE: return if state is a success state
bool STokenizer::is_success_state(int state)
{
    assert(state < NUM_ROWS && state >= 0);
    return _table[state][0] == 1;
}

// PURPOSE: return char at current pos of buffer
char STokenizer::get_pos_char()
{
    return _buffer[_pos];
}

// PURPOSE: return end token and set _pos to -1
Token STokenizer::get_end_token()
{
    _pos = -1;
    return Token("\0", END);
}

// PURPOSE: return unknown token and update _pos by one
Token STokenizer::get_unknown_token()
{
    char c = get_pos_char();
    Token tk(c, UNKNOWN);
    _pos++;
    return tk;
}

// PURPOSE: return true if there are more chars to read
bool STokenizer::more()
{
    return _pos != -1;
}

// PURPOSE: return true if there are no more tokens
bool STokenizer::done()
{
    return _pos == -1;
}