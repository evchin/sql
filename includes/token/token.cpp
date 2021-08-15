/*
 * Author: Evelyn Chin
 * Project: STokenizer.
 * Purpose: Apply token encoding to any given string.
 * File Purpose: Implementation of Token struct
 */

#include "token.h"

Token::Token()
{
    _token = "";
    _type = -1;
}

Token::Token(string token, int type)
{
    _token = token;
    _type = type;
}

Token::Token(char token, int type)
{
    _token = token;
    _type = type;
}

string Token::type_string()
{
    return TOKEN_TYPE_STRINGS[_type];
}

ostream& operator<<(ostream& out, Token const& token)
{
    out << "|" << token._token << "|";
    return out;
}

int Token::type()
{
    return _type;
}

string Token::token_str()
{
    return _token;
}