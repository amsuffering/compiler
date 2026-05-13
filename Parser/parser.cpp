#include <iostream>
#include "parser.h"

Parser::Parser(vector<Token> tokens) : tokens(std::move(tokens)) {}
