#pragma once

#include "figure.hpp"

class Octagon : public Figure {
protected:
  double calculate_area(const point &p1, const point &p2) const override;
public:
  Octagon() : Figure(8) {}
  Octagon(const double x[8], const double y[8]) : Figure(8, x, y) {}

  bool operator==(Octagon &other) const;
  Octagon &operator=(Octagon &other);
  Octagon &operator=(Octagon &&other);
};

