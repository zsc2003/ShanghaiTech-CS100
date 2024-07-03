#include <iostream>

#include "dump.hpp"
#include "expr.hpp"
#include "parse.hpp"
#include "type_check.hpp"

int main() {
  // !(x < 0) ? x + 2 : (4 * x + 5) / (-x)
  // created from Expr::create
  auto x = Expr::create<Variable>(ExprType::Float, "x");
  auto f = Expr::create<ConditionalOp>(
      Expr::create<LogicalNotOp>(Expr::create<RelationalOp>(
          OperatorKind::Less, x, Expr::create<IntegerConstant>(0))),
      Expr::create<BinaryArithOp>(OperatorKind::BinaryPlus, x,
                                  Expr::create<IntegerConstant>(2)),
      Expr::create<BinaryArithOp>(
          OperatorKind::BinaryDivide,
          Expr::create<BinaryArithOp>(
              OperatorKind::BinaryPlus,
              Expr::create<BinaryArithOp>(OperatorKind::BinaryMultiply,
                                          Expr::create<IntegerConstant>(4), x),
              Expr::create<IntegerConstant>(5)),
          Expr::create<UnaryArithOp>(OperatorKind::UnaryMinus, x)));
  typeCheck(f);
  dump(f);
  assert(f.getType() == ExprType::Float);

  // 1 + true, which is a type error.
  auto e = Expr::create<BinaryArithOp>(OperatorKind::BinaryPlus,
                                       Expr::create<IntegerConstant>(1),
                                       Expr::create<BooleanConstant>(true));
  typeCheck(e);
  dump(e);
  assert(e.getType() == ExprType::ErrorType);

  // (x + 3.14 >= y * 6e5 - x ? true : x > .5) == false
  // created from parsing
  auto g = parse("(x + 3.14 >= y * 6e5 - x ? true : x > .5) == false");
  typeCheck(g); // Boolean
  dump(g);
  assert(g.getType() == ExprType::Boolean);

  auto h =
      parse("x < y && z", {{"x", ExprType::Integer}, {"z", ExprType::Boolean}});
  typeCheck(h);
  dump(h);
  assert(h.getType() == ExprType::Boolean);
  return 0;
}