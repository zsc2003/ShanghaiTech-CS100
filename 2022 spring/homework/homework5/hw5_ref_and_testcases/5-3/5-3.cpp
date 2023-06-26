#include <cmath>
#include <string>

class Expr_node {
 public:
  Expr_node() = default;

  virtual double eval() const = 0;
  virtual std::string to_string() const = 0;

  virtual ~Expr_node() = default;

  Expr_node(const Expr_node &) = delete;
  Expr_node &operator=(const Expr_node &) = delete;
};

class Number_node : public Expr_node {
  friend Number_node *make_number(double);

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

inline Number_node *make_number(double value) {
  return new Number_node{value};
}

class Negation_node : public Expr_node {
  friend Negation_node *make_negation(Expr_node *);

  Expr_node *operand;

  Negation_node(Expr_node *expr) : operand(expr) {}

  virtual double eval() const override {
    return -operand->eval();
  }
  virtual std::string to_string() const override {
    return "(-" + operand->to_string() + ")";
  }

  virtual ~Negation_node() {
    delete operand;
  }
};

inline Negation_node *make_negation(Expr_node *expr) {
  return new Negation_node{expr};
}

class Binary_node : public Expr_node {
 protected:
  Expr_node *lhs, *rhs;

  Binary_node(Expr_node *left, Expr_node *right) : lhs(left), rhs(right) {}

  virtual ~Binary_node() {
    delete lhs;
    delete rhs;
  }
};

class Plus_node : public Binary_node {
  friend Plus_node *make_plus(Expr_node *, Expr_node *);

  // "Inherited" constructors. See C++ Primer 15.7.4
  using Binary_node::Binary_node;

  virtual double eval() const override {
    return lhs->eval() + rhs->eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs->to_string() + " + " + rhs->to_string() + ")";
  }
};

inline Plus_node *make_plus(Expr_node *lhs, Expr_node *rhs) {
  return new Plus_node{lhs, rhs};
}

class Minus_node : public Binary_node {
  friend Minus_node *make_minus(Expr_node *, Expr_node *);

  using Binary_node::Binary_node;

  virtual double eval() const override {
    return lhs->eval() - rhs->eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs->to_string() + " - " + rhs->to_string() + ")";
  }
};

inline Minus_node *make_minus(Expr_node *lhs, Expr_node *rhs) {
  return new Minus_node{lhs, rhs};
}

class Multiply_node : public Binary_node {
  friend Multiply_node *make_multiply(Expr_node *, Expr_node *);

  using Binary_node::Binary_node;

  virtual double eval() const override {
    return lhs->eval() * rhs->eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs->to_string() + " * " + rhs->to_string() + ")";
  }
};

inline Multiply_node *make_multiply(Expr_node *lhs, Expr_node *rhs) {
  return new Multiply_node{lhs, rhs};
}

class Divide_node : public Binary_node {
  friend Divide_node *make_divide(Expr_node *, Expr_node *);

  using Binary_node::Binary_node;
  
  virtual double eval() const override {
    return lhs->eval() / rhs->eval();
  }
  virtual std::string to_string() const override {
    return "(" + lhs->to_string() + " / " + rhs->to_string() + ")";
  }
};

inline Divide_node *make_divide(Expr_node *lhs, Expr_node *rhs) {
  return new Divide_node{lhs, rhs};
}

/**
 * In what follows, the nodes corresponding to five elementary functions are
 * implemented in one class 'Function_node', with a function pointer 'func'
 * pointing to the exact function in <cmath>, and 'func_name' representing the
 * name of the function.
 *
 * Which one is better, using five different classes like 'Sin_node',
 * 'Cos_node', ..., or using only one class 'Function_node'? Well, the answer
 * depends on how you're gonna use this tree. If you just want to evaluate the
 * expression and convert it to string, one class is enough. But suppose we are
 * using the expression tree to model a one-variable function f(x), and we may
 * want to find the derivative df(x)/dx. Then it might be necessary to define
 * five different classes, since the ways of differentiating these functions
 * differ considerably. We may have something like this:
 *
 * // d(sin(f(x)))/dx = cos(f(x))f'(x)
 * Expr_node *Sin_node::derivative() const {
 *   return make_multiply(make_cos(arg), arg->derivative());
 * }
 * 
 * // d(log(f(x)))/dx = f'(x)/f(x)
 * Expr_node *Log_node::derivative() const {
 *   return make_divide(arg->derivative(), arg);
 * }
 * ...
 */
class Function_node : public Expr_node {
  friend Function_node *make_sin(Expr_node *);
  friend Function_node *make_cos(Expr_node *);
  friend Function_node *make_tan(Expr_node *);
  friend Function_node *make_log(Expr_node *);
  friend Function_node *make_exp(Expr_node *);

  Expr_node *arg;
  double (*func)(double);
  std::string func_name;

  Function_node(Expr_node *a, double (*f)(double), const std::string &name)
      : arg(a), func(f), func_name(name) {}

  virtual double eval() const override {
    return func(arg->eval());
  }
  virtual std::string to_string() const override {
    auto ret = arg->to_string();
    if (!ret.empty() && ret.front() == '(' && ret.back() == ')')
      return func_name + ret;
    else
      return func_name + "(" + ret + ")";
  }

  virtual ~Function_node() {
    delete arg;
  }
};

inline Function_node *make_sin(Expr_node *arg) {
  return new Function_node{arg, sin, "sin"};
}

inline Function_node *make_cos(Expr_node *arg) {
  return new Function_node{arg, cos, "cos"};
}

inline Function_node *make_tan(Expr_node *arg) {
  return new Function_node{arg, tan, "tan"};
}

inline Function_node *make_log(Expr_node *arg) {
  return new Function_node{arg, log, "log"};
}

inline Function_node *make_exp(Expr_node *arg) {
  return new Function_node{arg, exp, "exp"};
}