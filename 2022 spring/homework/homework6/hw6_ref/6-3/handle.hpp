#ifndef CS100_HW_HANDLE_HPP
#define CS100_HW_HANDLE_HPP

#include "point.hpp"

class Point_counted {
  friend class Point_handle;

  Point p;
  unsigned cnt{1};

  Point_counted() = default;
  Point_counted(double x, double y, const std::string &l = "") : p(x, y, l) {}
  Point_counted(const Point &pt) : p(pt) {}
};

class Point_handle {
  Point_counted *ptr;

 public:
  Point_handle(double x, double y, const std::string &l = "")
      : ptr(new Point_counted{x, y, l}) {}
  Point_handle(const Point &p) : ptr(new Point_counted{p}) {}
  Point_handle() : ptr(new Point_counted{}) {}

  Point_handle(const Point_handle &other) : ptr(other.ptr) {
    ++ptr->cnt;
  }
  // Note: you can still use the copy-and-swap technique.
  Point_handle &operator=(const Point_handle &other) {
    ++other.ptr->cnt;
    if (!--ptr->cnt)
      delete ptr;
    ptr = other.ptr;
    return *this;
  }
  ~Point_handle() {
    if (!--ptr->cnt)
      delete ptr;
  }

  double get_x() const {
    return ptr->p.get_x();
  }
  double get_y() const {
    return ptr->p.get_y();
  }
  std::string get_label() const {
    return ptr->p.get_label();
  }

 private:
  void check_and_copy() {
    if (ptr->cnt > 1) {
      auto copy = new Point_counted{ptr->p};
      --ptr->cnt;
      ptr = copy;
    }
  }

 public:
  Point_handle &set_x(double x) {
    check_and_copy();
    ptr->p.set_x(x);
    return *this;
  }
  Point_handle &set_y(double y) {
    check_and_copy();
    ptr->p.set_y(y);
    return *this;
  }
  Point_handle &set_label(const std::string &label) {
    check_and_copy();
    ptr->p.set_label(label);
    return *this;
  }

  unsigned ref_count() const {
    return ptr->cnt;
  }
};

#endif // CS100_HW_HANDLE_HPP