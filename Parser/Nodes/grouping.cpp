#include "grouping.h"
#include "visitor.h"

Grouping::Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}

std::any Grouping::accept(Visitor &visitor) const
{
    return visitor.visitGrouping(*this);
}

const Expr &Grouping::getExpression() const
{
    return *this->expression;
}
