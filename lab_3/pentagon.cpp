#include "pentagon.hpp"
#include <cmath>

double Pentagon::calculate_area(const point &p1, const point &p2) const {
  return 2 * dist2(coords[0], coords[1]) * (sqrt(2) + 1);
}

bool Pentagon::operator==(Pentagon &other) const {
  return (double)*this == (double)other;
}

Pentagon& Pentagon::operator=(Pentagon &other) {
  for (int i = 0; i < n; ++i)
    coords[i] = other.coords[i];
  return *this;
}

Pentagon& Pentagon::operator=(Pentagon &&other) {
  coords = other.coords;
  other.coords = nullptr;
  return *this;
}
