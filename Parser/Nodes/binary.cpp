#include "binary.h"

Binary::Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right) : left(std::move(left)), op(op), right(std::move(right)) {}

std::any Binary::accept(Visitor &v)
{
    return std::any();
}