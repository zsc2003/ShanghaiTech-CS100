#include "expr.hpp"
#include <iostream>

int main() {
  auto &x = Expr::x;
  auto f = x * x + 2 * x + 1;
  std::cout << f.rep() << std::endl;
  std::cout << f.eval(3) << std::endl;
  std::cout << f.derivative(3) << std::endl;
  auto g = f / (-x * x + x - 1);
  std::cout << g.rep() << std::endl;
  std::cout << g.eval(3) << std::endl;
  std::cout << g.derivative(3) << std::endl;
  auto h = 2 * -x + 3;
  std::cout << h.rep() << std::endl;
  return 0;
}