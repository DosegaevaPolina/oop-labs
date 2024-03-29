#pragma once

#include "npc.hpp"
#include "print.hpp"
#include <fstream>
#include <map>
#include <optional>
#include <list>
#include <shared_mutex>


class AbstractObserver;


class Editor {
private:
  std::map<std::string, NPC*> data;
  std::shared_mutex data_mutex;
  std::list<AbstractObserver*> observer_list;
  AbstractObserver *stdout_observer, *log_observer;

  std::optional<NPC*> from_string(const string &serialized) const; 
  void from_stream(std::istream &in);
  void update_map();

public:
  inline static const char background_symbol = BG;
  char map[Y][X];
  std::shared_mutex map_mutex;

  Editor();
  Editor(const string &path, const string &log_path);
  ~Editor();
  void add_npc(NPC *npc);
  friend std::ostream &operator<<(std::ostream &os, const Editor &ed);
  void dump(const string &path);
  void fight();
  void move_npcs();
  void print_map();
  void Attach(AbstractObserver *observer);
  void Detach(AbstractObserver *observer);
  void Notify(const string &msg);

  friend std::ostream& operator<<(std::ostream &os, const Editor &ed); 
};


class AbstractObserver {
public:
  virtual ~AbstractObserver(){};
  virtual void Update(const std::string &msg) = 0;
};


class StdoutObserver : public AbstractObserver {
private:
  Editor &ed_;
  inline static int static_number_=0;
  int number_;

public:
  StdoutObserver(Editor &ed) : ed_(ed) {
    this->ed_.Attach(this);
    StdoutObserver::static_number_++; 
    // std::cout << "Hi, I'm the Observer \"" << StdoutObserver::static_number_ << "\".\n";
    this->number_ = StdoutObserver::static_number_;
  }

  virtual ~StdoutObserver() {
    // std::cout << "Goodbye, I was the StdoutObserver \"" << this->number_ << "\".\n";
  }

  void Update(const std::string &msg) override {
    print(msg, '\n');
  }

  void RemoveMeFromTheList() {
    ed_.Detach(this);
    // std::cout << "StdoutObserver \"" << number_ << "\" removed from the list.\n";
  }
};


class LogObserver : public AbstractObserver {
private:
  Editor &ed_;
  inline static int static_number_=0;
  int number_;
  std::ofstream log_stream_;

public:
  LogObserver(Editor &ed, const std::string &path) : ed_(ed) {
    this->ed_.Attach(this);
    LogObserver::static_number_++;
    this->number_ = LogObserver::static_number_;
    log_stream_ = std::ofstream(path);
    if (!log_stream_.is_open())
      throw std::invalid_argument(path + " - no such file");
  }

  virtual ~LogObserver() {}

  void Update(const std::string &msg) override {
    log_stream_ << msg << std::endl;
  }

  void RemoveMeFromTheList() {
    ed_.Detach(this);
  }
};
