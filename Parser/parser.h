#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"

class Parser {
    private:
    const vector<Token> tokens;
    int current = 0;

    public:
    Parser(vector<Token> tokens);
};

#endif