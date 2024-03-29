#pragma once

#include "npc.hpp"
#include "gtest/gtest_prod.h"
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <utility>
#include <list>


class AbstractObserver;

class Editor {
private:
  FRIEND_TEST(Editor, FromStream);
  std::map<std::string, NPC*> data;
  std::pair<int,int> x_range, y_range;
  std::list<AbstractObserver*> observer_list;
  AbstractObserver *stdout_observer, *log_observer;

  std::optional<NPC*> from_string(const string &serialized) const; 
  void from_stream(std::istream &in);

public:
  Editor(const string &path, const string &log_path);
  ~Editor();
  void add_npc(NPC *npc);
  friend std::ostream &operator<<(std::ostream &os, const Editor &ed);
  void dump(const string &path);
  void fight(unsigned range);
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
    std::cout << msg << std::endl;
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
