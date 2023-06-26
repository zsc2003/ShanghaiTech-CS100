#include "expr.hpp"

#include <type_traits>
#include <string>
#include <iostream>

namespace detail {

static_assert(std::is_copy_constructible_v<Expr>);
static_assert(std::is_copy_assignable_v<Expr>);
static_assert(std::is_nothrow_move_constructible_v<Expr>);
static_assert(std::is_nothrow_move_assignable_v<Expr>);
static_assert(std::is_constructible_v<Expr, const double>);
static_assert(std::is_convertible_v<const double, Expr>);

template <typename T, typename... U>
using enable_if_any = std::enable_if_t<(std::is_same_v<T, U> || ...)>;

#define EXPECT(NAME, EXPR, ...)                                                \
  template <typename E = const Expr,                                           \
            typename R = decltype(EXPR),                                       \
            typename = enable_if_any<R, __VA_ARGS__>>                          \
  std::true_type helper_##NAME(int);                                           \
  std::false_type helper_##NAME(...);                                          \
  static_assert(decltype(helper_##NAME(0))::value,                             \
                "Expect { " #EXPR " } -> any_of {" #__VA_ARGS__                \
                "}, with the setting (const Expr e, double d).");

#define e std::declval<E &>()
#define d double{}

EXPECT(eval,       e.eval(d),       double, const double)
EXPECT(derivative, e.derivative(d), double, const double)
EXPECT(rep,        e.rep(),         std::string, const std::string)
EXPECT(x,          Expr::x,         const Expr)
EXPECT(negative,   -e,              Expr, const Expr)
EXPECT(positive,   +e,              Expr, const Expr)
EXPECT(add,        e + e,           Expr, const Expr)
EXPECT(minus,      e - e,           Expr, const Expr)
EXPECT(multiply,   e * e,           Expr, const Expr)
EXPECT(divide,     e / e,           Expr, const Expr)

#undef e
#undef d
#undef EXPECT

} // namespace detail

int main() {
  std::cout << "Compile-time check passed." << std::endl;
  return 0;
}