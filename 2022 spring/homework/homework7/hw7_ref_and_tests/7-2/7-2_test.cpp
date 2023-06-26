#include "../memcheck/memcheck.hpp"

#define main __student_main_function_
#define _ONLINE_JUDGE

/************************************************************************/

// PASTE OR #include YOUR CODE HERE

/************************************************************************/

#ifdef main
#undef main
#endif

#include <algorithm>
#include <forward_list>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

template <typename T>
void test_ctor_front();

template <typename T>
void test_inc();

template <typename T>
void test_assignment_front();

template <typename T>
void test_compare();

class Special_type {
  int x;

 public:
  Special_type() = delete;
  Special_type(const Special_type &) = default;
  Special_type &operator=(const Special_type &) = delete;
  int get() const {
    return x;
  }

 private:
  // This constructor is not explicit.
  Special_type(int xx) : x(xx) {}

  friend void test_ctor_front<Special_type>();
  friend void test_inc<Special_type>();
  friend void test_assignment_front<Special_type>();
  friend void test_insert_special();
  friend void test_compare<Special_type>();

  friend bool operator==(const Special_type &lhs, const Special_type &rhs) {
    return lhs.get() == rhs.get();
  }

  friend bool operator<(const Special_type &lhs, const Special_type &rhs) {
    return lhs.get() < rhs.get();
  }

  friend bool operator!=(const Special_type &lhs,
                         const Special_type &rhs) = delete;

  friend bool operator<=(const Special_type &lhs,
                         const Special_type &rhs) = delete;

  friend bool operator>(const Special_type &lhs,
                        const Special_type &rhs) = delete;

  friend bool operator>=(const Special_type &lhs,
                         const Special_type &rhs) = delete;
};

namespace compile_check {

static_assert(std::is_default_constructible<Slist<int>>::value,
              "Slist should be default-constructible.");

static_assert(std::is_copy_constructible<Slist<int>>::value,
              "Slist should be copy-constructible.");

static_assert(std::is_copy_assignable<Slist<int>>::value,
              "Slist should be copy-assignable.");

static_assert(
    std::is_same<decltype(++std::declval<Slist_iterator<int, false>>()),
                 Slist_iterator<int, false> &>::value,
    "Prefix operator++ should return reference to the object itself.");

namespace detail {

  template <typename T = Slist_iterator<int, false>,
            typename = decltype(((const T *)nullptr)->operator*())>
  std::true_type deref_const_helper(int);

  std::false_type deref_const_helper(double);

  constexpr bool deref_is_const = decltype(deref_const_helper(0))::value;

  template <typename T = Slist<int>,
            typename = decltype(((const T *)nullptr)->size())>
  std::true_type size_const_helper(int);

  std::false_type size_const_helper(double);

  constexpr bool size_is_const = decltype(size_const_helper(0))::value;

  template <typename T = Slist<int>,
            typename = decltype(((const T *)nullptr)->empty())>
  std::true_type empty_const_helper(int);

  std::false_type empty_const_helper(double);

  constexpr bool empty_is_const = decltype(empty_const_helper(0))::value;

  constexpr bool size_return_size_type =
      std::is_same<decltype(std::declval<Slist<int>>().size()),
                   Slist<int>::size_type>::value;

  constexpr bool assignment_return_ref =
      std::is_same<decltype(std::declval<Slist<int>>().operator=(
                       std::declval<Slist<int>>())),
                   Slist<int> &>::value;

} // namespace detail

static_assert(detail::deref_is_const,
              "Why don't you define Slist_iterator::operator* as a const "
              "member function?");

static_assert(detail::size_is_const,
              "Why don't you define Slist::size as a const member function?");

static_assert(detail::empty_is_const,
              "Why don't you define Slist::empty as a const member function?");

static_assert(
    detail::size_return_size_type,
    "The return-type of Slist<T>::size() should be Slist<T>::size_type.");

static_assert(
    detail::assignment_return_ref,
    "operator= should return reference to the object on the left-hand side.");

} // namespace compile_check

