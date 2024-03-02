#pragma once

#include <iostream>
#include <stdexcept>
#include <memory>

template <typename T>
struct point {
  T x, y;

  point() : x(0), y(0) {}
};

template <typename T>
inline T dist2(point<T> &a, point<T> &b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

template <typename T>
class Figure {
protected:
  const int n;
  std::unique_ptr<point<T>[]> coords;
  Figure(int n);
  Figure(int n, const T x[n], const T y[n]);
  virtual double calculate_area(const point<T> &p1, const point<T> &p2) const = 0;

public:
  point<T> center() const;
  operator double() const;

  friend std::ostream &operator<<(std::ostream &os, const Figure &p) {
    for (int i = 0; i < p.n; ++i) {
      os << "x[" << i << "]: "
         << p.coords[i].x << std::endl
         << "y[" << i << "]: "
         << p.coords[i].y << std::endl;
    }
    return os;
  }
  
  friend std::istream &operator>>(std::istream &is, Figure &p) {
    T x[p.n], y[p.n];
    for (int i = 0; i < p.n; ++i) {
      std::cout << "x[" << i << "]: ";
      is >> p.coords[i].x;
      std::cout << "y[" << i << "]: ";
      is >> p.coords[i].y;
    }
    return is;
  }
};

template <typename T>
Figure<T>::Figure(int n) : n(n) {
  if (n < 2)
    throw std::invalid_argument("You need more points to make a figure");
  coords = std::make_unique<point<T>[]>(n);
}

template <typename T>
Figure<T>::Figure(int n, const T x[n], const T y[n]) : Figure(n) {
  for (int i = 0; i < n; ++i) {
    coords[i].x = x[i];
    coords[i].y = y[i];
  }
}

template <typename T>
point<T> Figure<T>::center() const { 
  point<T> c;
  for (int i = 0; i < n; ++i) {
    c.x += coords[i].x;
    c.y += coords[i].y;
  }
  c.x /= n;
  c.y /= n;
  return c;
}

template <typename T>
Figure<T>::operator double() const { return calculate_area(coords[0], coords[1]); }

