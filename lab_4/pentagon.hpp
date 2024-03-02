#pragma once

#include "figure.hpp"
#include <cmath>

template <typename T>
class Pentagon : public Figure<T> {
protected:
  double calculate_area(const point<T> &p1, const point<T> &p2) const override;
public:
  Pentagon() : Figure<T>(5) {}
  Pentagon(const T x[5], const T y[5]) : Figure<T>(5, x, y) {}

  bool operator==(Pentagon &other) const;
  Pentagon& operator=(Pentagon &other);
  Pentagon& operator=(Pentagon &&other);
};

template <typename T>
double Pentagon<T>::calculate_area(const point<T> &p1, const point<T> &p2) const {
  return 2 * dist2(this->coords[0], this->coords[1]) * (sqrt(2) + 1);
}

template <typename T>
bool Pentagon<T>::operator==(Pentagon &other) const {
  return (T)*this == (T)other;
}

template <typename T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon &other) {
  for (int i = 0; i < this->n; ++i)
    this->coords[i] = other.coords[i];
  return *this;
}

template <typename T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon &&other) {
  this->coords = other.coords;
  other.coords = nullptr;
  return *this;
}
