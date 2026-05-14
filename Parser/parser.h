#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"

class Parser {
    private:
    const std::vector<Token> tokens;
    int current = 0;

    public:
    Parser(std::vector<Token> tokens);
};

#endif