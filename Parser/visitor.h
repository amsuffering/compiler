#ifndef VISITOR_H
#define VISITOR_H

#include <any>

class Binary;
class Grouping;
class Literal;
class Unary;

class Visitor {
    public:
    virtual std::any visitBinary(const Binary& binary) = 0;
    virtual std::any visitGrouping(const Grouping& grouping) = 0;
    virtual std::any visitLiteral(const Literal& literal) = 0;
    virtual std::any visitUnary(const Unary& unary) = 0;
};

#endif