#include "expr.hpp"

#include <type_traits>
#include <string>
#include <iostream>

static_assert(std::is_copy_constructible_v<Expr>);
static_assert(std::is_copy_assignable_v<Expr>);
static_assert(std::is_nothrow_move_constructible_v<Expr>);
static_assert(std::is_nothrow_move_assignable_v<Expr>);
static_assert(std::is_constructible_v<Expr, const double>);
static_assert(std::is_convertible_v<const double, Expr>);

template <typename T, typename U>
using enable_if_same = std::enable_if_t<std::is_same_v<T, U>>;

#define EXPECT(name, expr, type)                                               \
  template <typename E = const Expr, typename R = decltype(expr),              \
            typename = enable_if_same<R, type>>                                \
  std::true_type helper_##name(int);                                           \
  std::false_type helper_##name(...);                                          \
  static_assert(decltype(helper_##name(0))::value,                             \
                "Expect { " #expr " } -> " #type                               \
                ", with the setting (const Expr e, double d).");

#define e std::declval<E &>()
#define d double{}

EXPECT(evaluate,   e.evaluate(d),   double)
EXPECT(derivative, e.derivative(d), double)
EXPECT(toString,   e.toString(),    std::string)
EXPECT(x,          Expr::x,         const Expr)
EXPECT(negative,   -e,              Expr)
EXPECT(positive,   +e,              Expr)
EXPECT(add,        e + e,           Expr)
EXPECT(minus,      e - e,           Expr)
EXPECT(multiply,   e * e,           Expr)
EXPECT(divide,     e / e,           Expr)

#undef e
#undef d
#undef EXPECT

int main() {
  std::cout << "Compile-time check passed." << std::endl;
  return 0;
}