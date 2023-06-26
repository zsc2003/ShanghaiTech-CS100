#define main __student_main_function_
#define _ONLINE_JUDGE

/**************************************************/

// PASTE YOUR CODE HERE

/**************************************************/

#ifdef OJ_ASSERT
#undef OJ_ASSERT
#endif

#include <cmath>
#include <iostream>
#include <type_traits>

#undef main

namespace details {

struct Unimplemented {
  operator Expr_node *() const {
    return nullptr;
  }
};

template <typename T>
inline auto make_sin_helper(T *arg, int) -> decltype(make_sin(arg)) {
  return make_sin(arg);
}

template <typename T>
inline auto make_sin_helper(T *, double) {
  return Unimplemented{};
}

constexpr bool defined_make_sin =
    !std::is_same<decltype(make_sin_helper((Expr_node *)nullptr, 0)),
                  Unimplemented>::value;

template <typename T>
inline auto make_cos_helper(T *arg, int) -> decltype(make_cos(arg)) {
  return make_cos(arg);
}

template <typename T>
inline auto make_cos_helper(T *, double) {
  return Unimplemented{};
}

constexpr bool defined_make_cos =
    !std::is_same<decltype(make_cos_helper((Expr_node *)nullptr, 0)),
                  Unimplemented>::value;

template <typename T>
inline auto make_tan_helper(T *arg, int) -> decltype(make_tan(arg)) {
  return make_tan(arg);
}

template <typename T>
inline auto make_tan_helper(T *, double) {
  return Unimplemented{};
}

constexpr bool defined_make_tan =
    !std::is_same<decltype(make_tan_helper((Expr_node *)nullptr, 0)),
                  Unimplemented>::value;

template <typename T>
inline auto make_log_helper(T *arg, int) -> decltype(make_log(arg)) {
  return make_log(arg);
}

template <typename T>
inline auto make_log_helper(T *, double) {
  return Unimplemented{};
}

constexpr bool defined_make_log =
    !std::is_same<decltype(make_log_helper((Expr_node *)nullptr, 0)),
                  Unimplemented>::value;

template <typename T>
inline auto make_exp_helper(T *arg, int) -> decltype(make_exp(arg)) {
  return make_exp(arg);
}

template <typename T>
inline auto make_exp_helper(T *, double) {
  return Unimplemented{};
}

constexpr bool defined_make_exp =
    !std::is_same<decltype(make_exp_helper((Expr_node *)nullptr, 0)),
                  Unimplemented>::value;

constexpr bool part2_implemented = defined_make_sin && defined_make_cos &&
                                   defined_make_tan && defined_make_log &&
                                   defined_make_exp;

} // namespace details

inline bool double_eq(double lhs, double rhs) {
  constexpr double EPS = 1e-9;
  return std::fabs(lhs - rhs) < EPS;
}

#define OJ_ASSERT(x)                                                           \
  {                                                                            \
    if (!(x)) {                                                                \
      std::cout << "Wrong answer at line " << __LINE__ << std::endl;           \
      delete expr;                                                             \
      return 0;                                                                \
    }                                                                          \
  }

template <bool Implemented /* false */>
struct test_part2 {
  static void test(int) {
    std::cout << "Part 2 not implemented." << std::endl;
  }
};

