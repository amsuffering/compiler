#ifndef NODE_H
#define NODE_H

#include <any>
#include "nodeVisitor.h"

class Node {
    public:
    virtual std::any accept(NodeVisitor& visitor) = 0;
};

#endif