#pragma once

#include <iostream>

struct point {
  double x, y;

  point() : x(0), y(0) {}
};

inline double dist2(point &a, point &b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

class Figure {
protected:
  const int n;
  point *coords;
  Figure(int n);
  Figure(int n, const double x[n], const double y[n]);
  virtual double calculate_area(const point &p1, const point &p2) const = 0;

public:
  virtual ~Figure();
  point center() const;
  operator double() const;
  friend std::ostream& operator<<(std::ostream &os, const Figure &p);
  friend std::istream& operator>>(std::istream &is, Figure &p);
};
