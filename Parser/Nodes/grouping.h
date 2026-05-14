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
    std::any accept(Visitor& visitor) const override;
    const Expr& getExpression() const;
};

#endif