#include <iostream>
#include <filesystem>
#include "editor.hpp"


namespace fs = std::filesystem;

int main() {
  auto pwd = fs::current_path();
  Editor ed(pwd / "lab_7/npc.txt", pwd / "log.txt");

  ed.add_npc(new Elf("Laslo", 3, 3));
  std::cout << ed << std::endl;

  for (int i = 0; i < 16; ++i) {
    Spawner *spawner = Spawner::random_spawner(ed.map);
    ed.add_npc(spawner->spawn_random());
    delete spawner;
  }

  ed.print_map();
  ed.fight();
  std::cout << std::endl;

  for (int i = 0; i < 3; ++i) {
    ed.move_npcs();
    ed.print_map();
    ed.fight();
    std::cout << std::endl;
  }

  std::cout << std::endl << ed;
  ed.dump("lab_6/out_npc.txt");
}
