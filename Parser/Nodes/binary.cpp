#include "binary.h"
#include "visitor.h"

Binary::Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : 
    left(std::move(left)), op(op), right(std::move(right)) {}

std::any Binary::accept(Visitor &visitor)
{
    return visitor.visitBinary(*this);
}

const Expr &Binary::getLeft() const
{
    return *this->left;
}

const Token &Binary::getOp() const
{
    return op;
}

const Expr &Binary::getRight() const
{
    return *this->right;
}
