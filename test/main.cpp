#include <iostream>
#include <set>
using namespace std;

string devowel (string s) {
    string s1 = "";
    set <char> st{'e','u','i','o','a','E','U','I','O','A'};
    for (int i = 0; i < s.length(); ++i) {
        if (st.find(s[i]) == st.end()) {
            s1 += s[i];
        }
    }
    return s1;
}

int main() {
    string s;
    getline(cin, s);
    cout << devowel(s) << endl;
    return 0;
}
