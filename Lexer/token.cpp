#include "token.h"
#include <sstream>
#include <iomanip>

static std::string formatDouble(double v)
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
    switch (type) {
        // SINGLE CHARACTER TOKENS
        case TokenType::LEFT_PAREN: return "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return "RIGHT_PAREN";
        case TokenType::LEFT_BRACE: return "LEFT_BRACE";
        case TokenType::RIGHT_BRACE: return "RIGHT_BRACE";
        case TokenType::COMMA: return "COMMA";
        case TokenType::DOT: return "DOT";
        case TokenType::MINUS: return "MINUS";
        case TokenType::PLUS: return "PLUS";
        case TokenType::SEMICOLON: return "SEMICOLON";
        case TokenType::SLASH: return "SLASH";
        case TokenType::STAR: return "STAR";

        // ONE OR TWO CHARACTER TOKENS
        case TokenType::BANG: return "BANG";
        case TokenType::BANG_EQUAL: return "BANG_EQUAL";
        case TokenType::EQUAL: return "EQUAL";
        case TokenType::EQUAL_EQUAL: return "EQUAL_EQUAL";
        case TokenType::GREATER: return "GREATER";
        case TokenType::GREATER_EQUAL: return "GREATER_EQUAL";
        case TokenType::LESS: return "LESS";
        case TokenType::LESS_EQUAL: return "LESS_EQUAL";

        // LITERALS
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::STRING: return "STRING";
        case TokenType::NUMBER: return "NUMBER";

        // KEYWORDS
        case TokenType::AND: return "AND";
        case TokenType::CLASS: return "CLASS";
        case TokenType::ELSE: return "ELSE";
        case TokenType::FALSE: return "FALSE";
        case TokenType::FUN: return "FUN";
        case TokenType::FOR: return "FOR";
        case TokenType::IF: return "IF";
        case TokenType::NIL: return "NIL";
        case TokenType::OR: return "OR";
        case TokenType::PRINT: return "PRINT";
        case TokenType::RETURN: return "RETURN";
        case TokenType::SUPER: return "SUPER";
        case TokenType::THIS: return "THIS";
        case TokenType::TRUE: return "TRUE";
        case TokenType::VAR: return "VAR";
        case TokenType::WHILE: return "WHILE";

        case TokenType::EoF: return "EOF";

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
