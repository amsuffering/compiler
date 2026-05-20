#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include <string>
#include "expression.h"

class ASTPrinter : public Visitor
{
    private:
    std::string parenthesize(std::string name, std::initializer_list<const Expr*> exprs);

    public:
    std::string print(Expr &expr);
    std::any visitBinary(const Binary& binary);
    std::any visitGrouping(const Grouping& grouping);
    std::any visitLiteral(const Literal& literal);
    std::any visitUnary(const Unary& unary);
};

#endif
