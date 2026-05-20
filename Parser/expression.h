#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "token.h"
#include "visitor.h"
#include <memory>

class Expr
{
public:
    virtual std::any accept(Visitor& visitor) const = 0;
    virtual ~Expr() = default;
};

class Binary : public Expr
{
    std::unique_ptr<Expr> left;
    Token op;
    std::unique_ptr<Expr> right;

public:
    Binary(std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right)
        : left(std::move(left)), op(op), right(std::move(right)) {}

    std::any accept(Visitor& visitor) const override { return visitor.visitBinary(*this); }
    const Expr& getLeft()  const { return *left; }
    const Token& getOp()   const { return op; }
    const Expr& getRight() const { return *right; }
};

class Unary : public Expr
{
    Token op;
    std::unique_ptr<Expr> right;

public:
    Unary(Token op, std::unique_ptr<Expr> right)
        : op(op), right(std::move(right)) {}

    std::any accept(Visitor& visitor) const override { return visitor.visitUnary(*this); }
    const Token& getOp()   const { return op; }
    const Expr& getRight() const { return *right; }
};

class Grouping : public Expr
{
    std::unique_ptr<Expr> expression;

public:
    Grouping(std::unique_ptr<Expr> expression)
        : expression(std::move(expression)) {}

    std::any accept(Visitor& visitor) const override { return visitor.visitGrouping(*this); }
    const Expr& getExpression() const { return *expression; }
};

class Literal : public Expr
{
    std::variant<bool, double, std::string, std::monostate> value;

public:
    Literal(std::variant<bool, double, std::string, std::monostate> value)
        : value(std::move(value)) {}

    std::any accept(Visitor& visitor) const override { return visitor.visitLiteral(*this); }
    const std::variant<bool, double, std::string, std::monostate>& getValue() const { return value; }
};

#endif
