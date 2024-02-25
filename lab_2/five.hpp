#pragma once
#include <cstddef>
#include <string>

using namespace std;

class Five {
private:
  unsigned char *digits;
  size_t size;
  void check_digit_and_throw(unsigned char d);
  int get_digit(size_t index) const;
  void resize(size_t new_size);
  size_t count_significants() const;

public:
  Five();
  Five(const size_t &n, unsigned char d = 0);
  Five(const initializer_list<unsigned char> &il);
  Five(const string &s);
  Five(const Five &o);
  Five(Five &&o);
  virtual ~Five() noexcept;

  string to_string() const;
  size_t get_size() const;

  Five& operator=(const Five &o);
  Five& operator=(Five &&o);
  Five operator+(const Five &o);
  Five operator-(const Five &o);

  bool operator==(const Five &o);
  bool operator<(const Five &o);
  bool operator>(const Five &o);
};

ostream& operator<<(std::ostream& os, const Five& f);
