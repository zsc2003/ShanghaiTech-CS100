#ifndef CS100_HW_HANDLE_HPP
#define CS100_HW_HANDLE_HPP

#include "point.hpp"
#include <memory>

class Point_handle {
  std::shared_ptr<Point> ptr;

 public:
  Point_handle(double x, double y, const std::string &l = "")
      : ptr(std::make_shared<Point>(x, y, l)) {}
  Point_handle(const Point &p) : ptr(std::make_shared<Point>(p)) {}
  Point_handle() : ptr(std::make_shared<Point>()) {}

  double get_x() const {
    return ptr->get_x();
  }
  double get_y() const {
    return ptr->get_y();
  }
  std::string get_label() const {
    return ptr->get_label();
  }

 private:
  void check_and_copy() {
    if (ptr.use_count() > 1)
      ptr.reset(new Point{*ptr});
  }

 public:
  Point_handle &set_x(double x) {
    check_and_copy();
    ptr->set_x(x);
    return *this;
  }
  Point_handle &set_y(double y) {
    check_and_copy();
    ptr->set_y(y);
    return *this;
  }
  Point_handle &set_label(const std::string &label) {
    check_and_copy();
    ptr->set_label(label);
    return *this;
  }

  unsigned ref_count() const {
    return ptr.use_count();
  }
};

#endif // CS100_HW_HANDLE_HPP