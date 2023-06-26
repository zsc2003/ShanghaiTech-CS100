#include <type_traits>
#include <utility>

#define main __student_main_function_
#define _ONLINE_JUDGE

/**************************************************/

// PASTE YOUR CODE HERE

/**************************************************/

#ifdef OJ_ASSERT
#undef OJ_ASSERT
#endif

static_assert(std::is_copy_constructible<Array>::value,
              "Your 'Array' type is not copy-constructible. Check your "
              "copy-constructor carefully.");

static_assert(std::is_copy_assignable<Array>::value,
              "Your 'Array' type is not copy-assignable. Check your "
              "copy-assignment operator carefully.");

static_assert(
    std::is_same<
        decltype(std::declval<Array>().operator=(std::declval<Array>())),
        Array &>::value,
    "Assignment operator should return a reference to the object itself.");

#include <iostream>
#define OJ_ASSERT(x)                                                           \
  {                                                                            \
    if (!(x)) {                                                                \
      std::cout << "Wrong answer at line " << __LINE__ << std::endl;           \
      return 0;                                                                \
    }                                                                          \
  }
#undef main

int main() {
  int testcase;
  std::cin >> testcase;
  switch (testcase) {
    case 1: {
      Array a;
      OJ_ASSERT(a.size() == 0);
      OJ_ASSERT(a.empty() == true);
      break;
    }
    case 2: {
      std::size_t n = 10;
      Array a(n);
      OJ_ASSERT(a.size() == n);
      OJ_ASSERT(a.empty() == false);
      n = 0;
      Array a1(n);
      OJ_ASSERT(a1.size() == n);
      OJ_ASSERT(a1.empty() == true);
      break;
    }
    case 3: {
      int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
      const Array b(a, a + 10);
      // size(), empty() and at() must be callable on const object.
      Array c(a + 5, a + 5);
      OJ_ASSERT(b.size() == 10);
      OJ_ASSERT(b.empty() == false);
      OJ_ASSERT(c.size() == 0);
      OJ_ASSERT(c.empty() == true);
      for (int i = 0; i < 10; i++) {
        OJ_ASSERT(a[i] == b.at(i));
      }
      OJ_ASSERT(b.size() == 10);
      OJ_ASSERT(b.empty() == false);
      break;
    }
    case 4: {
      int a[5] = {-5, -4, -3, -2, -1};
      Array a1;
      Array a2(10);
      Array a3(a, a + 5);
      Array a4(a1), a5(a2), a6(a3), a7(a4), a8(a6);
      OJ_ASSERT(a4.size() == 0);
      OJ_ASSERT(a5.size() == 10);
      OJ_ASSERT(a6.size() == 5);
      OJ_ASSERT(a7.size() == 0);
      OJ_ASSERT(a8.size() == 5);
      OJ_ASSERT(a4.empty() == true);
      OJ_ASSERT(a5.empty() == false);
      OJ_ASSERT(a6.empty() == false);
      OJ_ASSERT(a7.empty() == true);
      OJ_ASSERT(a8.empty() == false);
      for (int i = 0; i < 5; i++) {
        OJ_ASSERT(a6.at(i) == a[i]);
        OJ_ASSERT(a8.at(i) == a[i]);
      }
      break;
    }
    case 5: {
      int a[5] = {-5, -4, -3, -2, -1};
      int b[6] = {1, 2, 3, 4, 5, 6};
      Array a1;
      Array a2(10);
      Array a3(a, a + 5);
      Array a4 = a1;
      OJ_ASSERT(a4.size() == 0);
      OJ_ASSERT(a4.empty() == true);
      a4 = a2;
      OJ_ASSERT(a4.size() == 10);
      OJ_ASSERT(a4.empty() == false);
      a4 = a3;
      OJ_ASSERT(a4.size() == 5);
      OJ_ASSERT(a4.empty() == false);
      for (int i = 0; i < 5; i++) {
        OJ_ASSERT(a4.at(i) == a[i]);
      }
      Array a5(b, b + 3);
      a4 = a5;
      OJ_ASSERT(a4.size() == 3);
      OJ_ASSERT(a4.empty() == false);
      for (int i = 0; i < 3; i++)
        OJ_ASSERT(a4.at(i) == b[i]);
      break;
    }
    case 6: {
      int a[5] = {1, 2, 3, 4, 5};
      Array a1(5);
      Array a2(a, a + 5);
      Array a3 = a2;
      for (int i = 0; i < 5; i++) {
        int &t1 = a1.at(i);
        int &t2 = a2.at(i);
        int &t3 = a3.at(i);
        OJ_ASSERT(t2 == a[i]);
        OJ_ASSERT(t3 == a[i]);
        t1 = -i;
        t2 = -i;
        t3 = -i;
        OJ_ASSERT(a1.at(i) == -i);
        OJ_ASSERT(a2.at(i) == -i);
        OJ_ASSERT(a3.at(i) == -i);
        OJ_ASSERT(a1.size() == 5);
        OJ_ASSERT(a2.size() == 5);
        OJ_ASSERT(a3.size() == 5);
      }
      break;
    }
    case 7: {
      int a[5] = {1, 2, 3, 4, 5};
      Array a1(5);
      Array a2(a, a + 5);
      Array a3 = a2;
      for (int i = 0; i < 5; i++) {
        a1.at(i) = i - 1;
        a2.at(i) = i - 1;
        a3.at(i) = i - 1;
        [[maybe_unused]] const int &t1 = a1.at(i);
        [[maybe_unused]] const int &t2 = a2.at(i);
        [[maybe_unused]] const int &t3 = a3.at(i);
        OJ_ASSERT(a1.at(i) == i - 1);
        OJ_ASSERT(a2.at(i) == i - 1);
        OJ_ASSERT(a3.at(i) == i - 1);
        OJ_ASSERT(a1.size() == 5);
        OJ_ASSERT(a2.size() == 5);
        OJ_ASSERT(a3.size() == 5);
      }
      break;
    }
    case 8: {
      int a[5] = {1, 2, 3, 4, 5};
      Array a1;
      Array a2(10);
      Array a3(a, a + 5);
      Array a4 = a3;
      a3 = a3; // Self-assignment
      OJ_ASSERT(a3.size() == 5);
      OJ_ASSERT(a3.empty() == false);
      for (std::size_t i = 0; i < a3.size(); ++i)
        OJ_ASSERT(a3.at(i) == a[i]);
      a1.clear();
      a2.clear();
      a3.clear();
      a4.clear();
      OJ_ASSERT(a1.size() == 0);
      OJ_ASSERT(a1.empty() == true);
      OJ_ASSERT(a2.size() == 0);
      OJ_ASSERT(a2.empty() == true);
      OJ_ASSERT(a3.size() == 0);
      OJ_ASSERT(a3.empty() == true);
      OJ_ASSERT(a4.size() == 0);
      OJ_ASSERT(a4.empty() == true);
      break;
    }
    case 9: {
      Array a(100);
      for (int i = 0; i < 100; i++) {
        a.at(i) = i;
      }
      Array s = a.slice(0, 100);
      OJ_ASSERT(s.size() == 100);
      OJ_ASSERT(s.empty() == false);
      for (int i = 0; i < (int)s.size(); i++) {
        OJ_ASSERT(s.at(i) == i);
      }

      s = a.slice(30, 50);
      OJ_ASSERT(s.size() == 20);
      OJ_ASSERT(s.empty() == false);
      for (int i = 0; i < (int)s.size(); i++) {
        OJ_ASSERT(s.at(i) == i + 30);
      }

      s = a.slice(50, 30);
      OJ_ASSERT(s.size() == 0);
      OJ_ASSERT(s.empty() == true);

      s = a.slice(0, 100, 10);
      OJ_ASSERT(s.size() == 10);
      for (int i = 0; i < (int)s.size(); i += 10) {
        OJ_ASSERT(s.at(i) == i * 10);
      }

      s = a.slice(3, 20, 3);
      OJ_ASSERT(s.size() == 6);
      OJ_ASSERT(s.empty() == false);
      for (int i = 0; i < (int)s.size(); i++) {
        OJ_ASSERT(s.at(i) == 3 + i * 3);
      }

      s = a.slice(10, 20, 30);
      OJ_ASSERT(s.size() == 1);
      OJ_ASSERT(s.empty() == false);
      OJ_ASSERT(s.at(0) == 10);

      s = a.slice(17, 34, 5);
      OJ_ASSERT(s.size() == 4);
      OJ_ASSERT(s.empty() == false);
      for (int i = 0; i < (int)s.size(); i++) {
        OJ_ASSERT(s.at(i) == 17 + i * 5);
      }

      break;
    }
    case 10: {
      int a[10] = {1, 2, 3, 4, 5};
      Array a1(a, a + 5);
      OJ_ASSERT(a1.size() == 5);
      for (int i = 0; i < 5; i++) {
        a[i]++;
      }
      for (int i = 0; i < 5; i++) {
        OJ_ASSERT(a1.at(i) == a[i] - 1);
      }
      Array a2(a1);
      OJ_ASSERT(a2.size() == 5);
      for (int i = 0; i < 5; i++) {
        OJ_ASSERT(a2.at(i) == a[i] - 1);
      }

      Array a3(100);
      for (int i = 0; i < 100; i++) {
        a3.at(i) = i;
        OJ_ASSERT(a3.at(i) == i);
      }
      Array a4(20);
      a4 = a3;
      OJ_ASSERT(a4.size() == 100);
      for (int i = 0; i < 100; i++) {
        OJ_ASSERT(a4.at(i) == i);
      }
      a4.clear();
      OJ_ASSERT(a4.size() == 0);
      OJ_ASSERT(a4.empty() == true);
      OJ_ASSERT(a3.size() == 100);
      for (int i = 0; i < 100; i++) {
        a3.at(i) = i;
        OJ_ASSERT(a3.at(i) == i);
      }
      Array s = a3.slice(31, 45, 2);
      OJ_ASSERT(s.size() == 7);
      for (int i = 0; i < (int)s.size(); i++) {
        OJ_ASSERT(s.at(i) = 31 + 2 * i);
      }
      s.clear();
      OJ_ASSERT(s.size() == 0);
      OJ_ASSERT(s.empty() == true);
      OJ_ASSERT(a3.size() == 100);
      for (int i = 0; i < 100; i++) {
        a3.at(i) = i;
        OJ_ASSERT(a3.at(i) == i);
      }
      a3.clear();
      OJ_ASSERT(a3.size() == 0);
      OJ_ASSERT(a3.empty() == true);
      break;
    }
  }
  std::cout << testcase << std::endl;
  return 0;
}