
#include <string>
#include "visitor.h"

using std::string;

class ASTPrinter : public Visitor
{
    private:
    string print(Expr n) {
        return std::any_cast<string>(n.accept(*this));
    }

    public:
    void visitBinary(Binary b) override;
};