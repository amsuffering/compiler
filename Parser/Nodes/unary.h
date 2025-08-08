#ifndef UNARY_H
#define UNARY_H

#include "expr.h"
#include <memory>

class Unary : public Expr
{
    private:
    Token op;
    std::unique_ptr<Expr> right;
    
    public:
    std::any accept(Visitor &v) override;
};

#endif