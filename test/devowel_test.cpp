#include <gtest/gtest.h>
#include <iostream>

#include "devowel.h"

TEST(DevowelTest, AllVowels) {
  string s = devowel(string("aaaaa"));
  EXPECT_EQ(s.length(), 0);
}
