#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <variant>
using std::string, std::variant, std::monostate;

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

string typeToString(TokenType type);

class Token {
    private:
    const TokenType type;
    const string lexeme;
    const variant<bool, int, double, string, monostate> literal;
    const int line;

    public:
    Token(TokenType type, string lexeme, variant<bool, int, double, string, monostate> literal, int line); // parameterized constructor
    string getLexeme();
    variant<bool, int, double, string, monostate> getLiteral();
    int getLine();
    string tokenToString();
};

#endif