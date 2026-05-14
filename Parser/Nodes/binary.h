#ifndef BINARY_H
#define BINARY_H
#include "expr.h"
#include <memory>

class Binary : public Expr 
{
    private:
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

    public:
    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right);
    std::any accept(Visitor& v) const override;
    const Expr& getLeft() const;
    const Token& getOp() const;
    const Expr& getRight() const;
};

#endif