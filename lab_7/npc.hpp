#pragma once

#include <string>
#include <iostream>
#include <unistd.h>
#include "map.hpp"

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
protected:
public:
  string name;
  int x, y;
  bool alive;

  NPC(const string &name, int x, int y) : name(name), x(x), y(y), alive(true) {}

  virtual ~NPC() {}

  virtual const string& type_str() const = 0;
  virtual const int get_velocity() const = 0;
  virtual const int get_range() const = 0;
  virtual const char get_symbol() const = 0;
  virtual void Accept(Visitor *visitor, NPC *other) = 0;

  int dist2(const NPC *other) const;
  static int dice_roll(int max);

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
  inline static const int velocity = 5;
  inline static const int range = 10;
  inline static const char symbol = 'B';

  Bear(string name, int x, int y) : NPC(name, x, y) {}

  const string& type_str() const override { return type_name; }

  const int get_velocity() const override { return velocity; }
  
  const int get_range() const override { return range; }

  const char get_symbol() const override { return symbol; }

  void Accept(Visitor *visitor, NPC *other) override {
    // std::cout << "Bear accepting visitor\n";
    visitor->VisitBear(this, other);
  }
};

class Elf : public NPC {
public:
  inline static const string type_name = "Elf";
  inline static const int velocity = 10;
  inline static const int range = 50;
  inline static const char symbol = 'e';

  Elf(string name, int x, int y) : NPC(name, x, y) {}

  const string &type_str() const override { return type_name; }

  const int get_velocity() const override { return velocity; }
  
  const int get_range() const override { return range; }

  const char get_symbol() const override { return symbol; }

  void Accept(Visitor *visitor, NPC *other) override {
    // std::cout << "Elf accepting visitor\n";
    visitor->VisitElf(this, other);
  }
};

class Rogue : public NPC {
public:
  inline static const string type_name = "Rogue";
  inline static const int velocity = 10;
  inline static const int range = 10;
  inline static const char symbol = 'r';

  Rogue(string name, int x, int y) : NPC(name, x, y) {}

  const string &type_str() const override { return type_name; }

  const int get_velocity() const override { return velocity; }
  
  const int get_range() const override { return range; }

  const char get_symbol() const override { return symbol; }

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
  static std::string rand_name();
  int rand_x() const;
  int rand_y() const;

public:
  virtual ~Spawner(){};
  virtual NPC* spawn(string name, int x, int y) const = 0;
  virtual NPC* spawn_random() const = 0;
  static Spawner* from_string(string, const char (&map)[Y][X]);
  static Spawner* random_spawner(const char (&map)[Y][X]);
};

// конкретные Spawner'ы переопределяют фабричный метод для того, чтобы изменить тип получаемого NPC
class BearSpawner : public Spawner {
  const char (&map)[Y][X];
public:
  BearSpawner(const char (&map)[Y][X]) : map(map) {}
  NPC *spawn(string name, int x, int y) const override {
    return new Bear(name, x, y);
  }
  NPC *spawn_random() const override;
};

class ElfSpawner : public Spawner {
  const char (&map)[Y][X];
public:
  ElfSpawner(const char (&map)[Y][X]) : map(map) {}
  NPC *spawn(string name, int x, int y) const override {
    return new Elf(name, x, y);
  }
  NPC *spawn_random() const override;
};

class RogueSpawner : public Spawner {
  const char (&map)[Y][X];
public:
  RogueSpawner(const char (&map)[Y][X]) : map(map) {}
  NPC *spawn(string name, int x, int y) const override {
    return new Rogue(name, x, y);
  }
  NPC *spawn_random() const override;
};

// конкретные Посетители реализуют несколько версий одного и того же алгоритма,
// которые могут работать со всеми классами конкретных компонентов.
class FightVisitor : public Visitor {
private:
  bool kills(NPC *npc, NPC *other) {
    if (npc->type_str()   == Bear::type_name &&
        other->type_str() == Elf::type_name)
      return true;
    if (npc->type_str()   == Elf::type_name &&
        other->type_str() == Rogue::type_name)
      return true;
    if (npc->type_str()   == Rogue::type_name &&
        other->type_str() == Rogue::type_name)
      return true;
    
    return false;
  }

  void VisitNPC(NPC *npc, NPC *other) {
    if (npc->dist2(other) <= npc->get_range() * npc->get_range()) {
      if (kills(npc,other)) {
        int attack = NPC::dice_roll(6);
        int defence = NPC::dice_roll(6);
        if (attack > defence)
          other->alive = false;
      }
    }
    if (npc->dist2(other) <= other->get_range() * other->get_range()) {
      if (kills(other,npc)) {
        int attack = NPC::dice_roll(6);
        int defence = NPC::dice_roll(6);
        if (attack > defence)
          npc->alive = false;
      }
    }
  }

public:
  ~FightVisitor() override {}

  void VisitBear(Bear *bear, NPC *other) override { VisitNPC(bear, other); }

  void VisitElf(Elf *elf, NPC *other) override { VisitNPC(elf, other); }

  void VisitRogue(Rogue *rogue, NPC *other) override { VisitNPC(rogue, other); }
};

