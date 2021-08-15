#ifndef KEYWORDS_H
#define KEYWORDS_H

#include "../bplustree/map.h"

enum TOKEN_TYPES { ZERO, CREATE, MAKE, TABLE, FIELDS, INSERT, VALUES, SELECT, STAR, 
                    FROM, WHERE, DROP, COMMA, INTO,
                    SYMBOL, SPACE, QUOTE, RELATIONAL, AND, OR, UNARY, START_BRACKET, END_BRACKET, UNKNOWN, END };

struct Keywords
{
    Keywords()
    {
        keyword_map["create"] = CREATE;
        keyword_map["make"] = MAKE;
        keyword_map["table"] = TABLE;
        keyword_map["fields"] = FIELDS;
        keyword_map["insert"] = INSERT;
        keyword_map["values"] = VALUES;
        keyword_map["select"] = SELECT;
        keyword_map["*"] = STAR;
        keyword_map["from"] = FROM;
        keyword_map["where"] = WHERE;
        keyword_map["drop"] = DROP;
        keyword_map["and"] = AND;
        keyword_map["or"] = OR;
        keyword_map["into"] = INTO;
        keyword_map["CREATE"] = CREATE;
        keyword_map["MAKE"] = MAKE;
        keyword_map["TABLE"] = TABLE;
        keyword_map["FIELDS"] = FIELDS;
        keyword_map["INSERT"] = INSERT;
        keyword_map["VALUES"] = VALUES;
        keyword_map["SELECT"] = SELECT;
        keyword_map["FROM"] = FROM;
        keyword_map["WHERE"] = WHERE;
        keyword_map["DROP"] = DROP;
        keyword_map["AND"] = AND;
        keyword_map["OR"] = OR;
        keyword_map["INTO"] = INTO;
        keyword_map[","] = COMMA;
        keyword_map["("] = START_BRACKET;
        keyword_map["["] = START_BRACKET;
        keyword_map[")"] = END_BRACKET;
        keyword_map["]"] = END_BRACKET;
        keyword_map["="] = RELATIONAL;
        keyword_map["<"] = RELATIONAL;
        keyword_map[">"] = RELATIONAL;
        keyword_map["<="] = RELATIONAL;
        keyword_map[">="] = RELATIONAL;
    }

    bool contains(string key) const
    {
        return keyword_map.contains(key);
    }

    TOKEN_TYPES& operator[](const string& key)
    {
        return keyword_map[key];
    }

    Map<string, TOKEN_TYPES> keyword_map;
};

#endif