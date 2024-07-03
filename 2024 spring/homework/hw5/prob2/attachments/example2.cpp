#include "dynarray.hpp"

#include <cassert>
#include <vector>
#include <utility>

int main() {
  std::vector<int> v{1, 2, 3, 4, 5};
  Dynarray a(v.data(), v.data() + v.size());
  Dynarray b(std::move(a));
  assert(a.empty());
  assert(a.size() == 0u);
  assert(b.size() == 5);
  a = std::move(b);
  assert(b.empty());
  assert(b.size() == 0u);
  assert(a.size() == 5);
  for (auto i = 0; i != 5; ++i)
    assert(a.at(i) == i + 1);
  return 0;
}