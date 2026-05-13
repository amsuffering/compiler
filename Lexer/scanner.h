#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include "ErrorReporter.h"
#include <vector>
#include <map>

using std::vector;

class Scanner {
    private:
    const string source;
    vector<Token> tokens;
    ErrorReporter& reporter;
    int start = 0;
    int current = 0;
    int line = 1;
    std::map<string, TokenType> keywords;
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, std::variant<bool, double, string, monostate> literal);
    bool match(char expected);
    char peek();
    char peekNext();
    void stringLit();
    void numberLit();
    void identifier();

    public:
    Scanner(string& source, ErrorReporter& reporter);
    vector<Token> scanTokens();
    int getLine();
    int getCurrent();
};

#endif