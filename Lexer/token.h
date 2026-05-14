#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>

enum class TokenType {
    // SINGLE CHARACTER TOKENS
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    // ONE OR TWO CHARACTER TOKENS
    BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

    // LITERALS
    IDENTIFIER, STRING, NUMBER,

    // KEYWORDS
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    // NONE
    NONE,

    EoF
};

std::string typeToString(TokenType type);

class Token {
    private:
    const TokenType type;
    const std::string lexeme;
    const std::variant<bool, double, std::string, std::monostate> literal;
    const int line;

    public:
    Token(TokenType type, std::string lexeme, std::variant<bool, double, std::string, std::monostate> literal, int line);
    TokenType getType() const;
    std::string getLexeme() const;
    std::variant<bool, double, std::string, std::monostate> getLiteral() const;
    int getLine() const;
    std::string tokenToString() const;
};

#endif
