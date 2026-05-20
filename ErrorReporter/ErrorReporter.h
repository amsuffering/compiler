#ifndef ERRORREPORTER_H
#define ERRORREPORTER_H

#include "token.h"
#include <string>

class ErrorReporter {
    private:
    bool errorHappened;
    void report(int line, std::string where, std::string message);

    public:
    ErrorReporter();
    void error(int line, std::string message);
    void error(Token token, std::string message);
    bool hadError();
    void hadError(bool hadError);
};


#endif