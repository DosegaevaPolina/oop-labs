#pragma once

#include "figure.hpp"

class Pentagon : public Figure {
protected:
  double calculate_area(const point &p1, const point &p2) const override;
public:
  Pentagon() : Figure(5) {}
  Pentagon(const double x[5], const double y[5]) : Figure(5, x, y) {}

  bool operator==(Pentagon &other) const;
  Pentagon& operator=(Pentagon &other);
  Pentagon& operator=(Pentagon &&other);
};

