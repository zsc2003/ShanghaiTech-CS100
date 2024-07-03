#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>
#include <string>

class ExprNode {
public:
  // FIXME: Make any of these functions virtual, or pure virtual, if necessary.
  ExprNode() = default;

  double evaluate(double x) const;

  double derivative(double x) const;

  std::string toString() const;
  
  ~ExprNode() = default;
};

class Expr {
  std::shared_ptr<ExprNode> mNode;

  Expr(std::shared_ptr<ExprNode> ptr) : mNode{std::move(ptr)} {}

public:
  Expr(double value);

  // TODO: Add member functions if necessary.

  static const Expr x;

  // TODO: Add friend declarations if necessary.
};

class Variable : public ExprNode {
public:
  // TODO: evaluate, derivative and toString ...
};

const Expr Expr::x{std::make_shared<Variable>()};

class Constant : public ExprNode {
  double mValue;

public:
  explicit Constant(double value) : mValue{value} {}

  // TODO: evaluate, derivative and toString ...
};

Expr::Expr(double value) : mNode{std::make_shared<Constant>(value)} {}

enum class UnaryOpKind {
  UOK_Plus, UOK_Minus
};

class UnaryOperator : public ExprNode {
  UnaryOpKind mOpKind;
  Expr mOperand;

public:
  UnaryOperator(UnaryOpKind op, Expr operand) : mOpKind{op}, mOperand{std::move(operand)} {}

  // TODO: evaluate, derivative and toString ...
};

class BinaryOperator : public ExprNode {
protected:
  Expr mLeft;
  Expr mRight;

public:
  BinaryOperator(Expr left, Expr right)
      : mLeft{std::move(left)}, mRight{std::move(right)} {}
};

class PlusOp : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

class MinusOp : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

class MultiplyOp : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

class DivideOp : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  // TODO: evaluate, derivative and toString ...
};

// TODO: Add functions if necessary.

#endif // EXPR_HPP