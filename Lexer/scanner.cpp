#include "scanner.h"
#include <stdexcept>

Scanner::Scanner(string& source, ErrorReporter& reporter) : source(source), reporter(reporter) {}

vector<Token> Scanner::scanTokens()
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
    return (long unsigned int) current >= source.length();
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
        if (isdigit(c)) numberLit();
        else reporter.error(line, "Unexpected Character"); break;
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

void Scanner::addToken(TokenType type, std::variant<bool, int, float, string, monostate> literal)
{
    string text = source.substr(start, current);
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
    string value = source.substr(start + 1, current -1);
    addToken(TokenType::STRING, value);
}

void Scanner::numberLit()
{
}

int Scanner::getCurrent()
{
    return this->current;
}

int Scanner::getLine()
{
    return this->line;
}