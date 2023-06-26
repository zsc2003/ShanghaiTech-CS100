#include "point.hpp"
#include <functional>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

#define main __student_main_function_
#define _ONLINE_JUDGE

/*****************************************/

// PASTE OR #include YOUR CODE HERE
#include "handle.hpp"

/*****************************************/

namespace details {

struct public_and_const {};
struct public_not_const {};
struct not_public {};

template <typename T = Point_handle,
          typename = decltype(std::declval<const T>().get_x())>
public_and_const get_x_const_checker(char);

template <typename T = Point_handle,
          typename = decltype(std::declval<T>().get_x())>
public_not_const get_x_const_checker(int);

not_public get_x_const_checker(double);

template <typename T = Point_handle,
          typename = decltype(std::declval<const T>().get_y())>
public_and_const get_y_const_checker(char);

template <typename T = Point_handle,
          typename = decltype(std::declval<T>().get_y())>
public_not_const get_y_const_checker(int);

not_public get_y_const_checker(double);

template <typename T = Point_handle,
          typename = decltype(std::declval<const T>().get_label())>
public_and_const get_label_const_checker(char);

template <typename T = Point_handle,
          typename = decltype(std::declval<T>().get_label())>
public_not_const get_label_const_checker(int);

not_public get_label_const_checker(double);

template <typename T = Point_handle,
          typename = decltype(std::declval<const T>().ref_count())>
public_and_const ref_count_const_checker(char);

template <typename T = Point_handle,
          typename = decltype(std::declval<T>().ref_count())>
public_not_const ref_count_const_checker(int);

not_public ref_count_const_checker(double);

constexpr bool get_x_is_public_not_const =
    std::is_same<decltype(get_x_const_checker('\0')), public_not_const>::value;

constexpr bool get_y_is_public_not_const =
    std::is_same<decltype(get_y_const_checker('\0')), public_not_const>::value;

constexpr bool get_label_is_public_not_const =
    std::is_same<decltype(get_label_const_checker('\0')),
                 public_not_const>::value;

constexpr bool ref_count_is_public_not_const =
    std::is_same<decltype(ref_count_const_checker('\0')),
                 public_not_const>::value;

constexpr bool assignment_return_ref =
    std::is_same<decltype(std::declval<Point_handle>().operator=(
                     std::declval<Point_handle>())),
                 Point_handle &>::value;

constexpr bool set_x_return_ref =
    std::is_same<decltype(std::declval<Point_handle>().set_x(double{})),
                 Point_handle &>::value;

constexpr bool set_y_return_ref =
    std::is_same<decltype(std::declval<Point_handle>().set_y(double{})),
                 Point_handle &>::value;

constexpr bool set_label_return_ref =
    std::is_same<decltype(std::declval<Point_handle>().set_label(
                     std::string{})),
                 Point_handle &>::value;

} // namespace details

static_assert(!details::get_x_is_public_not_const,
              "Why don't you make 'get_x' a const member function? (kind "
              "reminder from GKxx)");

static_assert(!details::get_y_is_public_not_const,
              "Why don't you make 'get_y' a const member function? (kind "
              "reminder from GKxx)");

static_assert(!details::get_label_is_public_not_const,
              "Why don't you make 'get_label' a const member function? (kind "
              "reminder from GKxx)");

static_assert(!details::ref_count_is_public_not_const,
              "Why don't you make 'ref_count' a const member function? (kind "
              "reminder from GKxx)");

static_assert(details::assignment_return_ref,
              "Assignment operator should return reference to the object on "
              "the left-hand side! (kind reminder from GKxx)");

static_assert(details::set_x_return_ref,
              "You should allow the 'chained' member function calling as in "
              "'ph.set_x(4).set_y(10).ref_count()'. (kind reminder from GKxx)");

static_assert(details::set_y_return_ref,
              "You should allow the 'chained' member function calling as in "
              "'ph.set_y(10).set_x(4).ref_count()'. (kind reminder from GKxx)");

static_assert(
    details::set_label_return_ref,
    "You should allow the 'chained' member function calling as in "
    "'ph.set_label(\"A\").set_y(10).ref_count()'. (kind reminder from GKxx)");

static_assert(
    std::is_copy_constructible<Point_handle>::value,
    "Your 'Point_handle' type is not copy-constructible. Please check your "
    "copy-constructor carefully. (kind reminder from GKxx)");

static_assert(
    std::is_copy_assignable<Point_handle>::value,
    "Your 'Point_handle' type is not copy-assignable. Please check your "
    "copy-assignment operator carefully. (kind reminder from GKxx)");

