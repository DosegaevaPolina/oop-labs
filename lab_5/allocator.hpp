#pragma once

#include <cstddef>
#include <deque>
#include <new>
#include <utility>

template <typename T, size_t N>
class Allocator {
private:
  T *memory, *next;

  size_t allocations;
  std::deque<std::pair<T*,size_t>> used;

public:
  using value_type = T;

  template <class U>
  struct rebind {
    using other = Allocator<U,N>;
  };

  Allocator() {
    memory = static_cast<T*>(::operator new (N*sizeof(T)));
    next = memory;
    allocations = 0;
  }

  ~Allocator(){
    ::operator delete(memory);
  }

  T* allocate(size_t n) {
    T *result = nullptr;

    if (memory + N - next < n)
      throw std::bad_alloc();

    result = next;
    next += n;
    used.push_back(std::make_pair(result, n));
    allocations += 1;

    return result;
  }

  void deallocate(T *p, size_t n) {
    auto last_used = used.back();
    if (last_used.first == p && last_used.second == n) {
      next -= n;
      used.pop_back();
    }
    allocations -= 1;
    if (allocations == 0) next = memory;
  }

  template <class U, class... Args>
  void construct(U *p, Args &&...args) {
    new (p) U(std::forward<Args>(args)...);
  }

  void destroy(T* p) { p->~T(); }
};

template <class T, size_t N, class U, size_t M>
bool operator==(Allocator<T,N> const &, Allocator<U,M> const &) noexcept {
  return N == M;
}

template <class T, size_t N, class U, size_t M>
bool operator!=(Allocator<T,N> const &x, Allocator<U,M> const &y) noexcept {
  return !(x == y);
}
