#pragma once

#include <string>
#include <iostream>
#include <unistd.h>

using std::string;

class NPC;
class Bear;
class Elf;
class Rogue;

// интерфейс Посетителя объявляет набор методов посещения, соответствующих
// классам компонентов. Сигнатура метода посещения позволяет посетителю 
// определить конкретный класс компонента, с которым он имеет дело
class Visitor {
public:
  virtual ~Visitor() {}
  virtual void VisitBear(Bear *element, NPC *other) = 0;
  virtual void VisitElf(Elf *element, NPC *other) = 0;
  virtual void VisitRogue(Rogue *element, NPC *other) = 0;
};


// объявляем операции, которые должны выполнять все конкретные NPC
class NPC {
public:
  string name;
  int x, y;
  bool alive;

  NPC(const string &name, int x, int y) : name(name), x(x), y(y), alive(true) {}

  virtual ~NPC() {}

  virtual const string& type_str() const = 0;
  virtual void Accept(Visitor *visitor, NPC *other) = 0;

  int dist2(const NPC *other) const;

  friend std::ostream &operator<<(std::ostream &os, const NPC &npc)  {
    os << npc.type_str() << " " << npc.name << " "
              << npc.x << " "  << npc.y;
    return os;
  }
};


// конкретные NPC предоставляют различные реализации интерфейса
class Bear : public NPC {
public:
  inline static const string type_name = "Bear";

  Bear(string name, int x, int y) : NPC(name, x, y) {}

  const string &type_str() const override { return type_name; }

  void Accept(Visitor *visitor, NPC *other) override {
    // std::cout << "Bear accepting visitor\n";
    visitor->VisitBear(this, other);
  }
};

class Elf : public NPC {
public:
  inline static const string type_name = "Elf";

  Elf(string name, int x, int y) : NPC(name, x, y) {}

  const string &type_str() const override { return type_name; }

  void Accept(Visitor *visitor, NPC *other) override {
    // std::cout << "Elf accepting visitor\n";
    visitor->VisitElf(this, other);
  }
};

class Rogue : public NPC {
public:
  inline static const string type_name = "Rogue";

  Rogue(string name, int x, int y) : NPC(name, x, y) {}

  const string &type_str() const override { return type_name; }

  void Accept(Visitor *visitor, NPC *other) override {
    // std::cout << "Rogue accepting visitor\n";
    visitor->VisitRogue(this, other);
  }
};

using int_pair = std::pair<int,int>;
// класс Spawner объявляет фабричный метод, который должен возвращать объект класса NPC
// подклассы Spawner'a предоставляют реализацию этого метода
class Spawner {
protected:
  int_pair x_range, y_range;

  static std::string rand_name();
  int rand_x() const;
  int rand_y() const;

public:
  Spawner(int_pair x_range, int_pair y_range) : x_range(x_range), y_range(y_range) {}
  virtual ~Spawner(){};
  virtual NPC* spawn(string name, int x, int y) const = 0;
  virtual NPC* spawn_random() const = 0;
  static Spawner* from_string(string, int_pair, int_pair);
};

// конкретные Spawner'ы переопределяют фабричный метод для того, чтобы изменить тип получаемого NPC
class BearSpawner : public Spawner {
  using Spawner::Spawner;
public:
  NPC *spawn(string name, int x, int y) const override {
    return new Bear(name, x, y);
  }
  NPC *spawn_random() const override {
    return new Bear(rand_name(), rand_x(), rand_y());
  }
};

class ElfSpawner : public Spawner {
  using Spawner::Spawner;
public:
  NPC *spawn(string name, int x, int y) const override {
    return new Elf(name, x, y);
  }
  NPC *spawn_random() const override {
    return new Elf(rand_name(), rand_x(), rand_y());
  }
};

class RogueSpawner : public Spawner {
  using Spawner::Spawner;
public:
  NPC *spawn(string name, int x, int y) const override {
    return new Rogue(name, x, y);
  }
  NPC *spawn_random() const override {
    return new Elf(rand_name(), rand_x(), rand_y());
  }
};

// конкретные Посетители реализуют несколько версий одного и того же алгоритма,
// которые могут работать со всеми классами конкретных компонентов.
class FightVisitor : public Visitor {
public:
  ~FightVisitor() override {}

  void VisitBear(Bear *bear, NPC *other) override {
    // медведь убивает эльфа
    if (other->type_str() == Elf::type_name) {
      other->alive = false;
    }
  }

  void VisitElf(Elf *elf, NPC *other) override {
    // эльф убивает разбойника
    if (other->type_str() == Rogue::type_name) {
      other->alive = false;
    }
    // медведь убивает эльфа
    if (other->type_str() == Bear::type_name) {
      elf->alive = false;
    }
  }

  void VisitRogue(Rogue *rogue, NPC *other) override {
    // разбойники убивают друг друга
    if (other->type_str() == Rogue::type_name) {
      rogue->alive = false;
      other->alive = false;
    }
    // эльф убивает разбойника
    if (other->type_str() == Elf::type_name) {
      rogue->alive = false;
    }
  }
};


