#include "grouping.h"

Grouping::Grouping(std::unique_ptr<Expr> expression) : expression(std::move(expression)) {}
