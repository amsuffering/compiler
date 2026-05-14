#include "unary.h"
#include "visitor.h"

Unary::Unary(Token op, std::unique_ptr<Expr> right) : op(op), right(std::move(right)) {}

std::any Unary::accept(Visitor &v) const
{
    return v.visitUnary(*this);
}

const Token &Unary::getOp() const
{
    return op;
}

const Expr &Unary::getRight() const
{
    return *this->right;
}
