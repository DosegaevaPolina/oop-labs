#include "editor.hpp"
#include <shared_mutex>
#include <sstream>
#include <stdexcept>
#include <thread>
#include <utility>

std::optional<NPC*> Editor::from_string(const string &serialized) const {
  std::istringstream iss(serialized);
  int x, y;
  string type_name, name;

  iss >> type_name;
  if (iss.fail())
    return {};
  iss >> name;
  if (iss.fail())
    return {};
  iss >> x;
  if (iss.fail())
    return {};
  if (!(0 <= x && x <= X-1))
    return {};
  iss >> y;
  if (iss.fail())
    return {};
  if (!(0 <= y && y <= Y-1))
    return {};

  Spawner *spawner = Spawner::from_string(type_name, map);
  if (!spawner)
    return {};
  NPC* res = spawner->spawn(name, x, y);
  delete spawner;
  return res;
}

void Editor::update_map() {
  for (int y = 0; y < Y; ++y)
    for (int x = 0; x < X; ++x)
      map[y][x] = background_symbol;

  for (auto it = data.cbegin(); it != data.cend(); ++it) {
    auto npc = it->second;
    map[npc->y][npc->x] = npc->get_symbol();
  }
}

void Editor::print_map() {
  update_map();
  for (int y = 0; y < Y; ++y) {
    for (int x = 0; x < X; ++x)
      print(map[y][x]);
    print('\n');
  }
}

Editor::Editor() {
  update_map();

  stdout_observer = new StdoutObserver(*this);
  log_observer = nullptr;
}

Editor::Editor(const string &path, const string &log_path) {
  std::ifstream infile(path);
  if (!infile.is_open())
    throw std::invalid_argument(path + " - no such file");

  from_stream(infile);
  update_map();

  stdout_observer = new StdoutObserver(*this);
  log_observer = new LogObserver(*this, log_path);
}

Editor::~Editor() {
  for (auto it = data.begin(); it != data.end(); ++it) {
    delete it->second;
  }
  if (stdout_observer) delete stdout_observer;
  if (log_observer) delete log_observer;
}

void Editor::from_stream(std::istream &in) {
  std::string line;
  for (int i = 1; std::getline(in, line); ++i) {
    std::optional<NPC*> opt_npc = from_string(line);
    if (opt_npc)
      add_npc(opt_npc.value());
    else
      throw std::runtime_error("incorrect line: \n" + std::to_string(i) + ": " + line);
  }
}

void Editor::add_npc(NPC *npc) {
  const auto [it_data, success] = data.insert({npc->name, npc});
  if (!success)
    print("[WARNING] NPC with name \"", npc->name, "\" already exists\n");
}

void Editor::dump(const string &path) {
  std::ofstream outfile(path);
  if (!outfile.is_open())
    throw std::invalid_argument(path + " - no such file or directory");
  outfile << *this;
}

unsigned modulo(int value, int m) {
  int mod = value % m;
  return mod < 0 ? mod + m : mod;
}

void Editor::move_npcs() {
  std::lock_guard<std::shared_mutex> l(data_mutex);
  for (auto it = data.begin(); it != data.end(); ++it) { 
    auto npc = it->second;
    auto dx_dy = npc->get_velocity();
    int dx = rand() % (dx_dy + 1);
    int dy = dx_dy - dx;
    dx *= (rand() % 2) ? 1 : -1;
    dy *= (rand() % 2) ? 1 : -1;
    npc->x = modulo(npc->x + dx, X);
    npc->y = modulo(npc->y + dy, Y);
  }
} 


void Editor::fight() {
  Visitor *visitor = new FightVisitor;

  // проверяем расстояние и деремся
  for (auto it = data.begin(); it != data.end(); ++it) { 
    auto npc = it->second;
    for (auto it_other = it; it_other != data.end(); ++it_other) {
      if (it == it_other)
        continue;
      auto other_npc = it_other->second;
      if (npc->dist2(other_npc) > npc->get_range() * npc->get_range() &&
          npc->dist2(other_npc) > other_npc->get_range() * other_npc->get_range())
        continue;
      // мертвые не дерутся
      if (!npc->alive || !other_npc->alive)
        continue;

      std::thread t([npc, visitor, other_npc, this]() {
        std::lock_guard<std::shared_mutex> l(data_mutex);
        npc->Accept(visitor, other_npc);
      });
      t.join();
      if (!npc->alive) Notify(other_npc->name + " killed " + npc->name);
      if (!other_npc->alive) Notify(npc->name + " killed " + other_npc->name);
    }
  }

  // хороним погибших
  for (auto it = data.cbegin(); it != data.cend(); ) {
    auto npc = it->second;
    if (npc->alive == false)
      it = data.erase(it);
    else
      ++it;
  }

  // обновляем карту
  update_map();

  delete visitor;
}

void Editor::Attach(AbstractObserver *observer) { observer_list.push_back(observer); }

void Editor::Detach(AbstractObserver *observer) { observer_list.remove(observer); }

void Editor::Notify(const string &msg) {
  auto iterator = observer_list.begin();
  while (iterator != observer_list.end()) {
    (*iterator)->Update(msg);
    ++iterator;
  }
}

std::ostream &operator<<(std::ostream &os, const Editor &ed) {
  for (const auto &el : ed.data)
    os << *el.second << std::endl;
  return os;
}
