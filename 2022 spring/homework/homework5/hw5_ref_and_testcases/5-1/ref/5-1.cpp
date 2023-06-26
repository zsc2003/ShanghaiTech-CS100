#include <algorithm>
#include <cmath>
#include <cstddef>

class Array {
 public:
  Array();
  explicit Array(std::size_t n);
  explicit Array(int *begin, int *end);
  Array(const Array &other);
  Array &operator=(const Array &other);
  ~Array();
  int &at(std::size_t n);
  const int &at(std::size_t n) const;
  std::size_t size() const;
  bool empty() const;
  void clear();
  Array slice(std::size_t l, std::size_t r, std::size_t s = 1) const;

 private:
  std::size_t m_size;
  int *m_data;
};

Array::Array() : m_size(0), m_data(nullptr) {}

// The 'explicit' keyword should not be redeclared.
Array::Array(std::size_t n) : m_size(n), m_data(new int[n]{}) {}

Array::Array(int *begin, int *end) : Array(end - begin) {
  std::copy(begin, end, m_data);
}

Array::Array(const Array &other)
    : Array(other.m_data, other.m_data + other.m_size) {}

/**
 * Note: (VERY IMPORTANT)
 * Most of the students write the copy-assignment operator as follows:
 *
 * Array &Array::operator=(const Array &other) {
 *   if (this != &other) {
 *     delete[] m_data;
 *     m_size = other.m_size;
 *     m_data = new int[m_size];
 *     std::copy(other.m_data, other.m_data + m_size, m_data);
 *   }
 *   return *this;
 * }
 *
 * This is self-assignment-safe, of course, but it is NOT exception-safe.
 * Considering you have not learned anything about exception-handling,
 * we did not check the exception-safety of this function. You can refer to
 * Effective C++ Item 11 to learn about this. The correct version, which is
 * both self-assignment-safe and exception-safe, is as follows.
 */
Array &Array::operator=(const Array &other) {
  int *new_data = new int[other.m_size];
  std::copy(other.m_data, other.m_data + other.m_size, new_data);
  m_size = other.m_size;
  delete[] m_data;
  m_data = new_data;
  return *this;
}

Array::~Array() {
  // m_data should be deleted even when m_size == 0
  // because new int[0] will allocate some memory.
  delete[] m_data;
}

int &Array::at(std::size_t n) {
  return m_data[n];
}

const int &Array::at(std::size_t n) const {
  return m_data[n];
}

std::size_t Array::size() const {
  return m_size;
}

bool Array::empty() const {
  return size() == 0;
}

void Array::clear() {
  m_size = 0;
  delete[] m_data;
  m_data = nullptr;
}

// The default argument '= 1' should not be redeclared.
Array Array::slice(std::size_t l, std::size_t r, std::size_t s) const {
  if (r > size())
    r = size();
  int n = std::ceil(static_cast<double>(r - l) / s);
  if (n <= 0)
    return Array{};
  Array ret(n);
  for (std::size_t i = l, j = 0; i < r; i += s, ++j)
    ret.at(j) = m_data[i];
  return ret;
}
