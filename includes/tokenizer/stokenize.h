/*
 * Author: Evelyn Chin
 * Project: STokenizer.
 * Purpose: Apply token encoding to any given string.
 * File Purpose: Interface of class STokenizer
 */

#ifndef STOKENIZE_H
#define STOKENIZE_H

#include "../token/token.h"
#include "../bplustree/map.h"

class STokenizer
{
public:
    // PURPOSE: Default constructor
    STokenizer();
    // PURPOSE: sets up table and copies s into _buffer
    STokenizer(char s[]);
    // PURPOSE: return true if there are more chars to read
    bool more();
    // PURPOSE: return true if there are no more tokens
    bool done();
    // PURPOSE: get next token
    friend STokenizer& operator>>(STokenizer& stk, Token& token);
    // PURPSOSE: set str as the input string
    void set_string(char str[]);

private:
    int _table[NUM_ROWS][NUM_COLUMNS];
    char _buffer[MAX_BUFFER];
    int _pos = 0;

    // PURPOSE: create and set up table
    void make_table();
    // PURPOSE: return boolean indicating valid token
    bool get_token(int state, string &token);
    // PURPOSE: initialize all states as non-successes and all next_states to -1
    void init_table();
    // PURPOSE: set up table for symbol tokens
    void setup_symbol_token();
    // PURPOSE: set up table for space tokens
    void setup_space_token();
    // PURPOSE: set up table for unary tokens
    void setup_unary_token();
    // PURPOSE: set up table for relational tokens
    void setup_relational_token();
    // PURPOSE: set up table for quotation tokens
    void setup_quote_token();
    // PURPOSE: Mark state 'state' to become a success state
    void mark_success(int state);
    // PURPOSE: Mark current_state to go to next_state if character c received
    void mark(int current_state, char c, int next_state);
    // PURPOSE: Print rows row1 to row2 and columns c1 to c2 inclusive
    void print(int row1, int row2, char c1, char c2);
    // PURPOSE: return if state is a success state
    bool is_success_state(int state);
    // PURPOSE: return char at current pos of buffer
    char get_pos_char();
    // PURPOSE: return end token and set _pos to -1
    Token get_end_token();
    // PURPOSE: return unknown token and update _pos by one
    Token get_unknown_token();
    // PURPOSE: set keyword map
    void set_keywords();
};

#endif // STOKENIZE_H