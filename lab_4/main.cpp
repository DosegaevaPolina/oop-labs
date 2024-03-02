#include "figure.hpp"
#include "array.hpp"
#include "octagon.hpp"
#include "pentagon.hpp"
#include "hexagon.hpp"
#include <iostream>
#include <cmath>
#include <memory>

using std::make_shared;

int main() {
  double c1=sqrt(5)-1, c2=sqrt(5)+1;
  double s1=sqrt(10 + 2*sqrt(5)), s2=sqrt(10 - 2*sqrt(5));
  double x5[] = {0, -s1, -s2,  s2, s1};
  double y5[] = {4,  c1, -c2, -c2, c1};

  double x6[] = {2, 1, -1, -2, -1, 1};
  double y6[] = {0, sqrt(3), sqrt(3), 0, -sqrt(3), -sqrt(3)};

  double x8[] = {sqrt(2), 1, 0, -1, -sqrt(2), -1, 0, 1};
  double y8[] = {0, 1, sqrt(2), 1, 0, -1, -sqrt(2), -1};

  Array<Figure<double>> a(4);
  a[0] = make_shared<Pentagon<double>>(x5, y5);
  a[1] = make_shared<Hexagon<double>>(x6, y6);
  a[3] = make_shared<Octagon<double>>(x8, y8);

  std::cout << a << std::endl;

  for (int i = 0; i < a.get_size(); ++i) {
    auto fig = a[i];
    if (a[i] == nullptr) {
      std::cout << "The figure [" << i << "] has been deleted\n\n";
      continue;
    }
    std::cout << *a[i] << std::endl;
  }
}
