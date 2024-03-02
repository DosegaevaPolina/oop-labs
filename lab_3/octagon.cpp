#include "octagon.hpp"
#include <cmath>

double Octagon::calculate_area(const point &p1, const point &p2) const {
  return 2 * dist2(coords[0], coords[1]) * (sqrt(2) + 1);
}

bool Octagon::operator==(Octagon &other) const {
  return (double)*this == (double)other;
}

Octagon& Octagon::operator=(Octagon &other) {
  for (int i = 0; i < n; ++i)
    coords[i] = other.coords[i];
  return *this;
}

Octagon& Octagon::operator=(Octagon &&other) {
  coords = other.coords;
  other.coords = nullptr;
  return *this;
}
