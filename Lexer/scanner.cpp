#include "scanner.h"

Scanner::Scanner(std::string& source, ErrorReporter& reporter)
    : source(source), reporter(reporter), keywords({
        {"and",    TokenType::AND},
        {"class",  TokenType::CLASS},
        {"else",   TokenType::ELSE},
        {"false",  TokenType::FALSE},
        {"for",    TokenType::FOR},
        {"fun",    TokenType::FUN},
        {"if",     TokenType::IF},
        {"nil",    TokenType::NIL},
        {"or",     TokenType::OR},
        {"print",  TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super",  TokenType::SUPER},
        {"this",   TokenType::THIS},
        {"true",   TokenType::TRUE},
        {"var",    TokenType::VAR},
        {"while",  TokenType::WHILE}
    }) {}

std::vector<Token> Scanner::scanTokens()
{
    while(!isAtEnd()) {
        start = current;
        scanToken();
    }
    tokens.push_back(Token(TokenType::EoF, "", std::monostate{}, line));
    return tokens;
}

bool Scanner::isAtEnd()
{
    return static_cast<size_t>(current) >= source.length();
}

void Scanner::scanToken()
{
    char c = advance();
    switch (c) {
        // single characters are easy. if you see one just add the token
        case '(': addToken(TokenType::LEFT_PAREN); break;
        case ')': addToken(TokenType::RIGHT_PAREN); break;
        case '{': addToken(TokenType::LEFT_BRACE); break;
        case '}': addToken(TokenType::RIGHT_BRACE); break;
        case ',': addToken(TokenType::COMMA); break;
        case '.': addToken(TokenType::DOT); break;
        case '-': addToken(TokenType::MINUS); break;
        case '+': addToken(TokenType::PLUS); break;
        case ';': addToken(TokenType::SEMICOLON); break;
        case '*': addToken(TokenType::STAR); break;

        // operators we have the check the second character e.g. if we see  '!' at i then we have to check if i+1 is '=' to see if we add ! token or != token
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;

        // '/' is complicated because of comments ('//')
        case '/':
            if(match('/')) {
                // comment goes till end of line or file
                while(peek() != '\n' && !isAtEnd()) advance();
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        // characters we ignore (spaces, tabs, cartridge)
        case ' ':
        case '\r':
        case '\t':
            break;
        // increment line for newline
        case '\n':
            line++;
            break;

        // String Literal
        case '"': stringLit(); break;

        default:
            if (isdigit(c)) {
                numberLit();
            } else if (isalpha(c) || c == '_') {
                identifier();
            } else {
                reporter.error(line, "Unexpected Character.");
            }
    }
}

char Scanner::advance() // consumes
{
    return source.at(current++); // read token then increment
}

void Scanner::addToken(TokenType type)
{
    addToken(type, std::monostate{});
}

void Scanner::addToken(TokenType type, std::variant<bool, double, std::string, std::monostate> literal)
{
    std::string text = source.substr(start, current - start);
    tokens.push_back(Token(type, text, literal, line));
}

bool Scanner::match(char expected)
{
    if(isAtEnd()) return false;
    if(source.at(current) != expected) return false;
    current++;
    return true;
}

char Scanner::peek()  // does not consume
{
    if(isAtEnd()) return '\0';
    return source.at(current);
}

char Scanner::peekNext()
{
    if(static_cast<size_t>(current) + 1 >= source.length()) return '\0';
    return source.at(current+1);
}

void Scanner::stringLit()
{
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') line++;
        advance();
    }

    if(isAtEnd()) {
        reporter.error(line, "Unterminated string.");
        return;
    }

    // close "
    advance();

    // Trim surrounding quotes
    std::string value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
}

void Scanner::numberLit()
{
    while(isdigit(peek())) advance();

    // check for decimal
    if (peek() == '.' && isdigit(peekNext())) {
        // consume .
        advance();

        while (isdigit(peek())) advance();
    }
    double value = std::stod(source.substr(start, current - start));
    addToken(TokenType::NUMBER, value);
}

void Scanner::identifier()
{
    while(isalnum(peek()) || peek() == '_') advance();

    std::string text = source.substr(start, current - start);
    auto search = keywords.find(text); // check if there is a keyword for text
    TokenType type = TokenType::IDENTIFIER;
    if (search != keywords.end()) type = search->second;
    addToken(type);
}

int Scanner::getCurrent()
{
    return this->current;
}

int Scanner::getLine()
{
    return this->line;
}
