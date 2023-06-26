#include <algorithm>
#include <cmath>
#include <cstddef>

class Array {
 public:
  Array();
  explicit Array(std::size_t n);
  explicit Array(int *begin, int *end);
  Array(const Array &other);

  // Pay attention to this!
  void swap(Array &other);

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
 * The technique we use here is called 'copy-and-swap', the idea of which is
 * quite simple: To assign 'other' to the object *this, we only need
 * to make a copy of 'other', and then swap it with *this. This can get you free
 * from dealing with the memory allocation and deallocation manually, because
 * all the work then is done by the copy-constructor and the destructor. What's
 * more, the copy-assignment operator written in this way is both
 * self-assignment-safe and exception-safe.
 */
void Array::swap(Array &other) {
  using std::swap;
  swap(m_size, other.m_size);
  swap(m_data, other.m_data);
}
Array &Array::operator=(const Array &other) {
  Array(other).swap(*this);
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
