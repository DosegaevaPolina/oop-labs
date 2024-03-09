#include <iostream>
#include <thread>
#include "editor.hpp"


int main() {
  Editor ed;

  for (int i = 0; i < 16; ++i) {
    Spawner *spawner = Spawner::random_spawner(ed.map);
    ed.add_npc(spawner->spawn_random());
    delete spawner;
  }

  ed.print_map();
  ed.fight();
  std::cout << std::endl;

  for (int i = 0; i < 10; ++i) {
    ed.move_npcs();
    ed.print_map();
    ed.fight();
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

  std::cout << "\nSurvivors:\n" << ed;
  ed.dump("lab_6/out_npc.txt");
}
