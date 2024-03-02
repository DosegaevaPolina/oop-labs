#include "array.hpp"

Array::Array() : size(0), data(new Figure *[0]) {}

Array::Array(int size) : size(size) {
  data = new Figure *[size];
  for (int i = 0; i < size; ++i)
    data[i] = nullptr;
}

Array::~Array() { delete[] data; }

Figure* Array::operator[](int idx) {
  return (0 <= idx && idx < size) ? data[idx] : nullptr;
}

double Array::area() const {
  double sum = 0;
  for (int i = 0; i < size; ++i) {
    sum += (double)*data[i];
  }
  return sum;
}

std::ostream &operator<<(std::ostream &os, const Array &a) {
  for (int i = 0; i < a.size; ++i) {
    if (a.data[i] == nullptr) continue;
    point c = a.data[i]->center();
    os << "[" << i << "] center: ("
       << c.x << ", " << c.y << "), area: "
       << (double)*a.data[i] << std::endl;
  }
  return os;
}

void Array::delete_at(int idx) {
  delete data[idx];
  data[idx] = nullptr;
}

void Array::set(int idx, Figure *other) {
  if (data[idx] != nullptr)
    delete data[idx];
  data[idx] = other;
}
