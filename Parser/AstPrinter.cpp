
#include "AstPrinter.h"
#include "expr.h"

std::string ASTPrinter::print(Expr &expr)
{
    return std::any_cast<std::string>(expr.accept(*this));
}
