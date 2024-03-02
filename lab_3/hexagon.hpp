#pragma once

#include "figure.hpp"

class Hexagon : public Figure {
protected:
  double calculate_area(const point &p1, const point &p2) const override;
public:
  Hexagon() : Figure(6) {}
  Hexagon(const double x[6], const double y[6]) : Figure(6, x, y) {}

  bool operator==(Hexagon &other) const;
  Hexagon& operator=(Hexagon &other);
  Hexagon& operator=(Hexagon &&other);
};

