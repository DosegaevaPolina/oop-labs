#include "octagon.hpp"
#include "pentagon.hpp"
#include "array.hpp"
#include "hexagon.hpp"
#include <gtest/gtest.h>

TEST(Pentagon, empty_constructor) {
  Pentagon<double> p;
  point<double> dot;
  dot.x = 0;
  dot.y = 0;
  point<double> c = p.center();
  EXPECT_EQ(c.x, dot.x);
  EXPECT_EQ(c.y, dot.y);
  EXPECT_EQ((double)p, 0);
}

TEST(Pentagon, vect_const) {
  double x[] = {1, 2, 3, 1, 2};
  double y[] = {1, 2, 3, 1, 2};
  Pentagon<double> p(x, y);

  point<double> dot;
  dot.x = 1.8, dot.y = 1.8;
  point<double> c = p.center();
  EXPECT_EQ(c.x, dot.x);
  EXPECT_EQ(c.y, dot.y);
}

TEST(Pentagon, equal) {
  double x[] = {1, 2, 3, 1, 2};
  double y[] = {1, 2, 3, 1, 2};
  Pentagon<double> p1(x, y), p2(x, y);
  EXPECT_EQ(p1, p2);
}


TEST(Hexagon, empty) {
  Hexagon<double> p;
  point<double> dot;
  dot.x = 0;
  dot.y = 0;
  point<double> c = p.center();
  EXPECT_EQ(c.x, dot.x);
  EXPECT_EQ(c.y, dot.y);
  EXPECT_EQ((double)p, 0);
}

TEST(Hexagon, vect_const) {
  double x[] = {1, 2, 3, 1, 2, 3};
  double y[] = {1, 2, 3, 1, 2, 3};
  Hexagon<double> p(x, y);

  point<double> dot;
  dot.x = 2;
  dot.y = 2;
  point<double> c = p.center();
  EXPECT_EQ(c.x, dot.x);
  EXPECT_EQ(c.y, dot.y);
}

TEST(Hexagon, equal) {
  double x[] = {1, 2, 3, 1, 2, 3};
  double y[] = {1, 2, 3, 1, 2, 3};
  Hexagon<double> p1(x, y), p2(x, y);
  EXPECT_EQ(p1, p2);
}


TEST(Octagon, empty) {
  Octagon<double> p;
  point<double> dot;
  dot.x = 0, dot.y = 0;
  point<double> c = p.center();
  EXPECT_EQ(c.x, dot.x);
  EXPECT_EQ(c.y, dot.y);
  EXPECT_EQ((double)p, 0);
}

TEST(Octagon, vect_const) {
  double x[] = {1, 2, 3, 1, 2, 3, 1, 2};
  double y[] = {1, 2, 3, 1, 2, 3, 1, 2};
  Octagon<double> p(x, y);

  point<double> dot;
  dot.x = 1.875;
  dot.y = 1.875;
  point<double> c = p.center();
  EXPECT_EQ(c.x, dot.x);
  EXPECT_EQ(c.y, dot.y);
}

TEST(Octagon, equal) {
  double x[] = {1, 2, 3, 1, 2, 3, 1, 2};
  double y[] = {1, 2, 3, 1, 2, 3, 1, 2};
  Octagon<double> p1(x, y), p2(x, y);
  EXPECT_EQ(p1, p2);
}

TEST(Array, size_conrtuctor) {
  Array<Figure<double>> a(15);

  EXPECT_EQ(a.get_size(), 15);

  for (int i = 0; i < 15; ++i)
    EXPECT_EQ(a[i], nullptr);
}
