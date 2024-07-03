#ifndef EXPR_TYPE_CHECK_HPP
#define EXPR_TYPE_CHECK_HPP

#include "expr.hpp"

class TypeCheckVisitor : public ExprNodeVisitor {
  using ET = ExprType;

  static bool isArithmetic(ExprType type) {
    return type == ET::Integer || type == ET::Float;
  }

  static ExprType CommonArithmeticType(ExprType lhs, ExprType rhs) {
    if (!isArithmetic(lhs) || !isArithmetic(rhs))
      return ET::ErrorType;
    if (lhs == ET::Float || rhs == ET::Float)
      return ET::Float;
    else
      return ET::Integer;
  }

  static ExprType CommonType(ExprType lhs, ExprType rhs) {
    if (lhs == rhs)
      return lhs;
    return CommonArithmeticType(lhs, rhs);
  }

  ExprType visitAndGetType(const Expr &expr) {
    expr.accept(*this);
    return expr.getType();
  }

public:
  void visit([[maybe_unused]] Variable &v) override {
    // The type of Variable should be set during initialization.
    assert(v.getType() == ET::Integer ||
           v.getType() == ET::Boolean ||
           v.getType() == ET::Float);
  }

  void visit([[maybe_unused]] IntegerConstant &c) override {
    // The type of IntegerConstant should be set during initialization.
    assert(c.getType() == ET::Integer);
  }

  void visit([[maybe_unused]] FloatConstant &c) override {
    // The type of FloatConstant should be set during initialization.
    assert(c.getType() == ET::Float);
  }

  void visit([[maybe_unused]] BooleanConstant &c) override {
    // The type of BooleanConstant should be set during initialization.
    assert(c.getType() == ET::Boolean);
  }

  void visit(UnaryArithOp &u) override {
    auto operandType = visitAndGetType(u.getOperand());
    if (isArithmetic(operandType))
      u.setType(operandType);
    else
      u.setType(ET::ErrorType);
  }

  void visit(LogicalNotOp &l) override {
    auto operandType = visitAndGetType(l.getOperand());
    if (operandType == ET::Boolean)
      l.setType(ET::Boolean);
    else
      l.setType(ET::ErrorType);
  }

  void visit(BinaryArithOp &b) override {
    auto lhsType = visitAndGetType(b.getLHS());
    auto rhsType = visitAndGetType(b.getRHS());
    b.setType(CommonArithmeticType(lhsType, rhsType));
  }

  void visit(EqualityOp &e) override {
    auto lhsType = visitAndGetType(e.getLHS());
    auto rhsType = visitAndGetType(e.getRHS());
    if (CommonType(lhsType, rhsType) != ET::ErrorType)
      e.setType(ET::Boolean);
    else
      e.setType(ET::ErrorType);
  }

  void visit(RelationalOp &r) override {
    auto lhsType = visitAndGetType(r.getLHS());
    auto rhsType = visitAndGetType(r.getRHS());
    if (CommonArithmeticType(lhsType, rhsType) != ET::ErrorType)
      r.setType(ET::Boolean);
    else
      r.setType(ET::ErrorType);
  }

  void visit(BinaryLogicalOp &b) override {
    auto lhsType = visitAndGetType(b.getLHS());
    auto rhsType = visitAndGetType(b.getRHS());
    if (lhsType == ET::Boolean && rhsType == ET::Boolean)
      b.setType(ET::Boolean);
    else
      b.setType(ET::ErrorType);
  }

  void visit(ConditionalOp &c) override {
    auto condType = visitAndGetType(c.getCondition());
    auto etType = visitAndGetType(c.getExprTrue());
    auto efType = visitAndGetType(c.getExprFalse());
    if (condType != ET::Boolean)
      c.setType(ET::ErrorType);
    else
      c.setType(CommonType(etType, efType));
  }
};

void typeCheck(Expr &expr) {
  TypeCheckVisitor visitor;
  expr.accept(visitor);
}

#endif // EXPR_TYPE_CHECK_HPP
