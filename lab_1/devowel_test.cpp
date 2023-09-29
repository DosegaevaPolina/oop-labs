#include <gtest/gtest.h>
#include <iostream>

#include "devowel.h"

TEST(DevowelTest, AllVowels) {
  string s = devowel(string("aaaaa"));
  EXPECT_EQ(s.length(), 0);
}

TEST(DevowelTest, TwoVowels) {
	string s = devowel(string("paul"));
	EXPECT_EQ(s.length(), 2);
}
