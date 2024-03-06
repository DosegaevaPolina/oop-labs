#include "editor.hpp"
#include <gtest/gtest.h>
#include <sstream>

TEST(Editor, FromStream) {
  Editor ed("lab_6/npc.txt", "/tmp/log.txt");
  std::istringstream iss("Elf Isildur 13 42");
  ed.from_stream(iss);
  auto npc = ed.data["Isildur"];
  EXPECT_EQ(npc->x, 13);
  EXPECT_EQ(npc->y, 42);
}
