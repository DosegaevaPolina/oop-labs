#include "five.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>


// Конструкторы

Five::Five() {
  size = 0;
  digits = new unsigned char[0];
}


Five::~Five() noexcept {
  delete[] digits;
}


void Five::check_digit_and_throw(unsigned char d) {
  if ('0' <= d && d <= '4') return;
  stringstream what_stream;
  what_stream << "Your symbol (" << d << ") is not in five-digit number system!";
  delete[] digits;
  throw invalid_argument(what_stream.str());
}


Five::Five(const size_t &n, unsigned char d) {
  if (d == 0) d = '0';
  if (d == '0') {
    size = 1;
    digits = new unsigned char[1];
    digits[0] = d;
    return;
  }
  size = n;
  digits = new unsigned char[size];
  check_digit_and_throw(d);
  fill_n(digits, size, d);
}


Five::Five(const initializer_list<unsigned char> &il) {
  size = il.size();
  digits = new unsigned char[size];

  size_t pos = 0;
  for (auto it = crbegin(il); it != crend(il); ++it, ++pos) {
    check_digit_and_throw(*it);
    digits[pos] = *it;
  }

  // убираем лидирующие нули
  size_t newsize = count_significants();
  if (newsize != size) {
    size = newsize;
    resize(newsize);
  }
}


Five::Five(const string &s) {
  size = s.size();
  digits = new unsigned char[size];
  
  size_t pos = 0;
  for (auto it = crbegin(s); it != crend(s); ++it, ++pos) {
    check_digit_and_throw(*it);
    digits[pos] = *it;
  }

  // убираем лидирующие нули
  size_t newsize = count_significants();
  if (newsize != size) {
    size = newsize;
    resize(newsize);
  }
}


Five::Five(const Five &o) {
  size = o.size;
  digits = new unsigned char[size];

  copy(o.digits, o.digits + o.size, digits);
}

// move-конструктор
Five::Five(Five &&o) {
  size = o.size;
  digits = o.digits;

  o.digits = new unsigned char[0];
  o.size = 0;
}


string Five::to_string() const {
  string res = "";
  if (size == 0) return res;
  for (ssize_t i = size-1; i >= 0; --i)
    res += digits[i];
  return res;
}


ostream& operator<<(std::ostream& os, const Five& f) {
  return os << f.to_string();
}


size_t Five::get_size() const {
  return size;
}


Five::operator unsigned long int() const {
  unsigned long n = 0;
  unsigned long base = 1;
  for (size_t i = 0; i < size; ++i) {
    n += base * (digits[i] - '0');
    base *= 5;
  }
  return n;
}

// Арифметические операции

Five& Five::operator=(const Five &o) {
  // Guard self assignment
  if (this == &o)
    return *this;

  if (size != o.size) {
    auto temp = new unsigned char[o.size];   // allocate resource, if throws, do nothing
    delete[] digits; 
    digits = temp;
    size = o.size;
  } 

  copy(o.digits, o.digits + o.size, digits);
  return *this;
}

// move assignment
Five& Five::operator=(Five &&o) {
  if (this == &o) 
    return *this;

  delete[] digits;
  digits = o.digits;
  size = o.size;

  o.digits = new unsigned char[0];
  o.size = 0;

  return *this;
}


int Five::get_digit(size_t index) const {
  if (index + 1 > size) return 0;
  return digits[index] - '0';
}


void Five::resize(size_t newsize) {
  auto resized = new unsigned char[newsize]{};
  copy(digits, digits + min(size,newsize), resized);
  delete[] digits;
  digits = resized;
  size = newsize;
}


Five Five::operator+(const Five &o) {
  Five res;
  res.resize(max(size, o.size));

  int rem = 0;
  for (size_t i = 0; i < res.size; ++i) {
    int d1 =   get_digit(i);
    int d2 = o.get_digit(i);
    int sum = d1 + d2 + rem;
    res.digits[i] = sum % 5 + '0';
    rem = sum / 5;
  }

  if (rem != 0) {
    res.resize(res.size + 1);
    res.digits[res.size - 1] = rem + '0';
  }

  return res;
}


size_t Five::count_significants() const {
  if (size == 0) return 0;
  for (ssize_t i=size-1; i >= 0; --i)
    if (digits[i] != '0')
      return i+1;
  return 1;  // digits == {'0'}
}


Five Five::operator-(const Five &o) {
  if (size == 0)
    throw invalid_argument("Object is not initialized!");
  if (o.size > size)
    throw std::invalid_argument("The result will be negative!");

  Five res(*this);
  bool carry = false;
  for (size_t i = 0; i < res.size; ++i) {
    res.digits[i] = get_digit(i) - o.get_digit(i) + '0';
    if (carry) res.digits[i] -= 1;
    carry = res.digits[i] < '0';
    if (carry) res.digits[i] += 5;
  }
  if (carry)
    throw std::invalid_argument("The result will be negative!");

  size_t newsize = res.count_significants();
  res.resize(newsize);

  return res;
}


// Операции сравнения

bool Five::operator==(const Five &o) {
  if (size != o.size) return false;

  for (size_t i = 0; i < size; ++i)
    if (digits[i] != o.digits[i])
      return false;
  return true;
}


bool Five::operator<(const Five &o) {
  if (size != o.size)
    return size < o.size;

  for (ssize_t i = size-1; i >= 0; --i)
    if (digits[i] != o.digits[i])
      return digits[i] < o.digits[i];
  return false;
}


bool Five::operator>(const Five &o) {
  if (size != o.size)
    return size > o.size;

  for (ssize_t i = size-1; i >= 0; --i)
    if (digits[i] != o.digits[i])
      return digits[i] > o.digits[i];
  return false;
}

