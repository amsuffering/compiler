#ifndef LITERAL_H
#define LITERAL_H

#include<expr.h>

class Literal : public Expr 
{
    public:
    virtual std::any getValue() const = 0;
};

#endif