inline void report_if_wrong(bool condition, long line) {
  if (!condition) {
    std::cout << "Wrong answer on line " << line << std::endl;
    exit(0);
  }
}

#ifdef assert
#undef assert
#endif

#define assert(COND) report_if_wrong(COND, __LINE__)

// This testcase is the same as simple_tests.
void test_sample() {
  int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  Slist<int> list;
  for (auto x : a)
    list.push_front(x);
  assert(list.size() == 10);
  assert(!list.empty());
  int num = 0;
  for (auto x : list)
    assert(x == num++);

  for (auto i = 0; i != 5; ++i)
    list.pop_front();
  assert(list.size() == 5);
  assert(!list.empty());
  num = 5;
  for (auto x : list)
    assert(x == num++);

  --*list.begin();
  --*list.begin();
  list.insert_after(list.cbegin(), 5);
  list.insert_after(list.cbegin(), 4);
  assert(list.size() == 7);
  assert(!list.empty());
  num = 3;
  for (auto x : list)
    assert(x == num++);

  for (auto i = 0; i != 4; ++i)
    list.erase_after(list.begin());
  assert(list.size() == 3);
  assert(!list.empty());
  *list.begin() = 7;
  num = 7;
  for (auto x : list)
    assert(x == num++);

  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());
}

template <typename T>
void test_ctor_front() {
  Slist<T> list;
  std::list<T> a = {1, 3, 9, 7, 6, 8, 10, 5, 4, 2};
  for (auto x : a)
    list.push_front(x);
  assert(list.size() == 10);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), a.rbegin()));
  assert(std::equal(list.cbegin(), list.cend(), a.rbegin()));
  Slist<T> l2(list);
  assert(l2.size() == 10);
  assert(!l2.empty());
  assert(std::equal(l2.begin(), l2.end(), list.cbegin()));
  l2.push_front(12);
  l2.push_front(15);
  assert(list.size() == 10);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), a.rbegin()));
  assert(std::equal(list.cbegin(), list.cend(), a.rbegin()));
  assert(l2.size() == 12);
  assert(!l2.empty());
  a.push_back(12);
  a.push_back(15);
  assert(std::equal(l2.begin(), l2.end(), a.rbegin()));
  a.pop_back();
  a.pop_back();
  std::vector<T> v;
  for (auto x : list)
    v.push_back(x);
  assert(std::equal(v.begin(), v.end(), a.rbegin()));
  typename Slist<T>::const_iterator cit = list.begin();
  assert(cit == list.cbegin());
  while (cit != list.end())
    cit++;
  assert(cit == list.end());
  assert(cit == list.cend());
}

inline void test_ctor_front() {
  test_ctor_front<int>();
  test_ctor_front<Special_type>();
}

template <typename T>
void test_inc() {
  T a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  Slist<T> list;
  for (auto x : a)
    list.push_front(x);
  auto it = list.begin();
  int i = 0;
  while (it != list.end()) {
    ++i;
    const auto &cit = it;
    assert(*cit == i);
    assert(*(it++) == i);
  }
  it = list.begin();
  for (auto i = 0; i != 9; ++i)
    assert(*++it == i + 2);
}

inline void test_inc() {
  test_inc<int>();
  test_inc<Special_type>();
}

template <typename T>
void test_assignment_front() {
  T a[] = {10, 11, 4, 14, 12, 1, 7, 0, 2, 13, 9, 6, 5, 3, 8};
  std::list<T> l;
  for (auto x : a)
    l.emplace_front(x);
  Slist<T> list;
  for (auto x : a)
    list.push_front(x);
  assert(list.size() == 15);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), l.begin()));
  Slist<T> list2, list3, list4;
  for (auto it = std::rbegin(a); it != std::rend(a); ++it)
    list2.push_front(*it);
  list3 = list2;
  list3 = list;
  list3 = list4;
  list3 = list2;
  list3 = list3;
  assert(list3.size() == 15);
  assert(!list3.empty());
  assert(std::equal(list3.begin(), list3.end(), a));
  list4 = list4;
  list4 = list3;
  list4 = list2 = list2;
  list4 = static_cast<const Slist<T> &>(list);
  list4 = list4 = list4;
  assert(list4.size() == 15);
  assert(!list4.empty());
  assert(std::equal(list4.begin(), list4.end(), l.begin()));
}

