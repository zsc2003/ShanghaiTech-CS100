#ifndef CS100_HW_HANDLE_HPP
#define CS100_HW_HANDLE_HPP

#include "point.hpp"

class Point_handle {
  Point *ptr;
  unsigned *cnt;

 public:
  Point_handle(double x, double y, const std::string &l = "")
      : ptr(new Point{x, y, l}), cnt(new unsigned{1}) {}
  Point_handle(const Point &p) : ptr(new Point{p}), cnt(new unsigned{1}) {}
  Point_handle() : ptr(new Point{}), cnt(new unsigned{1}) {}

  Point_handle(const Point_handle &other) : ptr(other.ptr), cnt(other.cnt) {
    ++*cnt;
  }
  Point_handle &operator=(const Point_handle &other) {
    ++*other.cnt;
    if (!--*cnt) {
      delete ptr;
      delete cnt;
    }
    ptr = other.ptr;
    cnt = other.cnt;
    return *this;
  }
  ~Point_handle() {
    if (!--*cnt) {
      delete ptr;
      delete cnt;
    }
  }

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
    if (*cnt > 1) {
      auto copy = new Point{*ptr};
      --*cnt;
      ptr = copy;
      cnt = new unsigned{1};
    }
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
    return *cnt;
  }
};

#endif // CS100_HW_HANDLE_HPP