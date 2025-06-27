#ifndef EXPR_H
#define EXPR_H

#include "node.h"
#include "../../Lexer/token.h"

class Expr : public Node {
    private:
    public:
    virtual std::any accept(NodeVisitor& visitor) = 0;
};
#endif