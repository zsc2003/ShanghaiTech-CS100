#include "../memcheck/memcheck.hpp"
#include <type_traits>

#define main __student_main_function_
#define _ONLINE_JUDGE

/************************************************************************/

// PASTE OR #include YOUR CODE HERE

/************************************************************************/

#ifdef OJ_ASSERT
#undef OJ_ASSERT
#endif
#include <iostream>
#define OJ_ASSERT(x)                                                           \
  {                                                                            \
    if (!(x)) {                                                                \
      std::cout << "Wrong answer at line " << __LINE__ << std::endl;           \
      return;                                                                  \
    }                                                                          \
  }
#undef main

void test1() {
  std::string name1("Ali"), name2("Bob");
  int number1 = 10, number2 = 123456;
  double grade1 = 60.4, grade2 = 88.888;
  Grade g1(name1, number1, grade1);
  Grade g2(name2, number2, grade2);
  OJ_ASSERT(g1.getGrade() == grade1);
  OJ_ASSERT(g1.getNumber() == number1);
  OJ_ASSERT(g1.getName() == name1);
  OJ_ASSERT(g2.getGrade() == grade2);
  OJ_ASSERT(g2.getNumber() == number2);
  OJ_ASSERT(g2.getName() == name2);
  g2.setName(name1);
  g2.setNumber(number1);
  g2.setGrade(grade1);
  OJ_ASSERT(g2.getGrade() == grade1);
  OJ_ASSERT(g2.getNumber() == number1);
  OJ_ASSERT(g2.getName() == name1);
}

void test2() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie"), name4("David");
  int number1 = 1, number2 = 2, number3 = 3;
  double grade1 = 60, grade2 = 70, grade3 = 80;
  Gradesheet gs;
  OJ_ASSERT(gs.addGrade(Grade(name1, number1, grade1)) == true);
  OJ_ASSERT(gs.addGrade(Grade(name2, number2, grade2)) == true);
  OJ_ASSERT(gs.addGrade(Grade(name3, number3, grade3)) == true);
  OJ_ASSERT(gs.size() == 3);
  OJ_ASSERT(gs[0].getName() == name1);
  OJ_ASSERT(gs[0].getNumber() == number1);
  OJ_ASSERT(gs[0].getGrade() == grade1);
  OJ_ASSERT(gs[1].getName() == name2);
  OJ_ASSERT(gs[1].getNumber() == number2);
  OJ_ASSERT(gs[1].getGrade() == grade2);
  OJ_ASSERT(gs[2].getName() == name3);
  OJ_ASSERT(gs[2].getNumber() == number3);
  OJ_ASSERT(gs[2].getGrade() == grade3);
  OJ_ASSERT(gs.addGrade(Grade(name1, 5, 30)) == false);
  OJ_ASSERT(gs.addGrade(Grade(name4, number1, 100)) == false);
  OJ_ASSERT(gs.size() == 3);
  gs[1].setNumber(10);
  OJ_ASSERT(gs[1].getNumber() == 10);
  OJ_ASSERT(gs.addGrade(Grade(name4, 10, 100)) == false);
  OJ_ASSERT(gs.addGrade(Grade(name4, number2, 100)) == true);
  OJ_ASSERT(gs.size() == 4);
}

void test3() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie");
  int number1 = 1, number2 = 2, number3 = 3;
  double grade1 = 60.5, grade2 = 70.5, grade3 = 80.5;
  Gradesheet gs;
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  OJ_ASSERT(gs.average() == 70.5);
  gs[0].setGrade(90.5);
  OJ_ASSERT(gs.average() == 80.5);
}

void test4() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie");
  int number1 = 1, number2 = 2, number3 = 3;
  double grade1 = 60.5, grade2 = 70.5, grade3 = 80.5;
  Gradesheet gs;
  OJ_ASSERT(gs.findByNumber(1) == -1);
  OJ_ASSERT(gs.findByName(name1) == -1);
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  OJ_ASSERT(gs.findByNumber(1) == 60.5);
  OJ_ASSERT(gs.findByNumber(2) == 70.5);
  OJ_ASSERT(gs.findByNumber(4) == -1);
  gs[0].setNumber(4);
  OJ_ASSERT(gs.findByNumber(1) == -1);
  OJ_ASSERT(gs.findByNumber(4) == 60.5);
}

