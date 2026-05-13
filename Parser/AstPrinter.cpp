
#include "AstPrinter.h"
#include "expr.h"

string ASTPrinter::print(Expr &expr)
{
    return std::any_cast<string>(expr.accept(*this));
}
