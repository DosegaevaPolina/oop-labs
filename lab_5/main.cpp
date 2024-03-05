#include "allocator.hpp"
#include "vector.hpp"
#include <map>
#include <iostream>

#define N 10
using Key = unsigned;
using T = unsigned;
using A = Allocator<std::pair<const Key, T>, N>;

int main() {
  std::map<Key, T, std::less<Key>, A> m;
  int factorial = 1;
  for (int i=0; i < N; ++i) {
    m[i] = factorial;
    factorial *= i+1;
  }
  for (const auto &[key, value] : m)
    std::cout << key << " " << value << "\n";

  Vector<T,Allocator<T,N>> v(N);
  factorial = 1;
  int i = 0;
  for (auto &value : v) {
    value = factorial;
    factorial *= i+1;
    i += 1;
  }
  i = 0;
  for (const auto &value : v)
    std::cout << i++ << " " << value << "\n";
}
