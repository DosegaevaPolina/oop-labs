#include <iostream>
#include <filesystem>
#include "editor.hpp"


namespace fs = std::filesystem;

int main() {
  auto pwd = fs::current_path();
  Editor ed(pwd / "lab_6/npc.txt", pwd / "log.txt");
  ed.add_npc(new Elf("Laslo", 3, 3));
  std::cout << ed << std::endl;
  ed.dump("lab_6/out_npc.txt");

  ed.fight(10);
  std::cout <<  std::endl << ed;
}
