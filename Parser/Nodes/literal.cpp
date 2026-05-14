#include "literal.h"
#include "visitor.h"

Literal::Literal(std::variant<bool, double, string, monostate> value) : value(value) {}

std::any Literal::accept(Visitor &visitor)
{
    return visitor.visitLiteral(*this);
}

const std::variant<bool, double, string, monostate>& Literal::getValue() const
{
    return this->value;
}
