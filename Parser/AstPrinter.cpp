#include "AstPrinter.h"

std::string ASTPrinter::parenthesize(std::string name, std::initializer_list<const Expr*> exprs)
{
    std::string result;
    result.append("(").append(name);
    for (const Expr* expr : exprs) {
          result.append(" ");
          result.append(std::any_cast<std::string>(expr->accept(*this)));
    }
    result.append(")");
    return result;
}

std::string ASTPrinter::print(Expr &expr)
{
    return std::any_cast<std::string>(expr.accept(*this));
}

std::any ASTPrinter::visitBinary(const Binary &binary)
{
    return parenthesize(binary.getOp().getLexeme(), {&binary.getLeft(), &binary.getRight()});
}

std::any ASTPrinter::visitGrouping(const Grouping &grouping)
{
    return parenthesize("group", {&grouping.getExpression()});
}

std::any ASTPrinter::visitLiteral(const Literal& literal)
{
    return std::visit([](auto&& v) -> std::string {
        using T = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<T, std::string>)   return v;
        else if constexpr (std::is_same_v<T, double>)   return std::to_string(v);
        else if constexpr (std::is_same_v<T, bool>)     return v ? "true" : "false";
        else                                            return "nil";
    }, literal.getValue());
}

std::any ASTPrinter::visitUnary(const Unary &unary)
{
    return parenthesize(unary.getOp().getLexeme(), {&unary.getRight()});
}
