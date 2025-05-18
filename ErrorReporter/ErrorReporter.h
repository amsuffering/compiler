#ifndef ERRORREPORTER_H
#define ERRORREPORTER_H

#include <string>

class ErrorReporter {
    private:
    bool e;
    void report(int line, std::string where, std::string message);

    public:
    ErrorReporter();
    void error(int line, std::string message);
    bool hadError();
    void hadError(bool hadError);
};


#endif