template <>
struct test_part2<true> {
  static auto make_sin(Expr_node *arg) {
    return details::make_sin_helper(arg, 0);
  }
  static auto make_cos(Expr_node *arg) {
    return details::make_cos_helper(arg, 0);
  }
  static auto make_tan(Expr_node *arg) {
    return details::make_tan_helper(arg, 0);
  }
  static auto make_log(Expr_node *arg) {
    return details::make_log_helper(arg, 0);
  }
  static auto make_exp(Expr_node *arg) {
    return details::make_exp_helper(arg, 0);
  }
  static int test(int testcase) {
    switch (testcase) {
      case 8: {
        Expr_node *expr = make_cos(make_minus(
            make_tan(make_divide(
                make_number(-6),
                make_multiply(
                    make_divide(make_number(1), make_number(3)),
                    make_divide(make_number(-7),
                                make_sin(make_negation(make_number(3))))))),
            make_divide(make_number(-2), make_number(7))));
        OJ_ASSERT(double_eq(expr->eval(), 0.995587110164088));
        OJ_ASSERT(expr->to_string() ==
                  "cos(tan((-6.000000) / ((1.000000 / 3.000000) * ((-7.000000) "
                  "/ sin(-3.000000)))) - ((-2.000000) / 7.000000))");
        delete expr;
        expr = make_tan(make_multiply(
            make_number(-8),
            make_multiply(
                make_minus(
                    make_minus(make_cos(make_number(-7)), make_number(-8)),
                    make_number(10)),
                make_plus(
                    make_number(-5),
                    make_minus(
                        make_minus(make_number(-6), make_number(7)),
                        make_plus(make_number(3),
                                  make_plus(make_number(-1),
                                            make_divide(make_number(7),
                                                        make_number(-5)))))))));
        OJ_ASSERT(double_eq(expr->eval(), -0.06547129943848862));
        OJ_ASSERT(expr->to_string() ==
                  "tan((-8.000000) * (((cos(-7.000000) - (-8.000000)) - "
                  "10.000000) * ((-5.000000) + (((-6.000000) - 7.000000) - "
                  "(3.000000 + ((-1.000000) + (7.000000 / (-5.000000))))))))");
        delete expr;
        expr = make_exp(make_plus(
            make_multiply(make_tan(make_number(7)),
                          make_plus(make_number(3),
                                    make_cos(make_minus(
                                        make_tan(make_log(make_divide(
                                            make_number(-3), make_number(-8)))),
                                        make_number(-1))))),
            make_plus(make_number(3), make_number(-8))));
        OJ_ASSERT(double_eq(expr->eval(), 0.19824643019420518));
        OJ_ASSERT(expr->to_string() ==
                  "exp((tan(7.000000) * (3.000000 + cos(tan(log((-3.000000) / "
                  "(-8.000000))) - (-1.000000)))) + (3.000000 + (-8.000000)))");
        delete expr;
        expr = make_log(make_plus(
            make_plus(make_number(8), make_negation(make_plus(make_number(-10),
                                                              make_number(4)))),
            make_multiply(
                make_multiply(make_number(7),
                              make_plus(make_sin(make_number(-3)),
                                        make_negation(make_number(2)))),
                make_number(-4))));
        OJ_ASSERT(double_eq(expr->eval(), 4.303407582843983));
        OJ_ASSERT(expr->to_string() ==
                  "log((8.000000 + (-((-10.000000) + 4.000000))) + ((7.000000 "
                  "* (sin(-3.000000) + (-2.000000))) * (-4.000000)))");
        delete expr;
        expr = make_cos(make_plus(
            make_tan(make_tan(make_cos(make_sin(make_plus(
                make_divide(make_number(6),
                            make_plus(make_number(-4), make_number(-10))),
                make_cos(make_log(make_number(5)))))))),
            make_number(-2)));
        OJ_ASSERT(double_eq(expr->eval(), 0.43329446213309153));
        OJ_ASSERT(expr->to_string() ==
                  "cos(tan(tan(cos(sin((6.000000 / ((-4.000000) + "
                  "(-10.000000))) + cos(log(5.000000)))))) + (-2.000000))");
        delete expr;
        Expr_node *expr1 = make_plus(make_number(3), make_number(4));
        Expr_node *expr2 = make_minus(make_number(5), expr1);
        OJ_ASSERT(double_eq(expr1->eval(), 7));
        OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
        delete expr2;
        break;
      }
      case 9: {
        Expr_node *expr = make_exp(make_plus(
            make_log(make_exp(make_number(3))),
            make_multiply(
                make_number(-8),
                make_plus(
                    make_number(-9),
                    make_plus(
                        make_minus(make_number(-5),
                                   make_plus(make_number(9),
                                             make_tan(make_number(-8)))),
                        make_plus(make_number(-7),
                                  make_log(make_log(make_number(2)))))))));
        OJ_ASSERT(double_eq(expr->eval(), 2.70129940186113e+130));
        OJ_ASSERT(expr->to_string() ==
                  "exp(log(exp(3.000000)) + ((-8.000000) * ((-9.000000) + "
                  "(((-5.000000) - (9.000000 + tan(-8.000000))) + ((-7.000000) "
                  "+ log(log(2.000000)))))))");
        delete expr;
        expr = make_tan(make_plus(
            make_plus(make_divide(make_number(9), make_number(-9)),
                      make_minus(make_number(0), make_number(-4))),
            make_plus(make_negation(make_negation(make_number(10))),
                      make_divide(make_log(make_negation(make_number(-3))),
                                  make_number(-3)))));
        OJ_ASSERT(double_eq(expr->eval(), 0.06752765116523755));
        OJ_ASSERT(expr->to_string() ==
                  "tan(((9.000000 / (-9.000000)) + (0.000000 - (-4.000000))) + "
                  "((-(-10.000000)) + (log(-(-3.000000)) / (-3.000000))))");
        delete expr;
        expr = make_exp(make_divide(
            make_cos(make_number(-9)),
            make_divide(
                make_number(-8),
                make_minus(make_cos(make_number(0)),
                           make_plus(make_number(-6),
                                     make_multiply(
                                         make_negation(make_sin(make_negation(
                                             make_cos(make_number(9))))),
                                         make_number(-5)))))));
        OJ_ASSERT(double_eq(expr->eval(), 1.415179346978975));
        OJ_ASSERT(expr->to_string() ==
                  "exp(cos(-9.000000) / ((-8.000000) / (cos(0.000000) - "
                  "((-6.000000) + ((-sin(-cos(9.000000))) * (-5.000000))))))");
        delete expr;
        expr = make_sin(make_multiply(
            make_multiply(make_minus(make_number(5), make_exp(make_number(-6))),
                          make_cos(make_number(8))),
            make_plus(make_number(-6),
                      make_plus(make_number(6),
                                make_plus(make_exp(make_number(-10)),
                                          make_divide(make_number(4),
                                                      make_number(10)))))));
        OJ_ASSERT(double_eq(expr->eval(), -0.2868038148084638));
        OJ_ASSERT(
            expr->to_string() ==
            "sin(((5.000000 - exp(-6.000000)) * cos(8.000000)) * ((-6.000000) "
            "+ (6.000000 + (exp(-10.000000) + (4.000000 / 10.000000)))))");
        delete expr;
        expr = make_tan(make_divide(
            make_plus(make_sin(make_minus(
                          make_number(7),
                          make_plus(make_divide(make_number(0), make_number(6)),
                                    make_number(5)))),
                      make_number(4)),
            make_divide(
                make_number(-6),
                make_plus(make_tan(make_number(8)),
                          make_minus(make_number(-1), make_number(3))))));
        OJ_ASSERT(double_eq(expr->eval(), -0.667065523696339));
        OJ_ASSERT(expr->to_string() ==
                  "tan((sin(7.000000 - ((0.000000 / 6.000000) + 5.000000)) + "
                  "4.000000) / ((-6.000000) / (tan(8.000000) + ((-1.000000) - "
                  "3.000000))))");
        delete expr;
        Expr_node *expr1 = make_plus(make_number(3), make_number(4));
        Expr_node *expr2 = make_divide(make_number(5), expr1);
        OJ_ASSERT(double_eq(expr1->eval(), 7));
        OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
        delete expr2;
        break;
      }
      case 10: {
        Expr_node *expr = make_tan(make_minus(
            make_divide(
                make_divide(make_number(8),
                            make_divide(make_number(-9),
                                        make_negation(make_divide(
                                            make_number(9), make_number(-6))))),
                make_negation(make_number(6))),
            make_plus(make_exp(make_negation(make_number(4))),
                      make_number(8))));
        OJ_ASSERT(double_eq(expr->eval(), -17.255372191325));
        OJ_ASSERT(
            expr->to_string() ==
            "tan(((8.000000 / ((-9.000000) / (-(9.000000 / (-6.000000))))) / "
            "(-6.000000)) - (exp(-4.000000) + 8.000000))");
        delete expr;
        expr = make_exp(make_minus(
            make_plus(
                make_log(make_plus(
                    make_multiply(make_number(-6), make_sin(make_number(6))),
                    make_negation(make_negation(
                        make_log(make_negation(make_number(-9))))))),
                make_number(-1)),
            make_divide(make_number(1), make_number(1))));
        OJ_ASSERT(double_eq(expr->eval(), 0.5242506640449491));
        OJ_ASSERT(
            expr->to_string() ==
            "exp((log(((-6.000000) * sin(6.000000)) + (-(-log(-(-9.000000))))) "
            "+ (-1.000000)) - (1.000000 / 1.000000))");
        delete expr;
        expr = make_cos(make_minus(
            make_negation(make_multiply(make_number(0), make_number(-10))),
            make_multiply(
                make_exp(
                    make_divide(make_exp(make_number(2)),
                                make_minus(make_number(3),
                                           make_negation(make_number(-9))))),
                make_plus(make_number(-6), make_sin(make_number(-2))))));
        OJ_ASSERT(double_eq(expr->eval(), -0.4310843151215733));
        OJ_ASSERT(
            expr->to_string() ==
            "cos((-(0.000000 * (-10.000000))) - (exp(exp(2.000000) / (3.000000 "
            "- (-(-9.000000)))) * ((-6.000000) + sin(-2.000000))))");
        delete expr;
        expr = make_log(make_plus(
            make_divide(make_number(10), make_number(9)),
            make_multiply(
                make_divide(make_number(-4),
                            make_tan(make_negation(make_number(-5)))),
                make_plus(
                    make_number(-2),
                    make_divide(
                        make_number(-7),
                        make_plus(
                            make_number(-4),
                            make_divide(make_number(5),
                                        make_divide(make_exp(make_number(4)),
                                                    make_number(-5)))))))));
        OJ_ASSERT(double_eq(expr->eval(), -0.5064886526558077));
        OJ_ASSERT(
            expr->to_string() ==
            "log((10.000000 / 9.000000) + (((-4.000000) / tan(-(-5.000000))) * "
            "((-2.000000) + ((-7.000000) / ((-4.000000) + (5.000000 / "
            "(exp(4.000000) / (-5.000000))))))))");
        delete expr;
        expr = make_sin(make_minus(
            make_exp(make_negation(make_negation(make_number(-8)))),
            make_plus(make_negation(make_number(-5)),
                      make_minus(make_negation(make_sin(make_minus(
                                     make_number(-2), make_number(-9)))),
                                 make_number(0)))));
        OJ_ASSERT(double_eq(expr->eval(), 0.9324317984504941));
        OJ_ASSERT(expr->to_string() ==
                  "sin(exp(-(-(-8.000000))) - ((-(-5.000000)) + "
                  "((-sin((-2.000000) - (-9.000000))) - 0.000000)))");
        delete expr;
        Expr_node *expr1 = make_plus(make_number(3), make_number(4));
        Expr_node *expr2 = make_negation(expr1);
        OJ_ASSERT(double_eq(expr1->eval(), 7));
        OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
        delete expr2;
        break;
      }
    }
    return 0;
  }
};

