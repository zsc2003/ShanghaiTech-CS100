#include <string>
#include <map>
#include <iostream>
#include "polynomial.hpp"
#include "polynomial_parser.hpp"


int main(int argc, char** argv) {
  std::map<std::string, Polynomial> polys;
  PolynomialParser parser;

  char polyname[80];
  for (int i = 1; i <= 2; ++i) {
    sprintf(polyname, "p%d", i);
    std::string filename = std::string(argv[1]) + polyname + ".txt";
    Polynomial poly(filename);
    polys[std::string(polyname)] = poly;
  }  
  
  Polynomial poly_func = parser.compute_polynomial("p1 p2 +", polys);  
  std::cout << poly_func(1.5) << std::endl;
  return 0;
}