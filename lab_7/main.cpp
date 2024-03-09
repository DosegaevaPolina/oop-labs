#include <mutex>
#include <thread>
#include "editor.hpp"
#include "print.hpp"


enum class State {
  move,
  fight,
  print
};

static State state;
std::mutex state_mutex;

#define STEPS 10

int main() {
  Editor ed;

  for (int i = 0; i < 16; ++i) {
    Spawner *spawner = Spawner::random_spawner(ed.map);
    ed.add_npc(spawner->spawn_random());
    delete spawner;
  }

  ed.print_map();
  state = State::move;

  std::thread t([&ed]() {
    print("move-thread started\n");
    for (int i = 0; i < STEPS; ++i) {
      while (true) {
        if(state_mutex.try_lock()) {
          if (state == State::move)
            break;
          state_mutex.unlock();
        }
      }

      print("in move-thread\n");
      ed.move_npcs();
      state = State::fight;
      state_mutex.unlock();
    }
  });

  std::thread t2([&ed]() {
    print("fight-thread started\n");
    for (int i = 0; i < STEPS; ++i) {
      while (true) {
        if(state_mutex.try_lock()) {
          if (state == State::fight)
            break;
          state_mutex.unlock();
        }
      }

      print("in fight-thread\n");
      ed.fight();
      state = State::print;
      state_mutex.unlock();
    };
  });


  for (int i = 0; i < STEPS; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while (true) {
      if (state_mutex.try_lock()) {
        if (state == State::print)
          break;
        state_mutex.unlock();
      }
    }

    ed.print_map();
    state = State::move;
    state_mutex.unlock();
  }


  t.join();
  t2.join();

  print("\nSurvivors:\n", ed);
  ed.dump("lab_7/survived.txt");
}
