#include <iostream>
#include "ErrorReporter.h"

void ErrorReporter::report(int line, std::string where, std::string message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
    hadError(true);
}

ErrorReporter::ErrorReporter() : e(false) {}

void ErrorReporter::error(int line, std::string message)
{
    report(line, "", message);
}

bool ErrorReporter::hadError()
{
    return this->e;
}

void ErrorReporter::hadError(bool hadError) {
    this->e = hadError;
}