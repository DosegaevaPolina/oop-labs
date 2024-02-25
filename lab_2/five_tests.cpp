#include <gtest/gtest.h>
#include "five.hpp"


TEST(Constructors, default) {
  Five num;
  EXPECT_EQ(num.to_string(), "\0");
  EXPECT_EQ(num.get_size(), 0);
}


TEST(Constructors, ntimes) {
  Five num(4, '1');
  EXPECT_EQ(num.to_string(), "1111");
  EXPECT_EQ(num.get_size(), 4);

  EXPECT_ANY_THROW(Five(4, '9'));
}


TEST(Constructors, move) {
  Five num0(4, '1');
  Five num(std::move(num0));
  EXPECT_EQ(num.to_string(), "1111");
  EXPECT_EQ(num.get_size(), 4);
}


TEST(Constructors, list) {
  Five num({'4', '2'});
  EXPECT_EQ(num.get_size(), 2);
  EXPECT_EQ(num.to_string(), "42");

  Five empty({});
  EXPECT_EQ(empty.get_size(), 0);
  EXPECT_EQ(empty.to_string(), "");

  EXPECT_ANY_THROW(Five({'1', 'b'}));
}


TEST(Constructors, string) {
  Five num("42");
  EXPECT_EQ(num.to_string(), "42");
  EXPECT_EQ(num.get_size(), 2);

  Five empty("");
  EXPECT_EQ(empty.to_string(), "");
  EXPECT_EQ(empty.get_size(), 0);

  EXPECT_ANY_THROW(Five("-42"));  // '-' < '0'
  EXPECT_ANY_THROW(Five("b42"));  // 'b' > '4'
}


TEST(Constructors, copy) {
  Five num0("42");
  Five num = num0;
  EXPECT_EQ(num.to_string(), "42");
} 


// Operators testing

TEST(Operators, ostream) {
  Five num("42");
  stringstream s;
  s << num;
  EXPECT_EQ(num.to_string(), s.str());
}


TEST(Operators, sum) {
  EXPECT_EQ((Five("3") + Five("4")).to_string(), "12");
  EXPECT_EQ((Five("0") + Five("4")).to_string(), "4");
}


TEST(Operators, sub) {
  EXPECT_EQ((Five("10") - Five("1")).to_string(), "4");
  EXPECT_EQ((Five("1") - Five("1")).to_string(), "0");
  EXPECT_EQ((Five("") - Five("")).to_string(), "");
  EXPECT_ANY_THROW(Five("2") - Five("42"));  // o.size > size
  EXPECT_ANY_THROW(Five("2") - Five("4"));
}


TEST(Operators, assignment) {
  Five num0("42");
  Five num;
  num = num0;  // assignment: operator=(const Five &o)
  EXPECT_EQ(num.to_string(), "42");
  num = num;   // this == &o
  EXPECT_EQ(num.to_string(), "42");
  num = num0;  // size == o.size
  EXPECT_EQ(num.to_string(), "42");
}


TEST(Operators, move_assignment) {
  Five num;
  num = Five("42");  // move assignment: operator=(Five &&o)
  EXPECT_EQ(num.to_string(), "42");
  num = std::move(num);  // this == &o
  EXPECT_EQ(num.to_string(), "42");
}


TEST(Operators, comparison) {
  Five big("42");
  Five small("41");
  Five zero("0");

  EXPECT_TRUE(big > small);
  EXPECT_FALSE(small > big);
  EXPECT_FALSE(big > big);
  EXPECT_TRUE(big > zero);
  EXPECT_FALSE(zero > big);

  EXPECT_TRUE(small < big);
  EXPECT_FALSE(big < small);
  EXPECT_FALSE(big < big);
  EXPECT_TRUE(zero < big);
  EXPECT_FALSE(big < zero);
}


TEST(Operators, equality) {
  Five num("12");
  Five num2 = num;
  EXPECT_FALSE(num == Five("42"));
  EXPECT_FALSE(num == Five("1"));
  EXPECT_TRUE(num == num2);
  EXPECT_FALSE(num > num);
}
