
#include <string>
#include "nodeVisitor.h"

using std::string;

class ASTPrinter : public NodeVisitor{
    private:
    string print(Node n) {
        return std::any_cast<string>(n.accept(*this));
    }

    public:
    string visitBinaryExpr();
};