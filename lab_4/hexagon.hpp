#pragma once

#include "figure.hpp"
#include <cmath>

template <typename T>
class Hexagon : public Figure<T> {
protected:
  double calculate_area(const point<T> &p1, const point<T> &p2) const override;
public:
  Hexagon() : Figure<T>(6) {}
  Hexagon(const T x[6], const T y[6]) : Figure<T>(6, x, y) {}

  bool operator==(Hexagon &other) const;
  Hexagon& operator=(Hexagon &other);
  Hexagon& operator=(Hexagon &&other);
};

template <typename T>
double Hexagon<T>::calculate_area(const point<T> &p1, const point<T> &p2) const {
  return 2 * dist2(this->coords[0], this->coords[1]) * (sqrt(2) + 1);
}

template <typename T>
bool Hexagon<T>::operator==(Hexagon &other) const {
  return (T)*this == (T)other;
}

template <typename T>
Hexagon<T>& Hexagon<T>::operator=(Hexagon &other) {
  for (int i = 0; i < this->n; ++i)
    this->coords[i] = other.coords[i];
  return *this;
}

template <typename T>
Hexagon<T>& Hexagon<T>::operator=(Hexagon &&other) {
  this->coords = other.coords;
  other.coords = nullptr;
  return *this;
}
