#include <iostream>

#include "devowel.h"

using namespace std;

int main() {
    string s;
    getline(cin, s);
    cout << devowel(s) << endl;
    return 0;
}
