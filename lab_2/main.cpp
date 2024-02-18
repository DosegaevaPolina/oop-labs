#include "five.hpp"

#include <iostream>

using namespace std;

int main() {
  cout << Five(4, '1') << endl;
  cout << Five({'2', '1', '0'}) << endl << endl;
  cout << Five("4321") << endl << endl;

  Five f0 = Five("123");
  Five f1 = f0;
  cout << f1 << endl << endl;

  Five f2 = std::move(f1);
  cout << f2 << endl << endl;

  Five f3;
  f3 = f2;
  cout << f3 << endl << endl;

  cout << Five("44") + Five("401") << endl;
  cout << Five("1000") - Five("401") << endl;

  cout << (Five("12") == Five("12")) << endl << endl;
  cout << (Five("123") < Five("124")) << endl << endl;
  cout << (Five("12") > Five("1")) << endl << endl;
}
