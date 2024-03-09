#include <thread>
#include "editor.hpp"
#include "print.hpp"


int main() {
  Editor ed;

  for (int i = 0; i < 16; ++i) {
    Spawner *spawner = Spawner::random_spawner(ed.map);
    ed.add_npc(spawner->spawn_random());
    delete spawner;
  }

  ed.print_map();
  print('\n');

  for (int i = 0; i < 10; ++i) {
    std::thread t([](Editor &e) {
      e.move_npcs();
      e.fight();
    }, std::ref(ed));
    t.join();

    print('\n');
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ed.print_map();
  }

  print("\nSurvivors:\n", ed);
  ed.dump("lab_7/survived.txt");
}
