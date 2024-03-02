#pragma once

#include "figure.hpp"
#include <cmath>

template <typename T>
class Octagon : public Figure<T> {
protected:
  double calculate_area(const point<T> &p1, const point<T> &p2) const override;
public:
  Octagon() : Figure<T>(8) {}
  Octagon(const T x[8], const T y[8]) : Figure<T>(8, x, y) {}

  bool operator==(Octagon &other) const;
  Octagon& operator=(Octagon &other);
  Octagon& operator=(Octagon &&other);
};

template <typename T>
double Octagon<T>::calculate_area(const point<T> &p1, const point<T> &p2) const {
  return 2 * dist2(this->coords[0], this->coords[1]) * (sqrt(2) + 1);
}

template <typename T>
bool Octagon<T>::operator==(Octagon &other) const {
  return (T)*this == (T)other;
}

template <typename T>
Octagon<T>& Octagon<T>::operator=(Octagon &other) {
  for (int i = 0; i < this->n; ++i)
    this->coords[i] = other.coords[i];
  return *this;
}

template <typename T>
Octagon<T>& Octagon<T>::operator=(Octagon &&other) {
  this->coords = other.coords;
  other.coords = nullptr;
  return *this;
}