inline void test_assignment_front() {
  test_assignment_front<int>();
  test_assignment_front<Special_type>();
}

void test_pop_front() {
  double a[] = {24.030890368016912, 35.70097978406551,  55.67128058255084,
                40.727731959555605, 58.809606321088104, 94.54495316415048,
                21.978090016900364};
  Slist<double> dl;
  for (auto it = std::rbegin(a); it != std::rend(a); ++it)
    dl.push_front(*it);
  dl.pop_front();
  assert(std::equal(dl.begin(), dl.end(), a + 1));
  dl.pop_front();
  dl.pop_front();
  assert(dl.size() == 4);
  assert(!dl.empty());
  assert(std::equal(dl.begin(), dl.end(), a + 3));
  dl.push_front(314.159265);
  dl.push_front(1.73205080756);
  assert(std::equal(dl.begin(), dl.end(),
                    std::vector<double>{1.73205080756, 314.159265,
                                        40.727731959555605, 58.809606321088104,
                                        94.54495316415048, 21.978090016900364}
                        .begin()));
  for (auto i = 0; i != 6; ++i)
    dl.pop_front();
  assert(dl.size() == 0);
  assert(dl.empty());
}

void test_insert_clear() {
  using std::string;
  Slist<string> list;
  list.push_front(string(10, 'a'));
  list.push_front(string(5, 'b'));
  list.push_front(string(12, 'c'));
  assert(*list.insert_after(list.cbegin(), string(13, 'd')) == string(13, 'd'));
  assert(list.size() == 4);
  assert(!list.empty());
  std::list<string> ans = {string(12, 'c'), string(13, 'd'), string(5, 'b'),
                           string(10, 'a')};
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  auto it = list.begin();
  ++it;
  ++it;
  ++it;
  assert(*list.insert_after(it, string(18, 'e')) == string(18, 'e'));
  ans.emplace_back(18, 'e');
  assert(list.size() == 5);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  list.push_front(string(15, 'f'));
  ans.emplace_front(15, 'f');
  assert(list.size() == 6);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  it = list.begin();
  ++it;
  auto ans_it = ans.begin();
  ++ans_it;
  list.insert_after(it, string(9, 'g'));
  ++ans_it;
  ans_it = ans.emplace(ans_it, 9, 'g');
  list.insert_after(it, string(13, 'h'));
  ans.emplace(ans_it, 13, 'h');
  assert(list.size() == 8);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());
  list.push_front("Ma Long");
  list.push_front("Greatest of All Time");
  list.insert_after(list.begin(), "the dictator");
  list.insert_after(list.begin(), "the captain, the dragon");
  ans = {"Greatest of All Time", "the captain, the dragon", "the dictator",
         "Ma Long"};
  assert(list.size() == 4);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());
}

void test_insert_special() {
  Slist<Special_type> list;
  list.push_front(0);
  for (auto i = 10; i != 20; ++i)
    list.insert_after(list.begin(), i);
  std::vector<Special_type> v = {0, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10};
  assert(list.size() == 11);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), v.begin()));
  list.clear();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());
}

