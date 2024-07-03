#ifndef EXPR_HPP
#define EXPR_HPP

#include <cmath>
#include <memory>
#include <string>

class ExprNode {
public:
  ExprNode() = default;

  virtual double evaluate(double x) const = 0;

  virtual double derivative(double x) const = 0;

  virtual std::string toString() const = 0;

  virtual ~ExprNode() = default;
};

class Expr {
  std::shared_ptr<ExprNode> mNode;

  Expr(std::shared_ptr<ExprNode> ptr) : mNode{std::move(ptr)} {}

public:
  Expr(double value);

  double evaluate(double x) const { return mNode->evaluate(x); }

  double derivative(double x) const { return mNode->derivative(x); }

  std::string toString() const { return mNode->toString(); }

  static const Expr x;

  friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);
  friend Expr sin(const Expr &);
  friend Expr cos(const Expr &);
  friend Expr tan(const Expr &);
  friend Expr exp(const Expr &);
  friend Expr log(const Expr &);
};

class Variable : public ExprNode {
public:
  double evaluate(double x) const override { return x; }

  double derivative(double /* unused */) const override { return 1; }

  std::string toString() const override { return "x"; }
};

const Expr Expr::x{std::make_shared<Variable>()};

class Constant : public ExprNode {
  double mValue;

public:
  double evaluate(double /* unused */) const override { return mValue; }

  double derivative(double /* unused */) const override { return 0; }

  std::string toString() const override { return std::to_string(mValue); }

  explicit Constant(double value) : mValue{value} {}
};

Expr::Expr(double value) : mNode{std::make_shared<Constant>(value)} {}

enum class UnaryOpKind { UOK_Plus, UOK_Minus };

class UnaryOperator : public ExprNode {
  UnaryOpKind mOpKind;
  Expr mOperand;

public:
  double evaluate(double x) const override {
    return mOpKind == UnaryOpKind::UOK_Plus ? mOperand.evaluate(x)
                                            : -mOperand.evaluate(x);
  }

  double derivative(double x) const override {
    return mOpKind == UnaryOpKind::UOK_Plus ? mOperand.derivative(x)
                                            : -mOperand.derivative(x);
  }

  std::string toString() const override {
    return getOp() + ('(' + mOperand.toString() + ')');
  }

  char getOp() const { return mOpKind == UnaryOpKind::UOK_Plus ? '+' : '-'; }

  UnaryOperator(UnaryOpKind op, Expr operand)
      : mOpKind{op}, mOperand{std::move(operand)} {}
};

Expr operator-(const Expr &operand) {
  return {std::make_shared<UnaryOperator>(UnaryOpKind::UOK_Minus, operand)};
}

Expr operator+(const Expr &operand) {
  return {std::make_shared<UnaryOperator>(UnaryOpKind::UOK_Plus, operand)};
}

class BinaryOperator : public ExprNode {
protected:
  Expr mLeft;
  Expr mRight;

public:
  BinaryOperator(Expr left, Expr right)
      : mLeft{std::move(left)}, mRight{std::move(right)} {}
};

class PlusOperator : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  double evaluate(double x) const override {
    return mLeft.evaluate(x) + mRight.evaluate(x);
  }

  double derivative(double x) const override {
    return mLeft.derivative(x) + mRight.derivative(x);
  }

  std::string toString() const override {
    return '(' + mLeft.toString() + ") + (" + mRight.toString() + ')';
  }
};

class MinusOperator : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  double evaluate(double x) const override {
    return mLeft.evaluate(x) - mRight.evaluate(x);
  }

  double derivative(double x) const override {
    return mLeft.derivative(x) - mRight.derivative(x);
  }

  std::string toString() const override {
    return '(' + mLeft.toString() + ") - (" + mRight.toString() + ')';
  }
};

