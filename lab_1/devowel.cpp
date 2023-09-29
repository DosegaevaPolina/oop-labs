#include "devowel.h"

#include <set>

using std::set;

string devowel (string s) {
    string s1 = "";
    set <char> st{'e','u','i','o','a','E','U','I','O','A'};
    for (const auto &el : s) {
        if (st.find(el) == st.end()) {
            s1 += el;
        }
    }
    return s1;
}
