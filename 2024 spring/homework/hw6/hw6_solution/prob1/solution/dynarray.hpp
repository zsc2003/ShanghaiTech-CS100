#ifndef DYNARRAY_STD_HPP
#define DYNARRAY_STD_HPP 1

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <utility>

class Dynarray {
public:
  using size_type = std::size_t;
  using value_type = int;
  using pointer = int *;
  using reference = int &;
  using const_pointer = const int *;
  using const_reference = const int &;

private:
  size_type m_length;
  pointer m_storage;

public:
  explicit Dynarray(size_type n)
      : m_length{n}, m_storage{new value_type[n]{}} {}
  Dynarray(size_type n, const value_type &x)
      : m_length{n}, m_storage{new value_type[n]} {
    std::fill_n(m_storage, n, x);
  }
  Dynarray() : m_length{0}, m_storage{nullptr} {}
  Dynarray(const_pointer begin, const_pointer end)
      : m_length(end - begin), m_storage{new value_type[end - begin]} {
    std::copy(begin, end, m_storage);
  }
  Dynarray(const Dynarray &other)
      : m_length{other.size()}, m_storage{new value_type[m_length]} {
    std::copy_n(other.m_storage, other.m_length, m_storage);
  }
  Dynarray(Dynarray &&other) noexcept
      : m_length{std::exchange(other.m_length, 0)},
        m_storage{std::exchange(other.m_storage, nullptr)} {}
  void swap(Dynarray &other) noexcept {
    using std::swap;
    swap(m_length, other.m_length);
    swap(m_storage, other.m_storage);
  }
  Dynarray &operator=(Dynarray other) noexcept {
    swap(other);
    return *this;
  }
  ~Dynarray() { delete[] m_storage; }

  size_type size() const { return m_length; }
  bool empty() const { return m_length == 0u; }
  reference at(size_type n) {
    return const_cast<reference>(static_cast<const Dynarray *>(this)->at(n));
  }
  const_reference at(size_type n) const {
    if (n >= m_length)
      throw std::out_of_range{"Dynarray index out of range."};
    return m_storage[n];
  }
  reference operator[](size_type n) { return m_storage[n]; }
  const_reference operator[](size_type n) const { return m_storage[n]; }

  friend bool operator==(const Dynarray &, const Dynarray &);
  friend bool operator<(const Dynarray &, const Dynarray &);
};

bool operator==(const Dynarray &lhs, const Dynarray &rhs) {
  return std::equal(lhs.m_storage, lhs.m_storage + lhs.m_length, rhs.m_storage,
                    rhs.m_storage + rhs.m_length);
}

bool operator<(const Dynarray &lhs, const Dynarray &rhs) {
  return std::lexicographical_compare(
      lhs.m_storage, lhs.m_storage + lhs.m_length, rhs.m_storage,
      rhs.m_storage + rhs.m_length);
}

bool operator!=(const Dynarray &lhs, const Dynarray &rhs) {
  return !(lhs == rhs);
}

bool operator>(const Dynarray &lhs, const Dynarray &rhs) { return rhs < lhs; }

bool operator<=(const Dynarray &lhs, const Dynarray &rhs) {
  return !(lhs > rhs);
}

bool operator>=(const Dynarray &lhs, const Dynarray &rhs) {
  return !(lhs < rhs);
}

std::ostream &operator<<(std::ostream &os, const Dynarray &a) {
  os << '[';
  if (!a.empty()) {
    os << a[0];
    for (std::size_t i = 1; i < a.size(); ++i)
      os << ", " << a[i];
  }
  return os << ']';
}

#endif // DYNARRAY_STD_HPP