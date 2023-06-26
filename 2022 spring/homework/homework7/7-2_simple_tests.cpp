#include <iostream>
#include <type_traits>
using namespace std;
/**********************************************************/
#include"7-2.cpp"
// #include or paste your code here and compile this code.
/**********************************************************/

// This type is not default-constructible and not copy-assignable.
// You should make sure that your Slist can store such thing.
class Special_type {
  int x;

 public:
  Special_type() = delete;
  Special_type(const Special_type &) = default;
  Special_type &operator=(const Special_type &) = delete;
  Special_type(int xx) : x(xx) {}
  int get() const {
    return x;
  }
};

inline bool operator==(const Special_type &lhs, const Special_type &rhs) {
  return lhs.get() == rhs.get();
}

inline bool operator<(const Special_type &lhs, const Special_type &rhs) {
  return lhs.get() < rhs.get();
}

// The following are some compile-time checks.
static_assert(std::is_default_constructible<Slist<int>>::value,
              "Slist should be default-constructible.");

static_assert(std::is_copy_constructible<Slist<int>>::value,
              "Slist should be copy-constructible.");

static_assert(std::is_copy_assignable<Slist<int>>::value,
              "Slist should be copy-assignable.");

// Note: even if the following two assertions succeed, your Slist may still have
// some problem when storing data of the Special_type. These static-assertions
// only deduce whether the relevant functions are callable, without actually
// calling them. You need to try on your own to test whether any error arises
// when some functions are called.

static_assert(std::is_default_constructible<Slist<Special_type>>::value,
              "Slist<T> should be default-constructible even if T is not.");

static_assert(std::is_copy_assignable<Slist<Special_type>>::value,
              "Slist<T> should be copy-assignable even if T is not.");

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

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define SET_COLOR(COLOR, STRING) (ANSI_COLOR_##COLOR STRING ANSI_COLOR_RESET)

#define RED(STRING) SET_COLOR(RED, STRING)
#define GREEN(STRING) SET_COLOR(GREEN, STRING)

inline void report_if_wrong(bool condition, long line) {
  if (!condition) {
    std::cout << ANSI_COLOR_RED "Wrong on line " << line << ANSI_COLOR_RESET
              << std::endl;
    exit(0);
  }
}

#ifdef assert
#undef assert
#endif

#define assert(COND) report_if_wrong(COND, __LINE__)

int main() {
  std::cout << GREEN("You've passed the compile-time tests.") << std::endl;

  int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  Slist<int> list;
  for (auto x : a)
    list.push_front(x);
  assert(list.size() == 10);
  assert(!list.empty());
  
  //for(auto x:list)cout<<x<<' ';cout<<'\n';
  
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
  
  for(auto x:list)cout<<x<<' ';cout<<'\n';
  
  assert(list.size() == 7);
  assert(!list.empty());
  num = 3;
  for (auto x : list)
    assert(x == num++);
for(auto x:list)cout<<x<<' ';cout<<'\n';

  for (auto i = 0; i != 4; ++i)
  	list.erase_after(list.begin());
for(auto x:list)cout<<x<<' ';cout<<'\n';    

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

  std::cout << GREEN("Congratulations! You've passed the simple test.")
            << '\n';
    


/*	for(auto x:a)
		list.push_front(x);
	for(auto x:list)cout<<x<<' ';cout<<'\n';
	Slist<int> list2=list;
	for(auto x:list2)
		cout<<x<<' ';
	cout<<'\n';
		*/
	cout<<list.size()<<'\n';
	list.push_front(1);
	
	Slist<int> s1;
	Slist<int> s2=s1;
	
  return 0;
}
