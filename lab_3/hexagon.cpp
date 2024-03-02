#include "hexagon.hpp"
#include <cmath>

double Hexagon::calculate_area(const point &p1, const point &p2) const {
  return 2 * dist2(coords[0], coords[1]) * (sqrt(2) + 1);
}

bool Hexagon::operator==(Hexagon &other) const {
  return (double)*this == (double)other;
}

Hexagon& Hexagon::operator=(Hexagon &other) {
  for (int i = 0; i < n; ++i)
    coords[i] = other.coords[i];
  return *this;
}

Hexagon& Hexagon::operator=(Hexagon &&other) {
  coords = other.coords;
  other.coords = nullptr;
  return *this;
}
