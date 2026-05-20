#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "expression.h"
#include <memory>

class Parser {
    private:
    const std::vector<Token> tokens;
    int current = 0;

    // helper methods
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Token consume(TokenType type, std::string message);

    // grammar rules
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    public:
    Parser(std::vector<Token> tokens);
};

#endif