void test_insert_erase() {
  Slist<int> list;
  list.push_front(-1);
  for (auto i = 9; i != -1; --i)
    list.insert_after(list.cbegin(), i);
  assert(list.size() == 11);
  assert(!list.empty());
  std::list<int> ans;
  for (auto i = -1; i != 10; ++i)
    ans.push_back(i);
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  auto it = list.begin();
  for (auto i = 0; i != 10; ++i)
    ++it;
  list.insert_after(it, 11);
  list.insert_after(it, 10);
  ans.push_back(10);
  ans.push_back(11);
  assert(list.size() == 13);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  auto last = it;
  ++it;
  list.erase_after(it);
  ans.pop_back();
  it = last;
  list.erase_after(it);
  ans.pop_back();
  assert(list.size() == 11);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  list.erase_after(list.begin());
  list.erase_after(list.begin());
  ans.erase(++ans.begin());
  ans.erase(++ans.begin());
  assert(list.size() == 9);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  list.pop_front();
  ans.pop_front();
  list.pop_front();
  ans.pop_front();
  list.pop_front();
  ans.pop_front();
  assert(list.size() == 6);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  it = list.begin();
  ++it;
  ++it;
  list.erase_after(it);
  auto ans_it = ans.begin();
  ++ans_it;
  ++ans_it;
  ++ans_it;
  ans.erase(ans_it);
  assert(list.size() == 5);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  while (list.size() > 3)
    list.erase_after(++ ++list.cbegin());
  ans.pop_back();
  ans.pop_back();
  assert(list.size() == 3);
  assert(!list.empty());
  assert(std::equal(list.begin(), list.end(), ans.begin()));
  while (!list.empty())
    list.pop_front();
  assert(list.size() == 0);
  assert(list.empty());
  assert(list.begin() == list.end());
}

template <typename T>
void test_compare() {
  Slist<T> l1, l2;
  assert(l1 == l2);
  assert(l1 <= l2);
  assert(l1 >= l2);
  l1.push_front(3);
  l1.push_front(2);
  l1.push_front(1); // {1, 2, 3}
  assert(l2 < l1);
  assert(l2 != l1);
  assert(l1 > l2);
  assert(l1 != l2);
  l2.push_front(2);
  l2.push_front(1); // {1, 2}
  assert(l2 < l1);
  assert(l2 != l1);
  assert(l1 > l2);
  assert(l1 != l2);
  l2.insert_after(++l2.begin(), 3);
  assert(l1 == l2);
  assert(l1 <= l2);
  assert(l1 >= l2);
}

inline void test_compare() {
  test_compare<int>();
  test_compare<Special_type>();
}

// To pass this testcase, your insert_after should be O(1) and your copy-
// constructor should be O(n).
void test_large() {
  Slist<int> list;
  std::forward_list<int> fl;
  list.push_front(0);
  fl.push_front(0);
  auto it = list.begin();
  auto flit = fl.begin();
  for (auto i = 0; i != 100000; ++i) {
    it = list.insert_after(it, i * 2 + 3);
    flit = fl.insert_after(flit, i * 2 + 3);
  }
  for (auto i = 0; i != 100000; ++i) {
    list.insert_after(list.begin(), i * 2 + 5);
    fl.insert_after(fl.begin(), i * 2 + 5);
  }
  assert(list.size() == 100000 * 2 + 1);
  Slist<int> list2(list);
  assert(list2.size() == 100000 * 2 + 1);
  assert(std::equal(list2.begin(), list2.end(), fl.begin(), fl.end()));
  list2.clear();
  while (list.size() > 1)
    list.erase_after(list.begin());
  assert(list.size() == 1);
  assert(*list.begin() == 0);
}

int main() {
  int testcase;
  std::cin >> testcase;
  static void (*tests[])() = {&test_sample,
                              &test_ctor_front,
                              &test_inc,
                              &test_assignment_front,
                              &test_pop_front,
                              &test_insert_clear,
                              &test_insert_special,
                              &test_insert_erase,
                              &test_compare,
                              &test_large};
  tests[testcase - 1]();
  if (!memcheck::all_deallocated())
    throw std::runtime_error{"Memory leak detected"};
  std::cout << testcase << std::endl;
  return 0;
}
