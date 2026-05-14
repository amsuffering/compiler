#include "literal.h"
#include "visitor.h"

Literal::Literal(std::variant<bool, double, std::string, std::monostate> value) : value(value) {}

std::any Literal::accept(Visitor &visitor) const
{
    return visitor.visitLiteral(*this);
}

const std::variant<bool, double, std::string, std::monostate>& Literal::getValue() const
{
    return this->value;
}