void test5() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie"), name4("David");
  int number1 = 1, number2 = 2, number3 = 3;
  double grade1 = 60.5, grade2 = 70.5, grade3 = 80.5;
  Gradesheet gs;
  OJ_ASSERT(gs.findByName(name1) == -1);
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  OJ_ASSERT(gs.findByName(name1) == 60.5);
  OJ_ASSERT(gs.findByName(name4) == -1);
  gs[0].setName(name4);
  OJ_ASSERT(gs.findByName(name1) == -1);
  OJ_ASSERT(gs.findByName(name4) == 60.5);
}

void test6() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie"), name4("David");
  int number1 = 2, number2 = 1, number3 = 3;
  double grade1 = 80.5, grade2 = 70.5, grade3 = 90.5;
  Gradesheet gs;
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  gs.sortByName();
  OJ_ASSERT(gs[0].getName() == name1);
  OJ_ASSERT(gs[1].getName() == name2);
  OJ_ASSERT(gs[2].getName() == name3);
  OJ_ASSERT(gs[0].getNumber() == number1);
  OJ_ASSERT(gs[1].getNumber() == number2);
  OJ_ASSERT(gs[2].getNumber() == number3);
  OJ_ASSERT(gs[0].getGrade() == grade1);
  OJ_ASSERT(gs[1].getGrade() == grade2);
  OJ_ASSERT(gs[2].getGrade() == grade3);
  gs[1].setName(name4);
  gs.sortByName();
  OJ_ASSERT(gs[0].getName() == name1);
  OJ_ASSERT(gs[1].getName() == name3);
  OJ_ASSERT(gs[2].getName() == name4);
  OJ_ASSERT(gs[0].getNumber() == number1);
  OJ_ASSERT(gs[1].getNumber() == number3);
  OJ_ASSERT(gs[2].getNumber() == number2);
  OJ_ASSERT(gs[0].getGrade() == grade1);
  OJ_ASSERT(gs[1].getGrade() == grade3);
  OJ_ASSERT(gs[2].getGrade() == grade2);
}

void test7() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie"), name4("David");
  int number1 = 2, number2 = 1, number3 = 3, number5 = 4;
  double grade1 = 80.5, grade2 = 70.5, grade3 = 90.5;
  Gradesheet gs;
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  gs.sortByNumber();
  OJ_ASSERT(gs[0].getName() == name2);
  OJ_ASSERT(gs[1].getName() == name1);
  OJ_ASSERT(gs[2].getName() == name3);
  OJ_ASSERT(gs[0].getNumber() == number2);
  OJ_ASSERT(gs[1].getNumber() == number1);
  OJ_ASSERT(gs[2].getNumber() == number3);
  OJ_ASSERT(gs[0].getGrade() == grade2);
  OJ_ASSERT(gs[1].getGrade() == grade1);
  OJ_ASSERT(gs[2].getGrade() == grade3);
  gs[0].setNumber(number5);
  gs.sortByNumber();
  OJ_ASSERT(gs[0].getName() == name1);
  OJ_ASSERT(gs[1].getName() == name3);
  OJ_ASSERT(gs[2].getName() == name2);
  OJ_ASSERT(gs[0].getNumber() == number1);
  OJ_ASSERT(gs[1].getNumber() == number3);
  OJ_ASSERT(gs[2].getNumber() == number5);
  OJ_ASSERT(gs[0].getGrade() == grade1);
  OJ_ASSERT(gs[1].getGrade() == grade3);
  OJ_ASSERT(gs[2].getGrade() == grade2);
  std::vector<Gradesheet> vgs(1000000);
  for (int i = 0; i != 500; ++i)
    for (int j = 0; j != 200; ++j)
      OJ_ASSERT(vgs[i].addGrade(Grade("a" + std::to_string(j), j, j % 100)));
}

void test8() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie"), name4("David");
  int number1 = 2, number2 = 1, number3 = 3;
  double grade1 = 80.5, grade2 = 70.5, grade3 = 90.5, grade4 = 75;
  Gradesheet gs;
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  gs.sortByGrade();
  OJ_ASSERT(gs[0].getName() == name3);
  OJ_ASSERT(gs[1].getName() == name1);
  OJ_ASSERT(gs[2].getName() == name2);
  OJ_ASSERT(gs[0].getNumber() == number3);
  OJ_ASSERT(gs[1].getNumber() == number1);
  OJ_ASSERT(gs[2].getNumber() == number2);
  OJ_ASSERT(gs[0].getGrade() == grade3);
  OJ_ASSERT(gs[1].getGrade() == grade1);
  OJ_ASSERT(gs[2].getGrade() == grade2);
  gs[0].setGrade(grade4);
  gs.sortByGrade();
  OJ_ASSERT(gs[0].getName() == name1);
  OJ_ASSERT(gs[1].getName() == name3);
  OJ_ASSERT(gs[2].getName() == name2);
  OJ_ASSERT(gs[0].getNumber() == number1);
  OJ_ASSERT(gs[1].getNumber() == number3);
  OJ_ASSERT(gs[2].getNumber() == number2);
  OJ_ASSERT(gs[0].getGrade() == grade1);
  OJ_ASSERT(gs[1].getGrade() == grade4);
  OJ_ASSERT(gs[2].getGrade() == grade2);
  std::vector<Gradesheet> vgs(1000000);
  for (int i = 0; i != 5000; ++i)
    OJ_ASSERT(vgs[0].addGrade(Grade("a" + std::to_string(i), i, i % 100)));
}

