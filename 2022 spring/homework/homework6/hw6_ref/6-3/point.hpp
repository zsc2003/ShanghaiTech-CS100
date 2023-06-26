#ifndef CS100_HW_POINT_HPP
#define CS100_HW_POINT_HPP

#include <string>

class Point {
  double x{0}, y{0};
  std::string label;

 public:
  Point(double x0, double y0, const std::string &l = "")
      : x(x0), y(y0), label(l) {}
  Point() = default;
  double get_x() const {
    return x;
  }
  double get_y() const {
    return y;
  }
  std::string get_label() const {
    return label;
  }
  Point &set_x(double x0) {
    x = x0;
    return *this;
  }
  Point &set_y(double y0) {
    y = y0;
    return *this;
  }
  Point &set_label(const std::string &l) {
    label = l;
    return *this;
  }
};

#endif // CS100_HW_POINT_HPP