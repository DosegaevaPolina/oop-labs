#include "five.hpp"

#include <iostream>
#include <sstream>

using namespace std;

int main() {
  string result_str = "result: ";
  
  try {
    string first, second;
    cout << "(first number)\n> ";
    cin >> first;
    Five num1 = Five(first);

    cout << "(second number)\n> ";
    cin >> second;
    Five num2 = Five(second);

    char op;
    cout << "(operation: +/-/>/</=)\n> ";
    cin >> op;


    switch (op) {
    case '+':
      result_str += (num1 + num2).to_string();
      break;

    case '-':
      result_str += (num1 - num2).to_string();
      break;

    case '>':
      result_str += num1 > num2 ? "True" : "False";
      break;

    case '<':
      result_str += num1 < num2 ? "True" : "False";
      break;

    case '=':
      result_str += num1 == num2 ? "True" : "False";
      break;

    default:
      result_str = "No such operation";
      break;
    }

    cout << result_str << endl;
  } catch (const invalid_argument &ex) {
    cout << "Invalid argument exception caught: " << ex.what() << endl;
  }

  return 0;
}

