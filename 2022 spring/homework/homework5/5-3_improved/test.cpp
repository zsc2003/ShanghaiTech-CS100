// Uncomment either one you want to use.
// #include "expression_use_ref_cnt.hpp"
// #include "expression_use_shared_ptr.hpp"
#include <iostream>
#include <string>

int main() {
  auto expr_tree = exp((Expr(3) + Expr(4) * Expr(5)) / Expr(6));
  std::cout << expr_tree.eval() << std::endl;
  std::cout << expr_tree.to_string() << std::endl;
  return 0;
}