#include "figure.hpp"

#include <stdexcept>

Figure::Figure(int n) : n(n) {
  if (n < 2)
    throw std::invalid_argument("You need more points to make a figure");
  coords = new point[n];
}

Figure::Figure(int n, const double x[n], const double y[n]) : Figure(n) {
  for (int i = 0; i < n; ++i) {
    coords[i].x = x[i];
    coords[i].y = y[i];
  }
}

Figure::~Figure() {
  if (coords != nullptr)
    delete[] coords;
}

point Figure::center() const { 
  point c;
  for (int i = 0; i < n; ++i) {
    c.x += coords[i].x;
    c.y += coords[i].y;
  }
  c.x /= n;
  c.y /= n;
  return c;
}

Figure::operator double() const { return calculate_area(coords[0], coords[1]); }

std::ostream &operator<<(std::ostream &os, const Figure &p) {
  for (int i = 0; i < p.n; ++i) {
    os << "x[" << i << "]: "
       << p.coords[i].x << std::endl
       << "y[" << i << "]: "
       << p.coords[i].y << std::endl;
  }
  return os;
}

std::istream &operator>>(std::istream &is, Figure &p) {
  double x[p.n], y[p.n];
  for (int i = 0; i < p.n; ++i) {
    std::cout << "x[" << i << "]: ";
    is >> p.coords[i].x;
    std::cout << "y[" << i << "]: ";
    is >> p.coords[i].y;
  }
  return is;
}
