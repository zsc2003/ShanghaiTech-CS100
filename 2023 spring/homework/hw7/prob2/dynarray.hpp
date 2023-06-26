#ifndef DYNARRAY_STD_HPP
#define DYNARRAY_STD_HPP 1

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>
#include <iostream>

class Dynarray {
 public:
  using size_type = std::size_t;
  using value_type = int;
  using pointer = int *;
  using reference = int &;
  using const_pointer = const int *;
  using const_reference = const int &;

  static const size_type npos = -1;

 private:
  size_type m_length;
  pointer m_storage;

 public:
  explicit Dynarray(size_type n) : m_length{n}, m_storage{new value_type[n]{}} {}
  Dynarray(size_type n, const value_type &x) : m_length{n}, m_storage{new value_type[n]} {
    std::fill_n(m_storage, n, x);
  }
  Dynarray() : m_length{0}, m_storage{nullptr} {}
  Dynarray(const_pointer begin, const_pointer end)
      : m_length(end - begin), m_storage{new value_type[end - begin]} {
    std::copy(begin, end, m_storage);
  }
  Dynarray(const Dynarray &other)
      : m_length{other.size()}, m_storage{new value_type[m_length]} {
    for (size_type i = 0; i != m_length; ++i)
      m_storage[i] = other.at(i);
  }
  Dynarray(Dynarray &&other) noexcept
      : m_length{std::exchange(other.m_length, 0)},
        m_storage{std::exchange(other.m_storage, nullptr)} {}
  Dynarray &operator=(const Dynarray &other) {
    auto new_data = new value_type[other.size()];
    for (size_type i = 0; i != other.size(); ++i)
      new_data[i] = other.at(i);
    delete[] m_storage;
    m_storage = new_data;
    m_length = other.size();
    return *this;
  }
  Dynarray &operator=(Dynarray &&other) noexcept {
    if (this != &other) {
      delete[] m_storage;
      m_length = std::exchange(other.m_length, 0);
      m_storage = std::exchange(other.m_storage, nullptr);
    }
    return *this;
  }
  ~Dynarray() {
    delete[] m_storage;
  }

  size_type size() const {
    return m_length;
  }
  bool empty() const {
    return m_length == 0u;
  }
  reference at(size_type n) {
    return const_cast<reference>(static_cast<const Dynarray *>(this)->at(n));
  }
  const_reference at(size_type n) const {
    if (n >= m_length)
      throw std::out_of_range{"Dynarray index out of range."};
    return m_storage[n];
  }
  reference operator[](size_type n) {
    return m_storage[n];
  }
  const_reference operator[](size_type n) const {
    return m_storage[n];
  }

  size_type find(const value_type &x, size_type pos = 0) const {
    while (pos < size()) {
      if (at(pos) == x)
        return pos;
      ++pos;
    }
    return npos;
  }
};

bool operator==(const Dynarray &lhs, const Dynarray &rhs) {
  if (lhs.size() != rhs.size())
    return false;
  for (std::size_t i = 0; i != lhs.size(); ++i)
    if (!(lhs[i] == rhs[i]))
      return false;
  return true;
}

bool operator<(const Dynarray &lhs, const Dynarray &rhs) {
  for (std::size_t i = 0; i != lhs.size() && i != rhs.size(); ++i) {
    if (lhs[i] < rhs[i])
      return true;
    if (rhs[i] < lhs[i])
      return false;
  }
  return lhs.size() < rhs.size();
}

bool operator!=(const Dynarray &lhs, const Dynarray &rhs) {
  return !(lhs == rhs);
}

bool operator>(const Dynarray &lhs, const Dynarray &rhs) {
  return rhs < lhs;
}

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
