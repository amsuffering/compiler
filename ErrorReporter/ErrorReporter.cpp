#include <iostream>
#include "ErrorReporter.h"

void ErrorReporter::report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError(true);
}

ErrorReporter::ErrorReporter() : errorHappened(false) {}

void ErrorReporter::error(int line, std::string message)
{
    report(line, "", message);
}

void ErrorReporter::error(Token token, std::string message)
{
    if (token.getType() == TokenType::EoF) {
        report(token.getLine(), " at end", message);
    } else {
        report(token.getLine(), " at '" + token.getLexeme() + "'", message);
    }
}

bool ErrorReporter::hadError()
{
    return this->errorHappened;
}

void ErrorReporter::hadError(bool hadError) {
    this->errorHappened = hadError;
}