void test9() {
  std::string name1("Alice"), name2("Bob"), name3("Charlie"), name4("David");
  int number1 = 1, number2 = 23, number3 = 345, number5 = 4567;
  double grade1 = 80.5, grade2 = 70.56, grade3 = 90.5, grade4 = 60.123;
  Gradesheet gs;
  gs.addGrade(Grade(name1, number1, grade1));
  gs.addGrade(Grade(name2, number2, grade2));
  gs.addGrade(Grade(name3, number3, grade3));
  gs.addGrade(Grade(name4, number5, grade4));
  std::cout << gs;
  // /------------------------------\
  // |Name      Number    Grade     |
  // |------------------------------|
  // |Alice     1         80.5      |
  // |Bob       23        70.6      |
  // |Charlie   345       90.5      |
  // |David     4567      60.1      |
  // \------------------------------/
}

void test10() {
  Gradesheet gs;
  OJ_ASSERT(gs.addGrade(Grade(std::string("Bob"), 1, 10)) == true);
  OJ_ASSERT(gs.addGrade(Grade(std::string("David"), 11, 30)) == true);
  OJ_ASSERT(gs.addGrade(Grade(std::string("Alice"), 222, 50)) == true);
  OJ_ASSERT(gs.addGrade(Grade(std::string("Charlie"), 3333, 70)) == true);
  OJ_ASSERT(gs.addGrade(Grade(std::string("Charlie"), 2, 10)) == false);
  OJ_ASSERT(gs.addGrade(Grade(std::string("Eve"), 44444, 100)) == true);
  OJ_ASSERT(gs.addGrade(Grade(std::string("Ali"), 44444, 100)) == false);
  OJ_ASSERT(gs.size() == 5);
  std::cout << gs;
  // /------------------------------\
  // |Name      Number    Grade     |
  // |------------------------------|
  // |Bob       1         10        |
  // |David     11        30        |
  // |Alice     222       50        |
  // |Charlie   3333      70        |
  // |Eve       44444     100       |
  // \------------------------------/
  OJ_ASSERT(gs.average() == 52);
  gs[4].setGrade(90);
  OJ_ASSERT(gs.average() == 50);
  gs.sortByGrade();
  std::cout << gs;
  // /------------------------------\
  // |Name      Number    Grade     |
  // |------------------------------|
  // |Eve       44444     90        |
  // |Charlie   3333      70        |
  // |Alice     222       50        |
  // |David     11        30        |
  // |Bob       1         10        |
  // \------------------------------/
  gs.sortByName();
  std::cout << gs;
  // /------------------------------\
  // |Name      Number    Grade     |
  // |------------------------------|
  // |Alice     222       50        |
  // |Bob       1         10        |
  // |Charlie   3333      70        |
  // |David     11        30        |
  // |Eve       44444     90        |
  // \------------------------------/
  gs.sortByNumber();
  std::cout << gs;
  // /------------------------------\
  // |Name      Number    Grade     |
  // |------------------------------|
  // |Bob       1         10        |
  // |David     11        30        |
  // |Alice     222       50        |
  // |Charlie   3333      70        |
  // |Eve       44444     90        |
  // \------------------------------/
  OJ_ASSERT(gs.findByName(std::string("Charlie")) == 70);
  OJ_ASSERT(gs.findByNumber(11) == 30);
}

int main() {
  static constexpr void (*tests[10])() = {&test1, &test2, &test3, &test4,
                                          &test5, &test6, &test7, &test8,
                                          &test9, &test10};
  int testcase;
  std::cin >> testcase;
  tests[testcase - 1]();
  if (!memcheck::all_deallocated())
    throw std::runtime_error{"Memory leak detected"};
  std::cout << testcase << std::endl;
  return 0;
}
