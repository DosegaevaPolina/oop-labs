#pragma once

#include <memory>
#include <initializer_list>

template <typename T, class Allocator = std::allocator<T>>
class Vector {
private:
  T *data;
  size_t data_size;
  size_t data_capacity;
  Allocator allocator;
  using alloc_traits = std::allocator_traits<Allocator>;

public:
  using value_type = T;

  class Iterator {
  private:
    value_type *ptr;

  public:
    friend Vector;

    using difference_type = int;
    using value_type = Vector::value_type;
    using reference = Vector::value_type &;
    using pointer = Vector::value_type *;
    using iterator_category =
        std::forward_iterator_tag;

    Iterator() : ptr(nullptr) {}

    Iterator(pointer p) : ptr(p) {}

    ~Iterator() = default;

    reference operator*() { return *ptr; }

    pointer operator->() { return ptr; }

    Iterator &operator++() {
      ptr += 1;
      return *this;
    }

    Iterator operator++(int) {
      Iterator new_iter = *this;
      ptr += 1;
      return new_iter;
    }

    Iterator &operator--() {
      ptr -= 1;
      return *this;
    }

    Iterator operator--(int) {
      Iterator new_iter = *this;
      ptr -= 1;
      return new_iter;
    }

    Iterator operator+(const int &ci) const {
      Iterator new_iter = *this;
      new_iter.ptr += ci;
      return new_iter;
    }

    Iterator &operator+=(const int &ci) {
      ptr = ptr + ci;
      return *this;
    }

    Iterator operator-(const int &ci) const {
      Iterator new_iter = *this;
      new_iter.ptr -= ci;
      return new_iter;
    }

    Iterator &operator-=(const int &ci) {
      ptr = ptr - ci;
      return *this;
    }

    bool operator==(const Iterator &iter) const {
      return (this->ptr == iter.ptr);
    }

    bool operator!=(const Iterator &iter) const {
      return (this->ptr != iter.ptr);
    }
  };

  class ConstIterator {
  private:
    const value_type *ptr;

  public:
    friend Vector;

    using difference_type = int;
    using value_type = const Vector::value_type;
    using reference = const Vector::value_type &;
    using pointer = const Vector::value_type *;
    using iterator_category =
        std::forward_iterator_tag;

    ConstIterator() { ptr = nullptr; }

    ConstIterator(pointer p) : ptr(p) {}

    ~ConstIterator() = default;

    reference operator*() { return *ptr; }

    pointer operator->() { return ptr; }

    ConstIterator &operator++() {
      ptr += 1;
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator new_iter = *this;
      ptr += 1;
      return new_iter;
    }

    ConstIterator &operator--() {
      ptr -= 1;
      return *this;
    }

    ConstIterator operator--(int) {
      ConstIterator new_iter = *this;
      ptr -= 1;
      return new_iter;
    }

    ConstIterator operator+(const int &ci) const {
      ConstIterator new_iter = *this;
      new_iter.ptr += ci;
      return new_iter;
    }

    ConstIterator &operator+=(const int &ci) {
      ptr = ptr + ci;
      return *this;
    }

    ConstIterator operator-(const int &ci) const {
      ConstIterator new_iter = *this;
      new_iter.ptr -= ci;
      return new_iter;
    }

    ConstIterator &operator-=(const int &ci) {
      ptr = ptr - ci;
      return *this;
    }

    bool operator==(const ConstIterator &iter) const {
      return (this->ptr == iter.ptr);
    }

    bool operator!=(const ConstIterator &iter) const {
      return (this->ptr != iter.ptr);
    }
  };

  Vector() : data_size(0), data_capacity(0), allocator() {}

  Vector(const size_t &sz, const value_type &elem = T())
      : data_size(sz), data_capacity(sz), allocator() {
    data = alloc_traits::allocate(allocator, data_size);
    for (size_t i = 0; i < data_size; ++i) {
      data[i] = elem;
    }
  }

  Vector(std::initializer_list<value_type> p)
      : data_size(p.size()), data_capacity(p.size()), allocator() {
    data = alloc_traits::allocate(allocator, data_size);
    size_t i = 0;
    for (const value_type &elem : p) {
      data[i++] = elem;
    }
  }

  Vector(const Vector<value_type, Allocator> &other)
      : data_size(other.data_size), data_capacity(other.data_capacity),
        allocator(other.allocator) {
    data = alloc_traits::allocate(allocator, data_size);
    for (size_t i = 0; i < data_size; ++i) {
      data[i] = other.data[i];
    }
  }

  ~Vector() {
    for (size_t i = 0; i < data_size; ++i) {
      data[i].~T();
    }
    alloc_traits::deallocate(allocator, data, data_size);
    data_capacity = 0;
    data_size = 0;
  }

  void resize(size_t sz) {
    if (sz > data_capacity) {
      value_type *newdata =
          alloc_traits::allocate(allocator, data_capacity * 2);
      for (size_t i = 0; i < data_size; ++i) {
        newdata[i] = data[i];
      }
      alloc_traits::deallocate(allocator, data, data_capacity);
      data_capacity *= 2;
      data = newdata;
      data_size = sz;
    } else if (sz < data_capacity) {
      data_size = sz;
    }
  }

  const value_type &operator[](size_t index) const { return data[index]; }

  value_type &operator[](size_t index) { return data[index]; }

  void push_back(const value_type &elem) {
    if (data_size + 1 > data_capacity) {
      resize(data_size + 1);
      data[data_size - 1] = elem;
    } else {
      data[++data_size - 1] = elem;
    }
  }

  void pop_back() { resize(data_size - 1); }

  Vector &operator=(const Vector<value_type, Allocator> &other) {
    data_size = other.data_size;
    data_capacity = other.data_capacity;
    data = alloc_traits::allocate(allocator, data_size);
    for (size_t i = 0; i < data_size; ++i) {
      data[i] = other.data[i];
    }
  }

  Iterator begin() noexcept { return Iterator(data); }

  ConstIterator cbegin() const noexcept { return ConstIterator(data); }

  Iterator end() { return Iterator(data + data_size); }

  ConstIterator cend() const { return ConstIterator(data + data_size); }

  size_t size() { return data_size; }

  size_t capacity() { return data_capacity; }
};
