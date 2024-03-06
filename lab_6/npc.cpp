#include "npc.hpp"

std::string Spawner::rand_name() {
  const char alphanum[] = "0123456789"
                          "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                          "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  // 4 <= len <= 10
  int len = 4 + rand() % 7;
  tmp_s.reserve(len);

  for (int i = 0; i < len; ++i) {
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return tmp_s;
}

int Spawner::rand_x() const {
  return x_range.first + (rand() % static_cast<int>(x_range.second - x_range.first + 1));
}

int Spawner::rand_y() const {
  return y_range.first + (rand() % static_cast<int>(y_range.second - y_range.first + 1));
}

Spawner* Spawner::from_string(string type, int_pair x_range, int_pair y_range) {
  if (type == Bear::type_name)
    return new BearSpawner(x_range, y_range);
  if (type == Elf::type_name)
    return new ElfSpawner(x_range, y_range);
  if (type == Rogue::type_name)
    return new RogueSpawner(x_range, y_range);
  return nullptr;
}

int NPC::dist2(const NPC *other) const {
  return (x - other->x) * (x - other->x) + (y - other->y) * (y - other->y);
}
