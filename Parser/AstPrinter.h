#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include <string>
#include "visitor.h"

class Expr;

using std::string;

class ASTPrinter : public Visitor
{
    private:
    string print(Expr &expr);

    public:
    std::any visitBinary(const Binary& binary);
    std::any visitGrouping(const Grouping& grouping);
    std::any visitLiteral(const Literal& literal);
    std::any visitUnary(const Unary& unary);
};

#endif