int main() {
  int testcase;
  std::cin >> testcase;
  switch (testcase) {
    case 1: {
      // 1 and 2 are simple cases with shorter expression and no make_negation.
      Expr_node *expr = make_minus(
          make_multiply(make_number(9), make_number(1)), make_number(-1));
      OJ_ASSERT(double_eq(expr->eval(), 10));
      OJ_ASSERT(expr->to_string() == "((9.000000 * 1.000000) - (-1.000000))");
      delete expr;
      expr =
          make_divide(make_number(3),
                      make_plus(make_multiply(make_number(6), make_number(9)),
                                make_number(4)));
      OJ_ASSERT(double_eq(expr->eval(), 0.05172413793103448));
      OJ_ASSERT(expr->to_string() ==
                "(3.000000 / ((6.000000 * 9.000000) + 4.000000))");
      delete expr;
      expr = make_plus(make_divide(make_number(-2), make_number(6)),
                       make_plus(make_number(-8), make_number(-6)));
      OJ_ASSERT(double_eq(expr->eval(), -14.333333333333334));
      OJ_ASSERT(expr->to_string() ==
                "(((-2.000000) / 6.000000) + ((-8.000000) + (-6.000000)))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_multiply(make_number(5), expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    case 2: {
      Expr_node *expr =
          make_plus(make_number(-6),
                    make_divide(make_number(8),
                                make_divide(make_number(-8),
                                            make_divide(make_number(-8),
                                                        make_number(-1)))));
      OJ_ASSERT(double_eq(expr->eval(), -14.0));
      OJ_ASSERT(expr->to_string() == "((-6.000000) + (8.000000 / ((-8.000000) "
                                     "/ ((-8.000000) / (-1.000000)))))");
      delete expr;
      expr = make_multiply(make_multiply(make_number(-1), make_number(-9)),
                           make_number(-4));
      OJ_ASSERT(double_eq(expr->eval(), -36));
      OJ_ASSERT(expr->to_string() ==
                "(((-1.000000) * (-9.000000)) * (-4.000000))");
      delete expr;
      expr = make_plus(make_multiply(make_number(-5), make_number(-6)),
                       make_minus(make_number(6), make_number(2)));
      OJ_ASSERT(double_eq(expr->eval(), 34));
      OJ_ASSERT(expr->to_string() ==
                "(((-5.000000) * (-6.000000)) + (6.000000 - 2.000000))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_plus(make_number(5), expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    case 3: {
      Expr_node *expr = make_minus(
          make_number(-5),
          make_divide(
              make_negation(make_number(0)),
              make_multiply(
                  make_number(-9),
                  make_multiply(make_number(4),
                                make_multiply(make_number(-1),
                                              make_divide(make_number(-2),
                                                          make_number(-4)))))));
      OJ_ASSERT(double_eq(expr->eval(), -5.0));
      OJ_ASSERT(expr->to_string() ==
                "((-5.000000) - ((-0.000000) / ((-9.000000) * (4.000000 * "
                "((-1.000000) * ((-2.000000) / (-4.000000)))))))");
      delete expr;
      expr = make_plus(make_plus(make_negation(make_minus(make_number(-10),
                                                          make_number(10))),
                                 make_number(-7)),
                       make_minus(make_number(4),
                                  make_divide(make_number(8),
                                              make_multiply(make_number(10),
                                                            make_number(2)))));
      OJ_ASSERT(double_eq(expr->eval(), 16.6));
      OJ_ASSERT(expr->to_string() ==
                "(((-((-10.000000) - 10.000000)) + (-7.000000)) + (4.000000 - "
                "(8.000000 / (10.000000 * 2.000000))))");
      delete expr;
      expr = make_minus(
          make_negation(make_number(-5)),
          make_minus(
              make_number(8),
              make_plus(make_number(8),
                        make_plus(make_minus(make_number(-7), make_number(-8)),
                                  make_number(5)))));
      OJ_ASSERT(double_eq(expr->eval(), 11));
      OJ_ASSERT(expr->to_string() ==
                "((-(-5.000000)) - (8.000000 - (8.000000 + (((-7.000000) - "
                "(-8.000000)) + 5.000000))))");
      delete expr;
      expr = make_multiply(
          make_multiply(
              make_divide(make_multiply(make_number(-6), make_number(3)),
                          make_number(-6)),
              make_number(-2)),
          make_multiply(make_number(-7),
                        make_minus(make_number(10), make_number(-2))));
      OJ_ASSERT(double_eq(expr->eval(), 504.0));
      OJ_ASSERT(expr->to_string() ==
                "(((((-6.000000) * 3.000000) / (-6.000000)) * (-2.000000)) * "
                "((-7.000000) * (10.000000 - (-2.000000))))");
      delete expr;
      expr = make_minus(
          make_multiply(make_number(9), make_number(-1)),
          make_multiply(
              make_negation(make_number(5)),
              make_plus(make_minus(make_number(-2), make_number(-2)),
                        make_divide(make_number(10), make_number(-8)))));
      OJ_ASSERT(double_eq(expr->eval(), -15.25));
      OJ_ASSERT(expr->to_string() ==
                "((9.000000 * (-1.000000)) - ((-5.000000) * (((-2.000000) - "
                "(-2.000000)) + (10.000000 / (-8.000000)))))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_minus(make_number(5), expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    case 4: {
      Expr_node *expr = make_plus(
          make_negation(make_number(-5)),
          make_multiply(
              make_minus(make_number(5), make_number(-9)),
              make_multiply(make_divide(make_number(9), make_number(5)),
                            make_plus(make_number(-6), make_number(-3)))));
      OJ_ASSERT(double_eq(expr->eval(), -221.79999999999998));
      OJ_ASSERT(expr->to_string() ==
                "((-(-5.000000)) + ((5.000000 - (-9.000000)) * ((9.000000 / "
                "5.000000) * ((-6.000000) + (-3.000000)))))");
      delete expr;
      expr = make_negation(
          make_plus(make_divide(make_divide(make_number(-5), make_number(-2)),
                                make_divide(make_number(2), make_number(6))),
                    make_number(10)));
      OJ_ASSERT(double_eq(expr->eval(), -17.5));
      OJ_ASSERT(expr->to_string() == "(-((((-5.000000) / (-2.000000)) / "
                                     "(2.000000 / 6.000000)) + 10.000000))");
      delete expr;
      expr = make_multiply(
          make_plus(make_number(-1), make_number(10)),
          make_divide(
              make_number(9),
              make_divide(
                  make_number(6),
                  make_multiply(
                      make_number(7),
                      make_minus(make_number(2),
                                 make_minus(make_number(-5),
                                            make_multiply(make_number(8),
                                                          make_number(5))))))));
      OJ_ASSERT(double_eq(expr->eval(), 4441.5));
      OJ_ASSERT(
          expr->to_string() ==
          "(((-1.000000) + 10.000000) * (9.000000 / (6.000000 / (7.000000 * "
          "(2.000000 - ((-5.000000) - (8.000000 * 5.000000)))))))");
      delete expr;
      expr = make_minus(
          make_multiply(make_number(8), make_number(-10)),
          make_minus(make_divide(make_plus(make_number(-9), make_number(-9)),
                                 make_number(2)),
                     make_minus(make_number(6), make_number(-9))));
      OJ_ASSERT(double_eq(expr->eval(), -56.0));
      OJ_ASSERT(expr->to_string() ==
                "((8.000000 * (-10.000000)) - ((((-9.000000) + (-9.000000)) / "
                "2.000000) - (6.000000 - (-9.000000))))");
      delete expr;
      expr = make_plus(
          make_number(-8),
          make_minus(make_multiply(make_number(2), make_number(1)),
                     make_multiply(make_divide(make_number(-9), make_number(3)),
                                   make_number(7))));
      OJ_ASSERT(double_eq(expr->eval(), 15.0));
      OJ_ASSERT(expr->to_string() == "((-8.000000) + ((2.000000 * 1.000000) - "
                                     "(((-9.000000) / 3.000000) * 7.000000)))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_divide(make_number(5), expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    case 5: {
      Expr_node *expr = make_plus(
          make_number(4),
          make_divide(make_minus(make_number(10), make_number(-5)),
                      make_plus(make_minus(make_number(-6), make_number(-8)),
                                make_multiply(make_number(-3),
                                              make_divide(make_number(5),
                                                          make_number(-10))))));
      OJ_ASSERT(double_eq(expr->eval(), 8.285714285714285));
      OJ_ASSERT(expr->to_string() ==
                "(4.000000 + ((10.000000 - (-5.000000)) / (((-6.000000) - "
                "(-8.000000)) + ((-3.000000) * (5.000000 / (-10.000000))))))");
      delete expr;
      expr = make_divide(
          make_plus(make_number(-1), make_number(-6)),
          make_divide(make_number(8),
                      make_minus(make_minus(make_number(-4), make_number(-7)),
                                 make_number(-7))));
      OJ_ASSERT(double_eq(expr->eval(), -8.75));
      OJ_ASSERT(expr->to_string() ==
                "(((-1.000000) + (-6.000000)) / (8.000000 / (((-4.000000) - "
                "(-7.000000)) - (-7.000000))))");
      delete expr;
      expr = make_plus(
          make_divide(make_number(-8),
                      make_plus(make_divide(make_number(8),
                                            make_negation(make_number(-6))),
                                make_number(9))),
          make_number(-3));
      OJ_ASSERT(double_eq(expr->eval(), -3.774193548387097));
      OJ_ASSERT(expr->to_string() ==
                "(((-8.000000) / ((8.000000 / (-(-6.000000))) + 9.000000)) + "
                "(-3.000000))");
      delete expr;
      expr = make_minus(
          make_number(3),
          make_plus(make_number(-1),
                    make_negation(make_divide(
                        make_plus(make_divide(make_number(-4), make_number(-7)),
                                  make_number(7)),
                        make_number(3)))));
      OJ_ASSERT(double_eq(expr->eval(), 6.523809523809524));
      OJ_ASSERT(expr->to_string() ==
                "(3.000000 - ((-1.000000) + (-((((-4.000000) / (-7.000000)) + "
                "7.000000) / 3.000000))))");
      delete expr;
      expr = make_divide(
          make_number(-9),
          make_multiply(
              make_number(6),
              make_plus(
                  make_number(-8),
                  make_minus(
                      make_number(-8),
                      make_divide(make_negation(make_number(-3)),
                                  make_multiply(make_number(-9),
                                                make_plus(make_number(3),
                                                          make_number(2))))))));
      OJ_ASSERT(double_eq(expr->eval(), 0.09414225941422595));
      OJ_ASSERT(expr->to_string() ==
                "((-9.000000) / (6.000000 * ((-8.000000) + ((-8.000000) - "
                "((-(-3.000000)) / ((-9.000000) * (3.000000 + 2.000000)))))))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_negation(expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    case 6: {
      Expr_node *expr = make_divide(
          make_negation(make_number(7)),
          make_multiply(make_plus(make_number(-8),
                                  make_divide(make_number(-2), make_number(9))),
                        make_number(-7)));
      OJ_ASSERT(double_eq(expr->eval(), -0.12162162162162163));
      OJ_ASSERT(expr->to_string() ==
                "((-7.000000) / (((-8.000000) + ((-2.000000) / 9.000000)) * "
                "(-7.000000)))");
      delete expr;
      expr = make_minus(
          make_minus(make_number(-6),
                     make_minus(make_number(-6), make_number(8))),
          make_multiply(make_number(0),
                        make_divide(make_minus(make_number(8), make_number(2)),
                                    make_number(6))));
      OJ_ASSERT(double_eq(expr->eval(), 8.0));
      OJ_ASSERT(expr->to_string() ==
                "(((-6.000000) - ((-6.000000) - 8.000000)) - (0.000000 * "
                "((8.000000 - 2.000000) / 6.000000)))");
      delete expr;
      expr = make_divide(
          make_multiply(make_number(-1), make_number(-1)),
          make_minus(
              make_number(-3),
              make_divide(make_negation(make_number(7)),
                          make_multiply(make_number(-6),
                                        make_negation(make_number(-7))))));
      OJ_ASSERT(double_eq(expr->eval(), -0.31578947368421056));
      OJ_ASSERT(expr->to_string() ==
                "(((-1.000000) * (-1.000000)) / ((-3.000000) - ((-7.000000) / "
                "((-6.000000) * (-(-7.000000))))))");
      delete expr;
      expr = make_divide(
          make_number(9),
          make_multiply(
              make_number(4),
              make_minus(make_minus(make_number(0), make_plus(make_number(-9),
                                                              make_number(-7))),
                         make_minus(make_number(9), make_number(-9)))));
      OJ_ASSERT(double_eq(expr->eval(), -1.125));
      OJ_ASSERT(expr->to_string() ==
                "(9.000000 / (4.000000 * ((0.000000 - ((-9.000000) + "
                "(-7.000000))) - (9.000000 - (-9.000000)))))");
      delete expr;
      expr = make_minus(
          make_negation(
              make_multiply(make_negation(make_number(-1)), make_number(-10))),
          make_multiply(
              make_number(-7),
              make_multiply(make_number(-3),
                            make_divide(make_number(-7), make_number(-2)))));
      OJ_ASSERT(double_eq(expr->eval(), -63.5));
      OJ_ASSERT(expr->to_string() ==
                "((-((-(-1.000000)) * (-10.000000))) - ((-7.000000) * "
                "((-3.000000) * ((-7.000000) / (-2.000000)))))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_multiply(make_number(5), expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    case 7: {
      Expr_node *expr = make_plus(
          make_number(-2),
          make_multiply(make_divide(make_number(-10),
                                    make_minus(make_divide(make_number(9),
                                                           make_number(-4)),
                                               make_number(-9))),
                        make_multiply(make_number(7), make_number(4))));
      OJ_ASSERT(double_eq(expr->eval(), -43.48148148148148));
      OJ_ASSERT(expr->to_string() ==
                "((-2.000000) + (((-10.000000) / ((9.000000 / (-4.000000)) - "
                "(-9.000000))) * (7.000000 * 4.000000)))");
      delete expr;
      expr = make_minus(
          make_divide(make_number(-8), make_number(-1)),
          make_plus(make_number(-10),
                    make_multiply(
                        make_number(5),
                        make_minus(make_minus(make_number(-8), make_number(5)),
                                   make_number(2)))));
      OJ_ASSERT(double_eq(expr->eval(), 93.0));
      OJ_ASSERT(expr->to_string() ==
                "(((-8.000000) / (-1.000000)) - ((-10.000000) + (5.000000 * "
                "(((-8.000000) - 5.000000) - 2.000000))))");
      delete expr;
      expr = make_multiply(
          make_plus(make_number(6), make_number(10)),
          make_multiply(
              make_number(9),
              make_minus(make_minus(make_divide(make_number(2), make_number(4)),
                                    make_number(-10)),
                         make_number(-8))));
      OJ_ASSERT(double_eq(expr->eval(), 2664.0));
      OJ_ASSERT(expr->to_string() ==
                "((6.000000 + 10.000000) * (9.000000 * (((2.000000 / 4.000000) "
                "- (-10.000000)) - (-8.000000))))");
      delete expr;
      expr = make_divide(
          make_number(-2),
          make_multiply(
              make_number(-5),
              make_divide(
                  make_number(7),
                  make_plus(make_number(5),
                            make_divide(
                                make_multiply(make_number(6), make_number(-5)),
                                make_minus(make_number(2),
                                           make_multiply(make_number(9),
                                                         make_number(-5))))))));
      OJ_ASSERT(double_eq(expr->eval(), 0.24924012158054715));
      OJ_ASSERT(
          expr->to_string() ==
          "((-2.000000) / ((-5.000000) * (7.000000 / (5.000000 + ((6.000000 * "
          "(-5.000000)) / (2.000000 - (9.000000 * (-5.000000))))))))");
      delete expr;
      expr = make_minus(
          make_multiply(make_number(6), make_negation(make_number(-4))),
          make_minus(
              make_number(-2),
              make_plus(make_number(5),
                        make_minus(make_number(-2),
                                   make_minus(make_number(-1),
                                              make_divide(make_number(4),
                                                          make_number(-3)))))));
      OJ_ASSERT(double_eq(expr->eval(), 28.666666666666668));
      OJ_ASSERT(expr->to_string() ==
                "((6.000000 * (-(-4.000000))) - ((-2.000000) - (5.000000 + "
                "((-2.000000) - ((-1.000000) - (4.000000 / (-3.000000)))))))");
      delete expr;
      Expr_node *expr1 = make_plus(make_number(3), make_number(4));
      Expr_node *expr2 = make_plus(make_number(5), expr1);
      OJ_ASSERT(double_eq(expr1->eval(), 7));
      OJ_ASSERT(expr1->to_string() == "(3.000000 + 4.000000)");
      delete expr2;
      break;
    }
    default: { // 8, 9, 10 are for part 2
      test_part2<details::part2_implemented>::test(testcase);
      break;
    }
  }
  std::cout << testcase << std::endl;
  return 0;
}