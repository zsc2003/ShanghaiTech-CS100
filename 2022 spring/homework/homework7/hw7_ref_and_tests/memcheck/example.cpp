#include "memcheck.hpp"
#include <iostream>

void good() {
  auto p = new int[100];
  delete[] p;
  auto q = new double{3.14};
  delete q;
}

void bad() {
  auto p = new int[100];
  delete p;
  auto q = new double;
}

int main() {
  good();
  if (memcheck::all_deallocated())
    std::cout << "all deallocated in good()" << std::endl;
  bad();
  if (memcheck::all_deallocated())
    std::cout << "all deallocated in bad()" << std::endl;
  else
    std::cout << "Memory leak detected in bad()." << std::endl;
  return 0;
}