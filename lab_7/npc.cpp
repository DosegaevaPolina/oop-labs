#include "npc.hpp"
#include "map.hpp"

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
  return rand() % X;
}

int Spawner::rand_y() const {
  return rand() % Y;
}

Spawner* Spawner::from_string(string type, const char (&map)[Y][X]) {
  if (type == Bear::type_name)
    return new BearSpawner(map);
  if (type == Elf::type_name)
    return new ElfSpawner(map);
  if (type == Rogue::type_name)
    return new RogueSpawner(map);
  return nullptr;
}

Spawner* Spawner::random_spawner(const char (&map)[Y][X]) {
  switch (rand() % 3) {
  case 0:
    return new BearSpawner(map);
  case 1:
    return new ElfSpawner(map);
  case 2:
    return new RogueSpawner(map);
  }
  return nullptr;
}

NPC* BearSpawner::spawn_random() const {
  int x=-1, y=-1;
  do {
    x = rand_x();
    y = rand_y();
    // std::cout << "x: " << x << "\ty: " << y << std::endl;
  } while (map[y][x] != BG);
  return new Bear(rand_name(), x, y);
}

NPC* ElfSpawner::spawn_random() const {
  int x=-1, y=-1;
  do {
    x = rand_x();
    y = rand_y();
    // std::cout << "x: " << x << "\ty: " << y << std::endl;
  } while (map[y][x] != BG);
  return new Elf(rand_name(), x, y);
}

NPC* RogueSpawner::spawn_random() const {
  int x=-1, y=-1;
  do {
    x = rand_x();
    y = rand_y();
    // std::cout << "x: " << x << "\ty: " << y << std::endl;
  } while (map[y][x] != BG);
  return new Rogue(rand_name(), x, y);
}

int NPC::dist2(const NPC *other) const {
  return (x - other->x) * (x - other->x) + (y - other->y) * (y - other->y);
}

int NPC::dice_roll(int max) { return 1 + (rand() % max); }

