#include "octagon.hpp"
#include "figure.hpp"
#include "pentagon.hpp"
#include "array.hpp"
#include "hexagon.hpp"
#include <iostream>
#include <cmath>

int main() {
  double c1=sqrt(5)-1, c2=sqrt(5)+1;
  double s1=sqrt(10 + 2*sqrt(5)), s2=sqrt(10 - 2*sqrt(5));
  double x5[] = {0, -s1, -s2,  s2, s1};
  double y5[] = {4,  c1, -c2, -c2, c1};

  double x6[] = {2, 1, -1, -2, -1, 1};
  double y6[] = {0, sqrt(3), sqrt(3), 0, -sqrt(3), -sqrt(3)};

  double x8[] = {sqrt(2), 1, 0, -1, -sqrt(2), -1, 0, 1};
  double y8[] = {0, 1, sqrt(2), 1, 0, -1, -sqrt(2), -1};

  Pentagon p(x5, y5);
  Hexagon h(x6, y6);
  Octagon o(x8, y8);

  Array q(3);

  q.set(0, &p);
  q.set(1, &h);
  q.set(2, &o);

  std::cout << q;

  for (int i = 0; i < 3; ++i) {
    const Figure *fig = q[i];
    if (q[i] == nullptr) {
      std::cout << "The figure [" << i << "] has been deleted" << std::endl;
    } else if (typeid(p) == typeid(*fig)) {
      std::cout << *(Pentagon *)q[i];
    } else if (typeid(h) == typeid(*fig)) {
      std::cout << *(Hexagon *)q[i];
    } else if (typeid(o) == typeid(*fig)) {
      std::cout << *(Octagon *)q[i];
    }
  }

  std::cout << "\n\n";

  Pentagon p2;
  p2 = p;
  std::cout << p2 << "\n\n"; 
  std::cout.flush();
}
