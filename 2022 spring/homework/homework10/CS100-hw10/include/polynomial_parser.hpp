#ifndef CS100_HW10_POLYNOMIALPARSER_HPP_
#define CS100_HW10_POLYNOMIALPARSER_HPP_

#include "polynomial.hpp"
#include <string>
#include <map>
#include <functional>

class PolynomialParser {
 public:
  //procedure to compute a polynomial function as a new polynomial
  //takes a map of polynomials that have been loaded and are used in the function
  //  (key=name of polynomial)
  //  (value=the polynomial)
    Polynomial compute_polynomial( const std::string& expression,
                                 std::map<std::string,Polynomial>& polys);

  //procedure to compute a lambda function that represents the polynomial function
  //parameters are same than for the previous function
    typedef std::function<double(double)> scalarFct;
    scalarFct compute_lambda( const std::string& expression,
                            std::map<std::string, Polynomial> & polys);
};

#endif
