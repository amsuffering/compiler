#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "expression.h"
#include "ErrorReporter.h"
#include <memory>
#include <stdexcept>

class ParseError : public std::runtime_error {
    public:
    ParseError() : std::runtime_error("parse error") {};
};
class Parser {
    private:
    const std::vector<Token> tokens;
    int current = 0;
    ErrorReporter& reporter;

    // helper methods
    bool match(std::initializer_list<TokenType> types);
    bool check(TokenType type);
    Token advance();
    bool isAtEnd();
    Token peek();
    Token previous();
    Token consume(TokenType type, std::string message);
    ParseError error(Token token, std::string message);
    void synchronize();

    // grammar rules
    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> term();
    std::unique_ptr<Expr> factor();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> primary();

    public:
    Parser(std::vector<Token> tokens, ErrorReporter& reporter);
    std::unique_ptr<Expr> parse();
};

#endif