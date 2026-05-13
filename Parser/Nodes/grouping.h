#ifndef GROUPING_H
#define GROUPING_H

#include "expr.h"
#include <memory>

class Grouping : public Expr 
{
    private:
    std::unique_ptr<Expr> expression;

    public:
    Grouping(std::unique_ptr<Expr> expression);
    virtual std::any accept(Visitor& visitor) override;
    const Expr& getExpression() const;
};

#endif