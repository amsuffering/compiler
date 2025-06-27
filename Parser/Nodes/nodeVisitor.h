#ifndef NODEVISITOR_H
#define NODEVISITOR_H

#include "node.h"

class NodeVisitor {
    public:
    virtual void visit(Node& n) = 0;
};

#endif