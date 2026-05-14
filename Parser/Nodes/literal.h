#ifndef LITERAL_H
#define LITERAL_H

#include "expr.h"

class Literal : public Expr 
{
    private:
    std::variant<bool, double, std::string, std::monostate> value;

    public:
    Literal(std::variant<bool, double, std::string, std::monostate> value);
    std::any accept(Visitor& visitor) const override;
    const std::variant<bool, double, std::string, std::monostate>& getValue() const;

};

#endif