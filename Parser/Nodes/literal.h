#ifndef LITERAL_H
#define LITERAL_H

#include "expr.h"

class Literal : public Expr 
{
    private:
    std::variant<bool, double, string, monostate> value;

    public:
    Literal(std::variant<bool, double, string, monostate> value);
    std::any accept(Visitor& visitor) override;
    const std::variant<bool, double, string, monostate>& getValue() const;

};

#endif