static_assert(std::is_constructible<Point_handle, const Point &>::value,
              "Your 'Point_handle' type is not constructible from a 'const "
              "Point'. Please check the relevant constructor carefully. (kind "
              "reminder from GKxx)");

inline void report_if_wrong(bool result, unsigned line, int testcase) {
  if (!result)
    std::cout << "Wrong answer at line " << line << " on testcase " << testcase
              << std::endl;
}

#ifdef assert
#undef assert
#endif
#define assert(X) report_if_wrong((X), __LINE__, testcase)

#ifdef main
#undef main
#endif

inline bool same_point(const Point_handle &ph, const Point &p) {
  return ph.get_x() == p.get_x() && ph.get_y() == p.get_y() &&
         ph.get_label() == p.get_label();
}

int __attribute__((optimize("O0"))) main() {
  int testcase;
  std::cin >> testcase;
  switch (testcase) {
    case 1: {
      std::vector<Point_handle> vec(10);
      for (const auto &x : vec) {
        assert(same_point(x, Point{}));
        assert(x.ref_count() == 1);
      }
      for (auto i = 0; i != 10; ++i)
        vec.emplace_back(i * 0.3, i * 2.5 + 1, "A_" + std::to_string(i));
      for (auto i = 10; i != 20; ++i)
        assert(same_point(vec[i], Point{(i - 10) * 0.3, (i - 10) * 2.5 + 1,
                                        "A_" + std::to_string(i - 10)}));
      for (const auto &x : vec)
        assert(x.ref_count() == 1);
      for (auto i = 0; i != 10; ++i)
        vec.emplace_back(
            Point{i * 0.5, i * 2.25 + 4, "B_" + std::to_string(i)});
      for (auto i = 20; i != 30; ++i)
        assert(same_point(vec[i], Point{(i - 20) * 0.5, (i - 20) * 2.25 + 4,
                                        "B_" + std::to_string(i - 20)}));
      for (const auto &x : vec)
        assert(x.ref_count() == 1);
      Point_handle p0(1, 2), p1(2, 3), p2(3, 4);
      assert(same_point(p0, Point{1, 2}));
      assert(same_point(p1, Point{2, 3}));
      assert(same_point(p2, Point{3, 4}));
      break;
    }
    case 2: {
      Point p(1, 2, "A");
      Point_handle ph1(p);
      Point_handle ph11(p);
      assert(same_point(ph1, p));
      assert(ph1.ref_count() == 1);
      ph1 = ph1;
      assert(same_point(ph1, p));
      assert(ph1.ref_count() == 1);
      {
        Point_handle ph2(ph1);
        assert(same_point(ph2, p));
        assert(ph1.ref_count() == 2);
        assert(ph2.ref_count() == 2);
        {
          Point_handle ph3(ph2);
          assert(same_point(ph3, p));
          assert(ph1.ref_count() == 3);
          assert(ph2.ref_count() == 3);
          assert(ph3.ref_count() == 3);
          {
            Point_handle ph4(ph1);
            assert(same_point(ph4, p));
            assert(ph1.ref_count() == 4);
            assert(ph2.ref_count() == 4);
            assert(ph3.ref_count() == 4);
            assert(ph4.ref_count() == 4);
          }
          assert(same_point(ph3, p));
          assert(ph1.ref_count() == 3);
          assert(ph2.ref_count() == 3);
          assert(ph3.ref_count() == 3);
        }
        assert(same_point(ph2, p));
        assert(ph1.ref_count() == 2);
        assert(ph2.ref_count() == 2);
      }
      assert(same_point(ph1, p));
      assert(ph1.ref_count() == 1);
      break;
    }
    case 3: {
      std::vector<Point_handle> pvec;
      pvec.reserve(800000);
      for (auto i = 0; i != 200000; ++i)
        pvec.emplace_back(i + 0.0, i + 1.0, "A");
      for (auto i = 200000; i != 400000; ++i)
        pvec.emplace_back(pvec[i - 200000]);
      for (auto i = 400000; i != 600000; ++i) {
        pvec.emplace_back();
        pvec.back() = pvec[i - 400000];
      }
      for (auto i = 600000; i != 800000; ++i) {
        pvec.emplace_back();
        pvec.back() = pvec[i - 600000];
        pvec.back() = Point_handle(i * 2.0, i * 3.0, "B");
      }
      for (auto i = 0; i != 200000; ++i) {
        assert(same_point(pvec[i], Point{i + 0.0, i + 1.0, "A"}));
        assert(same_point(pvec[i + 200000], Point{i + 0.0, i + 1.0, "A"}));
        assert(same_point(pvec[i + 400000], Point{i + 0.0, i + 1.0, "A"}));
        assert(pvec[i].ref_count() == 3);
        assert(pvec[i + 200000].ref_count() == 3);
        assert(pvec[i + 400000].ref_count() == 3);
      }
      for (auto i = 600000; i != 800000; ++i) {
        assert(same_point(pvec[i], Point{i * 2.0, i * 3.0, "B"}));
        assert(pvec[i].ref_count() == 1);
      }
      break;
    }
    case 4: {
      Point_handle ph1(1, 2, "A");
      Point_handle ph2 = ph1;
      assert(same_point(ph1, Point{1, 2, "A"}));
      assert(same_point(ph2, Point{1, 2, "A"}));
      assert(ph1.ref_count() == 2);
      assert(ph2.ref_count() == 2);
      ph2.set_x(30).set_y(40).set_label("B").set_x(50);
      assert(same_point(ph2, Point{50, 40, "B"}));
      assert(same_point(ph1, Point{1, 2, "A"}));
      assert(ph1.ref_count() == 1);
      assert(ph2.ref_count() == 1);
      Point_handle ph3 = ph2;
      Point_handle ph4 = ph1;
      ph4 = ph3;
      assert(same_point(ph1, Point{1, 2, "A"}));
      assert(same_point(ph3, Point{50, 40, "B"}));
      assert(same_point(ph4, Point{50, 40, "B"}));
      assert(ph2.ref_count() == 3);
      assert(ph3.ref_count() == 3);
      assert(ph4.ref_count() == 3);
      assert(ph1.ref_count() == 1);
      ph2.set_x(70);
      assert(same_point(ph2, Point{70, 40, "B"}));
      assert(ph2.ref_count() == 1);
      assert(ph3.ref_count() == 2);
      assert(ph4.ref_count() == 2);
      Point_handle ph5;
      ph5 = ph5;
      ph5 = ph4;
      ph4.set_y(100).set_label("C");
      assert(same_point(ph4, Point{50, 100, "C"}));
      assert(same_point(ph5, Point{50, 40, "B"}));
      assert(same_point(ph3, Point{50, 40, "B"}));
      assert(ph4.ref_count() == 1);
      assert(ph3.ref_count() == 2);
      assert(ph5.ref_count() == 2);
      break;
    }
    case 5: {
      Point p(1, 2, "A");
      Point_handle ph1(p);
      Point_handle ph11(p);
      assert(same_point(ph1, p));
      assert(ph1.ref_count() == 1);
      {
        Point_handle ph2;
        ph2 = ph1;
        ph2 = ph2;
        assert(same_point(ph2, p));
        assert(ph1.ref_count() == 2);
        assert(ph2.ref_count() == 2);
        {
          Point_handle ph3 = ph2;
          ph3 = ph1;
          ph3 = ph3;
          ph3 = ph2;
          assert(same_point(ph3, p));
          assert(ph1.ref_count() == 3);
          assert(ph2.ref_count() == 3);
          assert(ph3.ref_count() == 3);
          {
            Point_handle ph4;
            ph4 = ph4;
            ph4 = ph4;
            ph4 = ph2;
            ph4 = ph3 = ph3;
            assert(same_point(ph4, p));
            assert(ph1.ref_count() == 4);
            assert(ph2.ref_count() == 4);
            assert(ph3.ref_count() == 4);
            assert(ph4.ref_count() == 4);
            ph3.set_x(40);
            assert(same_point(ph3, Point{40, 2, "A"}));
            assert(ph3.ref_count() == 1);
            assert(ph1.ref_count() == 3);
            assert(ph2.ref_count() == 3);
            assert(ph4.ref_count() == 3);
          }
          assert(same_point(ph3, Point{40, 2, "A"}));
          assert(ph1.ref_count() == 2);
          assert(ph2.ref_count() == 2);
          assert(ph3.ref_count() == 1);
          ph3.set_x(1).set_y(2).set_label("A");
          assert(same_point(ph3, p));
          assert(ph1.ref_count() == 2);
          assert(ph2.ref_count() == 2);
          assert(ph3.ref_count() == 1);
          ph3 = ph1;
          assert(same_point(ph3, p));
          assert(ph1.ref_count() == 3);
          assert(ph2.ref_count() == 3);
          assert(ph3.ref_count() == 3);
        }
        assert(same_point(ph2, p));
        assert(ph1.ref_count() == 2);
        assert(ph2.ref_count() == 2);
      }
      assert(same_point(ph1, p));
      assert(ph1.ref_count() == 1);
      break;
    }
  }
  std::cout << testcase << std::endl;
  return 0;
}