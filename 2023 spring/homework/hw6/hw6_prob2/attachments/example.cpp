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
  
  int arr[] = {42, 43, 45, 43, 45, 47, 42};
  Dynarray c(arr, arr + 7);
  assert(c.find(45) == 2);
  assert(c.find(43) == 1);
  assert(c.find(47) == 5);
  assert(c.find(43, 2) == 3);
  assert(c.find(42, 1) == 6);
  assert(c.find(43, 4) == Dynarray::npos);
  assert(c.find(42, 19260817) == Dynarray::npos);
puts("OK");
  return 0;
}