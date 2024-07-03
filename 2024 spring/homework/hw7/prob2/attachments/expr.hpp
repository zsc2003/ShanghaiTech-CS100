#ifndef EXPR_HPP
#define EXPR_HPP

#include <cassert>
#include <cmath>
#include <memory>
#include <string>

enum class ExprType { Unevaluated, Integer, Float, Boolean, ErrorType };

class ExprNodeVisitor;

class ExprNode {
  ExprType mType;

public:
  explicit ExprNode(ExprType type = ExprType::Unevaluated) : mType{type} {}

  void setType(ExprType type) { mType = type; }

  ExprType getType() const { return mType; }

  virtual void accept(ExprNodeVisitor &visitor) = 0;

  virtual ~ExprNode() = default;
};

class Expr {
  std::shared_ptr<ExprNode> mNode;

  Expr(std::shared_ptr<ExprNode> node) : mNode{std::move(node)} {}

public:
  void setType(ExprType type) { mNode->setType(type); }

  ExprType getType() const { return mNode->getType(); }

  void accept(ExprNodeVisitor &visitor) const { mNode->accept(visitor); }

  template <
      typename ConcreteType, typename... Args,
      typename = std::enable_if_t<std::is_base_of_v<ExprNode, ConcreteType>>>
  static Expr create(Args &&...args) {
    return {std::make_shared<ConcreteType>(std::forward<Args>(args)...)};
  }
};

class Variable;
template <typename T, ExprType ET> class Constant;
using IntegerConstant = Constant<int, ExprType::Integer>;
using FloatConstant = Constant<double, ExprType::Float>;
using BooleanConstant = Constant<bool, ExprType::Boolean>;
class UnaryArithOp;
class LogicalNotOp;
class BinaryArithOp;
class EqualityOp;
class RelationalOp;
class BinaryLogicalOp;
class ConditionalOp;

enum class OperatorKind {
  UnaryPlus,
  UnaryMinus,
  BinaryPlus,
  BinaryMinus,
  BinaryMultiply,
  BinaryDivide,
  LogicalNot,
  LogicalAnd,
  LogicalOr,
  Less,
  LessEqual,
  Greater,
  GreaterEqual,
  Equal,
  NotEqual,
  Conditional
};

class ExprNodeVisitor {
public:
  virtual void visit(Variable &) = 0;
  virtual void visit(IntegerConstant &) = 0;
  virtual void visit(FloatConstant &) = 0;
  virtual void visit(BooleanConstant &) = 0;
  virtual void visit(UnaryArithOp &) = 0;
  virtual void visit(LogicalNotOp &) = 0;
  virtual void visit(BinaryArithOp &) = 0;
  virtual void visit(EqualityOp &) = 0;
  virtual void visit(RelationalOp &) = 0;
  virtual void visit(BinaryLogicalOp &) = 0;
  virtual void visit(ConditionalOp &) = 0;
  virtual ~ExprNodeVisitor() = default;
};

class Variable : public ExprNode {
  std::string mName;

public:
  Variable(ExprType type, std::string name)
      : ExprNode{type}, mName{std::move(name)} {
    assert(type == ExprType::Integer || type == ExprType::Boolean ||
           type == ExprType::Float);
  }

  const std::string &getName() const { return mName; }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

template <typename T, ExprType ET> class Constant : public ExprNode {
  T mValue;

public:
  T getValue() const { return mValue; }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }

  explicit Constant(T value) : ExprNode{ET}, mValue{value} {}
};

class UnaryOperator : public ExprNode {
  OperatorKind mOpKind;
  Expr mOperand;

public:
  OperatorKind getOpKind() const { return mOpKind; }

  const Expr &getOperand() const { return mOperand; }

  UnaryOperator(OperatorKind op, Expr operand)
      : ExprNode{}, mOpKind{op}, mOperand{std::move(operand)} {}
};

class UnaryArithOp : public UnaryOperator {
public:
  UnaryArithOp(OperatorKind op, Expr operand)
      : UnaryOperator{op, std::move(operand)} {
    assert(op == OperatorKind::UnaryPlus || op == OperatorKind::UnaryMinus);
  }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

class LogicalNotOp : public UnaryOperator {
public:
  LogicalNotOp(Expr operand)
      : UnaryOperator{OperatorKind::LogicalNot, std::move(operand)} {}

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

class BinaryOperator : public ExprNode {
  OperatorKind mOpKind;
  Expr mLeft;
  Expr mRight;

public:
  BinaryOperator(OperatorKind op, Expr left, Expr right)
      : ExprNode{}, mOpKind{op}, mLeft{std::move(left)},
        mRight{std::move(right)} {}

  const Expr &getLHS() const { return mLeft; }

  const Expr &getRHS() const { return mRight; }

  OperatorKind getOpKind() const { return mOpKind; }
};

class BinaryArithOp : public BinaryOperator {
public:
  BinaryArithOp(OperatorKind op, Expr left, Expr right)
      : BinaryOperator{op, std::move(left), std::move(right)} {
    assert(op == OperatorKind::BinaryPlus || op == OperatorKind::BinaryMinus ||
           op == OperatorKind::BinaryMultiply ||
           op == OperatorKind::BinaryDivide);
  }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

class EqualityOp : public BinaryOperator {
public:
  EqualityOp(OperatorKind op, Expr left, Expr right)
      : BinaryOperator{op, std::move(left), std::move(right)} {
    assert(op == OperatorKind::Equal || op == OperatorKind::NotEqual);
  }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

class RelationalOp : public BinaryOperator {
public:
  RelationalOp(OperatorKind op, Expr left, Expr right)
      : BinaryOperator{op, std::move(left), std::move(right)} {
    assert(op == OperatorKind::Less || op == OperatorKind::LessEqual ||
           op == OperatorKind::Greater || op == OperatorKind::GreaterEqual);
  }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

class BinaryLogicalOp : public BinaryOperator {
public:
  BinaryLogicalOp(OperatorKind op, Expr left, Expr right)
      : BinaryOperator{op, std::move(left), std::move(right)} {
    assert(op == OperatorKind::LogicalAnd || op == OperatorKind::LogicalOr);
  }

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }
};

class ConditionalOp : public ExprNode {
  Expr mCondition;
  Expr mExprTrue;
  Expr mExprFalse;

public:
  ConditionalOp(Expr cond, Expr etrue, Expr efalse)
      : ExprNode{}, mCondition{std::move(cond)}, mExprTrue{std::move(etrue)},
        mExprFalse{std::move(efalse)} {}

  void accept(ExprNodeVisitor &visitor) override { visitor.visit(*this); }

  OperatorKind getOpKind() const { return OperatorKind::Conditional; }

  const Expr &getCondition() const { return mCondition; }

  const Expr &getExprTrue() const { return mExprTrue; }

  const Expr &getExprFalse() const { return mExprFalse; }
};

#endif // EXPR_HPP
