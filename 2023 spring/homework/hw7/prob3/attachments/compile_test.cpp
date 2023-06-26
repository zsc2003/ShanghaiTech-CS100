#include "polynomial.hpp"

#include <type_traits>
#include <iostream>

namespace detail {

  static_assert(std::is_default_constructible_v<Polynomial>);
  static_assert(!std::is_trivially_default_constructible_v<Polynomial>);
  static_assert(std::is_constructible_v<Polynomial, const std::vector<double>>);
  static_assert(!std::is_convertible_v<const std::vector<double>, Polynomial>);
  static_assert(std::is_copy_constructible_v<Polynomial>);
  static_assert(std::is_copy_assignable_v<Polynomial>);
  static_assert(std::is_move_constructible_v<Polynomial>);
  static_assert(std::is_move_assignable_v<Polynomial>);

  struct unknown_input_iter {
    using value_type = double;
    using reference = const double &;
    using pointer = const double *;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::input_iterator_tag;
    
    reference operator*() const;
    pointer operator->() const;
    unknown_input_iter &operator++();
    unknown_input_iter operator++(int);
    bool operator==(const unknown_input_iter &) const;
    bool operator!=(const unknown_input_iter &) const;
  };

  static_assert(std::is_constructible_v<Polynomial, const unknown_input_iter,
                                        const unknown_input_iter>);

  template <typename T = const Polynomial,
            typename U = decltype(std::declval<T>().deg()),
            typename = std::enable_if_t<std::is_integral_v<U>>>
  std::true_type test_deg(int);
  std::false_type test_deg(...);
  static_assert(decltype(test_deg(0))::value,
                "Expect { cp.deg() } -> integral, "
                "with the setting (Polynomial p, const Polynomial cp, "
                "std::size_t i, double x).");

  template <typename T, typename... Types>
  using enable_if_any = std::enable_if_t<(std::is_same_v<T, Types> || ...)>;

#define EXPECT(NAME, EXPR, ...)                                                \
  template <typename P = Polynomial, typename CP = const Polynomial,           \
            typename R = decltype(EXPR),                                       \
            typename = enable_if_any<R, __VA_ARGS__>>                          \
  std::true_type test_##NAME(int);                                             \
  std::false_type test_##NAME(...);                                            \
  static_assert(decltype(test_##NAME(0))::value,                               \
                "Expect { " #EXPR " } -> any_of {" #__VA_ARGS__                \
                "}, with the setting (Polynomial p, const Polynomial cp, "     \
                "std::size_t i, double x).");

#define p std::declval<P &>()
#define cp std::declval<CP &>()
#define i std::size_t{}
#define x double{}

  EXPECT(subscript,       p[i],             double, const double, const double &)
  EXPECT(const_subscript, cp[i],            double, const double, const double &)
  EXPECT(setter,          p.setCoeff(i, x), void)
  EXPECT(evaluate,        p(x),             double, const double)
  EXPECT(const_evaluate,  cp(x),            double, const double)
  EXPECT(negate,          -cp,              Polynomial, const Polynomial)
  EXPECT(plus,            cp + cp,          Polynomial, const Polynomial)
  EXPECT(minus,           cp - cp,          Polynomial, const Polynomial)
  EXPECT(multiply,        cp * cp,          Polynomial, const Polynomial)
  EXPECT(add_assign,      p += cp,          Polynomial &)
  EXPECT(minus_assign,    p -= cp,          Polynomial &)
  EXPECT(multiply_assign, p *= cp,          Polynomial &)
  EXPECT(derivative,      cp.derivative(),  Polynomial, const Polynomial)
  EXPECT(integral,        cp.integral(),    Polynomial, const Polynomial)
  EXPECT(equal,           cp == cp,         bool)
  EXPECT(not_equal,       cp != cp,         bool)

#undef p
#undef cp
#undef i
#undef x
#undef EXPECT

template <typename Ret, typename Class, bool NE, typename... Params>
void memfun_match(Ret (Class::*)(Params...) noexcept(NE));

#define ONLY_CONST_TEST(NAME, MEMFUN)                                          \
  template <typename T = Polynomial,                                           \
            typename = decltype(memfun_match(&T::MEMFUN))>                     \
  std::false_type helper_##NAME(int);                                          \
  std::true_type helper_##NAME(...);                                           \
  static_assert(decltype(helper_##NAME(0))::value,                             \
                "Why do you have a non-const \'Polynomial::" #MEMFUN "\'?");

ONLY_CONST_TEST(deg, deg)
ONLY_CONST_TEST(derivative, derivative)
ONLY_CONST_TEST(integral, integral)
ONLY_CONST_TEST(function_call_operator, operator())

#undef ONLY_CONST_TEST
} // namespace detail

int main() {
  std::cout << "Compile-time check passed." << std::endl;
  return 0;
}