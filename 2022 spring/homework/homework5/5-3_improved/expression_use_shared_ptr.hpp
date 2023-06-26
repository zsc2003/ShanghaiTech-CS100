#ifndef CS100_HW_EXPRESSION_HPP
#define CS100_HW_EXPRESSION_HPP

#include <cmath>
#include <memory>
#include <string>

class Expr_node {
  friend class Expr;

 protected:
  virtual double eval() const = 0;
  virtual std::string to_string() const = 0;

 public:
  virtual ~Expr_node() = default;
};

class Expr {
  std::shared_ptr<Expr_node> ptr;

 public:
  Expr(double);
  double eval() const {
    return ptr->eval();
  }
  std::string to_string() const {
    return ptr->to_string();
  }

 private:
  Expr(Expr_node *p) : ptr(p) {}

  friend Expr operator-(const Expr &);
  friend Expr operator+(const Expr &, const Expr &);
  friend Expr operator-(const Expr &, const Expr &);
  friend Expr operator*(const Expr &, const Expr &);
  friend Expr operator/(const Expr &, const Expr &);
  friend Expr sin(const Expr &);
  friend Expr cos(const Expr &);
  friend Expr tan(const Expr &);
  friend Expr log(const Expr &);
  friend Expr exp(const Expr &);
};

class Number_node : public Expr_node {
  friend class Expr;

  double value;

  Number_node(double val) : value(val) {}

  virtual double eval() const override {
    return value;
  }
  virtual std::string to_string() const override {
    auto number = std::to_string(value);
    if (number.front() == '-')
      return "(" + number + ")";
    else
      return number;
  }
};

Expr::Expr(double value) : ptr(new Number_node(value)) {}

class Negation_node : public Expr_node {
  friend Expr operator-(const Expr &);

  Expr operand;

  Negation_node(const Expr &expr) : operand(expr) {}

  virtual double eval() const override {
    return -operand.eval();
  }
  virtual std::string to_string() const override {
    return "(-" + operand.to_string() + ")";
  }
};

inline Expr operator-(const Expr &expr) {
  return new Negation_node(expr);
}

class Binary_node : public Expr_node {
 protected:
  Expr lhs, rhs;

  Binary_node(const Expr &left, const Expr &right) : lhs(left), rhs(right) {}
};

class Plus_node : public Binary_node {
  friend Expr operator+(const Expr &, const Expr &);

  Plus_node(const Expr &left, const Expr &right) : Binary_node(left, right) {}

  virtual double eval() const override {
    return lhs.eval() + rhs.eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs.to_string() + " + " + rhs.to_string() + ")";
  }
};

inline Expr operator+(const Expr &lhs, const Expr &rhs) {
  return new Plus_node(lhs, rhs);
}

class Minus_node : public Binary_node {
  friend Expr operator-(const Expr &, const Expr &);

  Minus_node(const Expr &left, const Expr &right) : Binary_node(left, right) {}

  virtual double eval() const override {
    return lhs.eval() - rhs.eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs.to_string() + " - " + rhs.to_string() + ")";
  }
};

inline Expr operator-(const Expr &lhs, const Expr &rhs) {
  return new Minus_node(lhs, rhs);
}

class Multiply_node : public Binary_node {
  friend Expr operator*(const Expr &, const Expr &);

  Multiply_node(const Expr &left, const Expr &right)
      : Binary_node(left, right) {}

  virtual double eval() const override {
    return lhs.eval() * rhs.eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs.to_string() + " * " + rhs.to_string() + ")";
  }
};

inline Expr operator*(const Expr &lhs, const Expr &rhs) {
  return new Multiply_node(lhs, rhs);
}

class Divide_node : public Binary_node {
  friend Expr operator/(const Expr &, const Expr &);

  Divide_node(const Expr &left, const Expr &right) : Binary_node(left, right) {}

  virtual double eval() const override {
    return lhs.eval() / rhs.eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs.to_string() + " / " + rhs.to_string() + ")";
  }
};

inline Expr operator/(const Expr &lhs, const Expr &rhs) {
  return new Divide_node(lhs, rhs);
}

class Function_node : public Expr_node {
  friend Expr sin(const Expr &);
  friend Expr cos(const Expr &);
  friend Expr tan(const Expr &);
  friend Expr log(const Expr &);
  friend Expr exp(const Expr &);

  Expr arg;
  double (*func)(double);
  std::string func_name;

  Function_node(const Expr &a, double (*f)(double), const std::string &name)
      : arg(a), func(f), func_name(name) {}

  virtual double eval() const override {
    return func(arg.eval());
  }
  virtual std::string to_string() const override {
    auto ret = arg.to_string();
    if (!ret.empty() && ret.front() == '(' && ret.back() == ')')
      return func_name + ret;
    else
      return func_name + "(" + ret + ")";
  }
};

inline Expr sin(const Expr &arg) {
  double (*func)(double) = std::sin;
  return new Function_node(arg, func, "sin");
}

inline Expr cos(const Expr &arg) {
  double (*func)(double) = std::cos;
  return new Function_node(arg, func, "cos");
}

inline Expr tan(const Expr &arg) {
  double (*func)(double) = std::tan;
  return new Function_node(arg, func, "tan");
}

inline Expr log(const Expr &arg) {
  double (*func)(double) = std::log;
  return new Function_node(arg, func, "log");
}

inline Expr exp(const Expr &arg) {
  double (*func)(double) = std::exp;
  return new Function_node(arg, func, "exp");
}

#endif // CS100_HW_EXPRESSION_HPP
