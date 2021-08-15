/*
 * Author: Evelyn Chin
 * Project: STokenizer
 * Purpose: Apply token encoding to any given string.
 * File Purpose: Constants
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "keywords.h"

extern Keywords keywords;

// PARSER

const int PARSER_NUM_ROWS = 23;
const int PARSER_NUM_COLS = 26;

const int START_SELECT = 0;
const int START_MAKE = 9;
const int START_INSERT = 16;

// STOKENIZE CONSTANTS

const bool DEBUG = false;

const int NUM_ROWS = 12;
const int NUM_COLUMNS = 256;
const int MAX_BUFFER = 300;

const char SPACES[] = {' ', '\t', '\n', '\0'};
const char PUNC[] = "!#$%&'+-./:;?@\\^_`{|}~";
const char RELATIONALS[] = "<=>";
const char UNARIES[] = {'(', '[', ')', ']', '*', ','};

const int START_QUOTES = 0;
const int START_SYMBOL = 4;
const int START_SPACES = 6;
const int START_UNARIES = 8;
const int START_RELATIONAL = 10;

const std::string TOKEN_TYPE_STRINGS[] = 
    {"ZERO", "CREATE", "MAKE", "TABLE", "FIELDS", "INSERT", "VALUES", "SELECT", 
     "STAR", "FROM", "WHERE", "DROP", "COMMA", 
     "INTO", "SYMBOL", "SPACE", "QUOTE", "RELATIONAL", "AND", "OR", "UNARY", "START_BRACKET", "END_BRACKET", "UNKNOWN", "END"};

#endif // CONSTANTS_H