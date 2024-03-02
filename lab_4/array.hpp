#pragma once

#include <memory>
#include <ostream>

using std::shared_ptr;
using std::unique_ptr;

template <class T>
class Array {
private:
  unique_ptr<shared_ptr<T>[]> data;
  int size;

public:
  Array(int);

  void delete_at(int idx);
  shared_ptr<T>& operator[](int idx);
  double area() const;
  int get_size() { return size; }

  friend std::ostream &operator<<(std::ostream &os, const Array &a) {
    for (int i = 0; i < a.size; ++i) {
      if (a.data[i] == nullptr) continue;
      auto c = a.data[i]->center();
      os << "[" << i << "] center: ("
         << c.x << ", " << c.y << "), area: "
         << (double)*a.data[i] << std::endl;
    }
    return os;
  }
};

template <class T>
Array<T>::Array(int size) : size(size) {
  data = unique_ptr<shared_ptr<T>[]>(new shared_ptr<T>[size]);
  for (int i = 0; i < size; ++i)
    data[i] = nullptr;
}

template <class T>
shared_ptr<T>& Array<T>::operator[](int idx) {
  return data[idx];
}

template <class T>
double Array<T>::area() const {
  double sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += (double)*data[i];
  }
  return sum;
}

template <class T>
void Array<T>::delete_at(int idx) {
  if (0 <= idx && idx < size)
    // вызываем деструктор shared_ptr
    data[idx] = nullptr;  // то же, что data[idx].reset();
}

