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
    Unary(Token op, std::unique_ptr<Expr> right);
    std::any accept(Visitor &v) const override;
    const Token& getOp() const;
    const Expr& getRight() const;
};

#endif