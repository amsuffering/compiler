#ifndef EXPR_H
#define EXPR_H

#include "token.h"
#include "visitor.h"
#include <any>

class Expr 
{
    public:
    virtual std::any accept(Visitor& visitor) = 0;
};

#endif