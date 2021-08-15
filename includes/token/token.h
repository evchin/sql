/*
 * Author: Evelyn Chin
 * Project: STokenizer.
 * Purpose: Apply token encoding to any given string.
 * File Purpose: Interface of Token struct
 */

#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include "../constants/constants.h"
using namespace std;

struct Token
{
public:
    Token();
    Token(string token, int type);
    Token(char token, int type);
    int type();
    string type_string();
    string token_str();
    friend ostream& operator<<(ostream& out, Token const& token);
private:
    string _token;
    int _type;
};

#endif // TOKEN_H