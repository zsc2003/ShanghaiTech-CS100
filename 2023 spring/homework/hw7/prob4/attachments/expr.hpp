#ifndef EXPR_HPP
#define EXPR_HPP

#include <memory>
#include <string>

class NodeBase {
 public:
  // Make any of these functions virtual, or pure virtual, if necessary.
  NodeBase() = default;
  double eval(double x) const;
  double derivative(double x) const;
  std::string rep() const;
  ~NodeBase() = default;
};

class Expr {
  std::shared_ptr<NodeBase> m_ptr;

  Expr(std::shared_ptr<NodeBase> ptr) : m_ptr{ptr} {}

 public:
  Expr(double value);

  // Add member functions if necessary.

  static const Expr x;

  // Add friend declarations if necessary.
};

class Variable : public NodeBase {
  // Add functions if necessary.
};

class Constant : public NodeBase {
  double m_value;

  // Add functions if necessary.

 public:
  Constant(double value) : m_value{value} {}
};

class UnaryOperator : public NodeBase {
  char m_op;
  Expr m_operand;

  // Add functions if necessary.

 public:
  UnaryOperator(char op, const Expr &operand) : m_op{op}, m_operand{operand} {}
};

class BinaryOperator : public NodeBase {
 protected:
  Expr m_left;
  Expr m_right;

 public:
  BinaryOperator(const Expr &left, const Expr &right)
      : m_left{left}, m_right{right} {}
};

class PlusOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;

  // Add functions if necessary.
};

class MinusOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  
  // Add functions if necessary.
};

class MultiplyOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  
  // Add functions if necessary.
};

class DivideOp : public BinaryOperator {
  using BinaryOperator::BinaryOperator;
  
  // Add functions if necessary.
};

const Expr Expr::x{std::make_shared<Variable>()};

Expr::Expr(double value) : m_ptr{std::make_shared<Constant>(value)} {}

Expr operator-(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('-', operand)};
}

Expr operator+(const Expr &operand) {
  return {std::make_shared<UnaryOperator>('+', operand)};
}

Expr operator+(const Expr &left, const Expr &right) {
  // Your code here.
}

Expr operator-(const Expr &left, const Expr &right) {
  // Your code here.
}

Expr operator*(const Expr &left, const Expr &right) {
  // Your code here.
}

Expr operator/(const Expr &left, const Expr &right) {
  // Your code here.
}

#endif // EXPR_HPP