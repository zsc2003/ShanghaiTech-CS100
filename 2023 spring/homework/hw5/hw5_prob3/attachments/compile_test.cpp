#include <iostream>
#include <type_traits>
#include <utility>

#include "dynarray.hpp"

#if __cplusplus < 201703L
#error At least C++17 is required.
#endif

static_assert(std::is_default_constructible_v<Dynarray>,
              "`Dynarray` should be default constructible.");

static_assert(std::is_constructible_v<Dynarray, std::size_t>,
              "The constructor `Dynarray(n)` should be supported.");

static_assert(!std::is_convertible_v<std::size_t, Dynarray>,
              "The constructor `Dynarray(n)` should be explicit.");

static_assert(std::is_constructible_v<Dynarray, std::size_t, int>,
              "The constructor `Dynarray(n, x)` should be supported.");

static_assert(std::is_constructible_v<Dynarray, const int *, const int *>,
              "The constructor `Dynarray(begin, end)` should be supported.");

static_assert(std::is_copy_constructible_v<Dynarray>,
              "`Dynarray` should be copy constructible.");

static_assert(std::is_copy_assignable_v<Dynarray>,
              "`Dynarray` should be copy assignable.");

static_assert(
    std::is_same_v<Dynarray &, decltype(std::declval<Dynarray>() =
                                            std::declval<Dynarray>())>,
    "Why doesn't your copy-assignment operator return reference to the "
    "left-hand side object?");

namespace detail {

#define DEFINE_DETECTER(LABEL, OBJECT, MEMFCN, RET, ...)                       \
  template <typename T = OBJECT,                                               \
            typename U = decltype(std::declval<T>().MEMFCN(__VA_ARGS__)),      \
            typename = std::enable_if_t<std::is_same_v<U, RET>>>               \
  std::true_type detect_##LABEL(int);                                          \
  std::false_type detect_##LABEL(...);                                         \
  inline constexpr auto LABEL##_correct = decltype(detect_##LABEL(0))::value;

DEFINE_DETECTER(size, const Dynarray, size, std::size_t, )

DEFINE_DETECTER(empty, const Dynarray, empty, bool, )

DEFINE_DETECTER(at, Dynarray, at, int &, std::size_t{})

DEFINE_DETECTER(const_at, const Dynarray, at, const int &, std::size_t{})

#undef DEFINE_DETECTER

} // namespace detail

static_assert(detail::size_correct,
              "Dynarray::size() not defined or incorrect.");

static_assert(detail::empty_correct,
              "Dynarray::empty() not defined or incorrect.");

static_assert(detail::at_correct,
              "Dynarray::at(n) (non-const version) not defined or incorrect.");

static_assert(detail::const_at_correct,
              "Dynarray::at(n) (const version) not defined or incorrect.");

int main() {
  std::cout << "Compile-time check passed." << std::endl;
  return 0;
}