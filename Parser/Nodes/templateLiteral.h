#ifndef TEMPLATELITERAL_H
#define TEMPLATELITERAL_H

#include "literal.h"
#include "visitor.h"
#include <any>

template <typename T>
class LiteralTemplate : public Literal
{
    private:
    T value;

    public:
    LiteralTemplate(T value) : value(value) {}
    std::any accept(Visitor &v) override { return v.visitLiteral(*this); }
    std::any getValue() const override { return value; }
    T getTypedValue() const { return value; }
};

#endif