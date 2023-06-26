#include <iostream>
#include <cmath>


#define sqr(x,y) sqrt(x*x+y*y)


int main() {
  int a, b;
  std::cin >> a >> b;
  std::cout << sqr(a, b) << std::endl;
  return 0;
}