class MultiplyOperator : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  double evaluate(double x) const override {
    return mLeft.evaluate(x) * mRight.evaluate(x);
  }

  double derivative(double x) const override {
    return mLeft.derivative(x) * mRight.evaluate(x) +
           mLeft.evaluate(x) * mRight.derivative(x);
  }

  std::string toString() const override {
    return '(' + mLeft.toString() + ") * (" + mRight.toString() + ')';
  }
};

class DivideOperator : public BinaryOperator {
public:
  using BinaryOperator::BinaryOperator;

  double evaluate(double x) const override {
    return mLeft.evaluate(x) / mRight.evaluate(x);
  }

  double derivative(double x) const override {
    auto right_val = mRight.evaluate(x);
    return (mLeft.derivative(x) * right_val -
            mLeft.evaluate(x) * mRight.derivative(x)) /
           (right_val * right_val);
  }

  std::string toString() const override {
    return '(' + mLeft.toString() + ") / (" + mRight.toString() + ')';
  }
};

Expr operator+(const Expr &left, const Expr &right) {
  return {std::make_shared<PlusOperator>(left, right)};
}

Expr operator-(const Expr &left, const Expr &right) {
  return {std::make_shared<MinusOperator>(left, right)};
}

Expr operator*(const Expr &left, const Expr &right) {
  return {std::make_shared<MultiplyOperator>(left, right)};
}

Expr operator/(const Expr &left, const Expr &right) {
  return {std::make_shared<DivideOperator>(left, right)};
}

/// The following are not required but are interesting and helpful.

// These are *user-defined literal suffixes*, with which you can write
//   auto f = 2_ex * 3_ex;
// and it is equivalent to
//   auto f = Expr(2) * expr(3);
Expr operator""_ex(unsigned long long x) { return {static_cast<double>(x)}; }
Expr operator""_ex(long double x) { return {static_cast<double>(x)}; }

class Function : public ExprNode {
  using FuncType = double(double);

protected:
  FuncType *mFuncPtr;
  std::string mFuncName;
  Expr mArg;

public:
  Function(FuncType *ptr, std::string name, Expr arg)
      : mFuncPtr{ptr}, mFuncName{std::move(name)}, mArg{std::move(arg)} {}

  double evaluate(double x) const override { return mFuncPtr(x); }

  std::string toString() const override {
    return mFuncName + '(' + mArg.toString() + ')';
  }
};

class SinFunction : public Function {
public:
  double derivative(double x) const override {
    return std::cos(mArg.evaluate(x)) * mArg.derivative(x);
  }

  explicit SinFunction(Expr arg) : Function(std::sin, "sin", std::move(arg)) {}
};

class CosFunction : public Function {
public:
  double derivative(double x) const override {
    return -std::sin(mArg.evaluate(x)) * mArg.derivative(x);
  }

  explicit CosFunction(Expr arg) : Function(std::cos, "cos", std::move(arg)) {}
};

class TanFunction : public Function {
public:
  double derivative(double x) const override {
    return mArg.derivative(x) / std::pow(std::cos(mArg.evaluate(x)), 2);
  }

  explicit TanFunction(Expr arg) : Function(std::tan, "tan", std::move(arg)) {}
};

class ExpFunction : public Function {
public:
  double derivative(double x) const override {
    return evaluate(x) * mArg.derivative(x);
  }

  explicit ExpFunction(Expr arg) : Function(std::exp, "exp", std::move(arg)) {}
};

class LogFunction : public Function {
public:
  double derivative(double x) const override {
    return mArg.derivative(x) / mArg.evaluate(x);
  }

  explicit LogFunction(Expr arg) : Function(std::log, "log", std::move(arg)) {}
};

Expr sin(const Expr &arg) { return {std::make_shared<SinFunction>(arg)}; }

Expr cos(const Expr &arg) { return {std::make_shared<CosFunction>(arg)}; }

Expr tan(const Expr &arg) { return {std::make_shared<TanFunction>(arg)}; }

Expr exp(const Expr &arg) { return {std::make_shared<ExpFunction>(arg)}; }

Expr log(const Expr &arg) { return {std::make_shared<LogFunction>(arg)}; }

#endif // EXPR_HPP