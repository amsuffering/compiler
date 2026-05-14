#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "ErrorReporter.h"
#include <vector>
#include <unordered_map>

class Scanner {
    private:
    const std::string source;
    std::vector<Token> tokens;
    ErrorReporter& reporter;
    int start = 0;
    int current = 0;
    int line = 1;
    std::unordered_map<std::string, TokenType> keywords;
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<bool, double, std::string, std::monostate> literal);
    bool match(char expected);
    char peek();
    char peekNext();
    void stringLit();
    void numberLit();
    void identifier();

    public:
    Scanner(std::string& source, ErrorReporter& reporter);
    std::vector<Token> scanTokens();
    int getLine();
    int getCurrent();
};

#endif
