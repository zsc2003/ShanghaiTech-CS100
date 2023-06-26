#include <cstdio>

class Dynarray {
  int *m_storage;
  // int m_storage[10];
  std::size_t m_length;
 public:
  int &at(std::size_t n) const {
    return m_storage[n];
  }
};

int main()
{
    Dynarray d;
    return 0;
}

