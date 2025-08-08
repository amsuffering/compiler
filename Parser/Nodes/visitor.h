#ifndef VISITOR_H
#define VISITOR_H

#include "binary.h"
#include "grouping.h"
#include "literal.h"
#include "unary.h"

class Visitor {
    public:
    virtual void visitBinary(const Binary& b) = 0;
    virtual void visitGrouping(const Grouping& g) = 0;
    virtual void visitLiteral(const Literal& l) = 0;
    virtual void visitUnary(const Unary& u) = 0;
};

#endif