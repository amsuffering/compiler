#ifndef EXPR_H
#define EXPR_H

#include "token.h"
#include <any>

class Visitor;
class Expr 
{
    public:
    virtual std::any accept(Visitor& visitor) const = 0;
};

#endif