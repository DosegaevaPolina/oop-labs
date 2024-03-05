#include <fuzztest/fuzztest.h>
#include <gtest/gtest.h>
#include "allocator.hpp"
#include <iterator>
#include <map>
#include <utility>

#define N 1000
using Key = unsigned;
using T = unsigned;
using A = Allocator<std::pair<const Key, T>, N>;

TEST(Allocator, std_map) {
  std::map<Key, T, std::less<Key>, A> m;

  for (int i=0; i < 10000; ++i) {
    switch (rand() % 2) {
    case 0:
      if (m.size() < N)
        m[rand() % N] = i;
    case 1:
      if (m.empty()) continue;
      int idx = rand() % m.size();
      m.erase(std::next(m.begin(), idx));
    }
  }
}


using namespace fuzztest;

void Vector(size_t vec_size) {
  std::vector<T, Allocator<T, N>> v;
  v.resize(vec_size);
  SUCCEED();
}
FUZZ_TEST(Allocator, Vector).WithDomains(InRange(1, N));

void MapInsert(size_t vec_size) {
  std::map<Key, T, std::less<Key>, A> m;
  std::vector<std::pair<const Key, T>, A> v;
  v.resize(vec_size);
  m.insert(std::begin(v), std::end(v));
  SUCCEED();
}
FUZZ_TEST(Allocator, MapInsert).WithDomains(InRange(1, N));
