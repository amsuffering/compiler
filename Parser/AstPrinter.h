#ifndef ASTPRINTER_H
#define ASTPRINTER_H

#include <string>
#include<vector>
#include "visitor.h"

class Expr;

class ASTPrinter : public Visitor
{
    private:
    std::string print(Expr &expr);
    std::string parenthesize(std::string name, std::vector<Expr> expr);

    public:
    std::any visitBinary(const Binary& binary);
    std::any visitGrouping(const Grouping& grouping);
    std::any visitLiteral(const Literal& literal);
    std::any visitUnary(const Unary& unary);
};

#endif
