#include "token.h"
#include <sstream>
#include <iomanip>

std::string formatDouble(double v)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << v;
    std::string s = oss.str();
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (!s.empty() && s.back() == '.') s += '0';
    return s;
}

std::string typeToString(TokenType type)
{
    using enum TokenType;
    switch (type) {
        // SINGLE CHARACTER TOKENS
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case MINUS: return "MINUS";
        case PLUS: return "PLUS";
        case SEMICOLON: return "SEMICOLON";
        case SLASH: return "SLASH";
        case STAR: return "STAR";

        // ONE OR TWO CHARACTER TOKENS
        case BANG: return "BANG";
        case BANG_EQUAL: return "BANG_EQUAL";
        case EQUAL: return "EQUAL";
        case EQUAL_EQUAL: return "EQUAL_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";

        // LITERALS
        case IDENTIFIER: return "IDENTIFIER";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";

        // KEYWORDS
        case AND: return "AND";
        case CLASS: return "CLASS";
        case ELSE: return "ELSE";
        case FALSE: return "FALSE";
        case FUN: return "FUN";
        case FOR: return "FOR";
        case IF: return "IF";
        case NIL: return "NIL";
        case OR: return "OR";
        case PRINT: return "PRINT";
        case RETURN: return "RETURN";
        case SUPER: return "SUPER";
        case THIS: return "THIS";
        case TRUE: return "TRUE";
        case VAR: return "VAR";
        case WHILE: return "WHILE";

        case EoF: return "EOF";

        default: return "NONE";
    }
}

Token::Token(TokenType type, std::string lexeme, std::variant<bool, double, std::string, std::monostate> literal, int line) : type(type), lexeme(lexeme), literal(literal), line(line) {}

TokenType Token::getType() const
{
    return this->type;
}

std::string Token::getLexeme() const
{
    return this->lexeme;
}

std::variant<bool, double, std::string, std::monostate> Token::getLiteral() const
{
    return this->literal;
}

int Token::getLine() const
{
    return this->line;
}

std::string Token::tokenToString() const
{
    std::string prefix = typeToString(type) + " " + lexeme + " ";
    return std::visit([&prefix](auto&& v) -> std::string {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, std::string>)   return prefix + v;
        else if constexpr (std::is_same_v<T, double>)   return prefix + formatDouble(v);
        else if constexpr (std::is_same_v<T, bool>)     return prefix + (v ? "true" : "false");
        else                                            return prefix + "nil";
    }, this->literal);
}
