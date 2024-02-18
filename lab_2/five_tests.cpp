#include <gtest/gtest.h>
#include "five.hpp"


TEST(Constructors, default) {
  Five num = Five();
  EXPECT_EQ(num.to_string(), "\0");
  EXPECT_EQ(num.get_size(), 0);
}


TEST(Constructors, ntimes) {
  Five num = Five(4, '1');
  EXPECT_EQ(num.to_string(), "1111");
  EXPECT_EQ(num.get_size(), 4);
}


TEST(Constructors, bad_digit_9) {
  EXPECT_ANY_THROW(Five num = Five(4, '9'));
}


TEST(Constructors, bad_digit_b) {
  EXPECT_ANY_THROW(Five num = Five(4, 'b'));
}


TEST(Constructors, list_empty) {
  Five num = Five({});
  EXPECT_EQ(num.get_size(), 0);
  EXPECT_EQ(num.to_string(), "");
}


TEST(Constructors, list) {
  Five num = Five({'4', '2'});
  EXPECT_EQ(num.get_size(), 2);
  EXPECT_EQ(num.to_string(), "42");
}


TEST(Constructors, list_exception) {
  EXPECT_ANY_THROW(Five num = Five({'b', '2'}));
}


TEST(Constructors, list_exception_2) {
  EXPECT_ANY_THROW(Five num = Five({'7', '2'}));
}


TEST(Constructors, string) {
  Five num = Five("42");
  EXPECT_EQ(num.to_string(), "42");
  EXPECT_EQ(num.get_size(), 2);
}


TEST(Constructors, string_empty) {
  Five num = Five("");
  EXPECT_EQ(num.to_string(), "");
  EXPECT_EQ(num.get_size(), 0);
}


TEST(Constructors, string_exception) {
  EXPECT_ANY_THROW(Five num = Five("b2"));
}


TEST(Constructors, string_exception_2) {
  EXPECT_ANY_THROW(Five num = Five("72"));
}


TEST(Constructors, copy) {
  Five num = Five("42");
  Five num2 = Five(num);
  num = Five("1111");
  EXPECT_EQ(num2.to_string(), "42");
  EXPECT_EQ(num.to_string(), "1111");
}


TEST(Constructors, rvalue_copy) {
  Five num = Five(Five("42"));
  EXPECT_EQ(num.to_string(), "42");
}


// Operators testing

TEST(Operators, sum) {
  Five num = Five("12");
  Five num2 = Five("12");
  EXPECT_EQ((num + num2).to_string(), "24");
}


TEST(Operators, sum_carry) {
  Five num = Five("14");
  Five num2 = Five("12");
  EXPECT_EQ((num + num2).to_string(), "31");
}


TEST(Operators, sum_with_resize) {
  Five num = Five("3");
  Five num2 = Five("4");
  EXPECT_EQ((num + num2).to_string(), "12");
}


TEST(Operators, plus_zero) {
  Five num = Five("0");
  Five num2 = Five("4");
  EXPECT_EQ((num + num2).to_string(), "4");
}


TEST(Operators, plus_empty) {
  Five num = Five("");
  Five num2 = Five("4");
  EXPECT_EQ((num + num2).to_string(), "4");
}


TEST(Operators, sub) {
  Five num = Five("24");
  Five num2 = Five("12");
  EXPECT_EQ((num - num2).to_string(), "12");
}


TEST(Operators, sub_with_transfer) {
  Five num = Five("21");
  Five num2 = Five("12");
  EXPECT_EQ((num - num2).to_string(), "4");
}


TEST(Operators, sub_exception) {
  Five num = Five("42000");
  Five num2 = Five("1");
  EXPECT_ANY_THROW(num2 - num);
}


TEST(Operators, sub_uneven_transfer) {
  Five num = Five("1100");
  Five num2 = Five("1");
  EXPECT_EQ((num - num2).to_string(), "1044");
}


TEST(Operators, sub_uneven_transfer_2) {
  Five num = Five("42000");
  Five num2 = Five("111");
  EXPECT_EQ((num - num2).to_string(), "41334");
}


TEST(Operators, sub_uneven_transfer_3) {
  Five num = Five("42000");
  Five num2 = Five("110");
  EXPECT_EQ((num - num2).to_string(), "41340");
}


TEST(Operators, sub_zero) {
  Five num = Five("42000");
  Five num2 = Five("0");
  EXPECT_EQ((num - num2).to_string(), "42000");
}


TEST(Operators, sub_empty) {
  Five num = Five("42000");
  Five num2 = Five("");
  EXPECT_EQ((num - num2).to_string(), "42000");
}


TEST(Operators, assignment) {
  Five num;
  num = Five("42");
  EXPECT_EQ(num.to_string(), "42");
}


TEST(Operators, comparison) {
  Five num = Five("42");
  Five num2 = Five("11");
  EXPECT_TRUE(num > num2);
  EXPECT_FALSE(num < num2);
  EXPECT_TRUE(num2 < num);
  EXPECT_FALSE(num2 > num);
}


TEST(Operators, equality) {
  Five num = Five("12");
  Five num2 = num;
  EXPECT_TRUE(num == num2);
  EXPECT_FALSE(num > num);
}

