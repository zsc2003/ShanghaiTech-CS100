#ifndef EXPR_TYPE_CHECK_HPP
#define EXPR_TYPE_CHECK_HPP

#include "expr.hpp"

class TypeCheckVisitor;

/// @brief Performs type checking on the expression @c expr, including all of
/// its subexpressions.
/// @param expr The expression, which is the root of the AST.
void typeCheck(Expr &expr);

#endif // EXPR_TYPE_CHECK_HPP
