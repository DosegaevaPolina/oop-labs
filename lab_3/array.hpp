#pragma once

#include "figure.hpp"

class Array {
private:
  Figure **data;
  int size;

public:
  Array();
  Array(int);
  ~Array();

  void delete_at(int idx);
  void set(int idx, Figure *other);
  Figure* operator[](int idx);
  double area() const;
  int get_size() { return size; }
  friend std::ostream& operator<<(std::ostream &os, const Array &a);
};
