#include<iostream>
#include<string>
#include "array.h"

using namespace std;

bool matchPattern(const string& str, const string& pattern) {
    int n = str.size(), m = pattern.size();
    int i = 0, j = 0, star = -1, match = 0;

    while (i < n) {
        if (j < m && (pattern[j] == '?' || pattern[j] == str[i])) {
            i++; j++;
        }
        else if (j < m && pattern[j] == '*') {
            star = j++;
            match = i;
        }
        else if (star != -1) {
            j = star + 1;
            i = ++match;
        }
        else {
            return false;
        }
    }
    while (j < m && pattern[j] == '*') j++;
    return j == m;
}

int main() {
    setlocale(LC_ALL, "Ru");
    Array sequences;
    init(sequences, 5);

    Array patterns;
    init(patterns, 5);
    cout << "¬ведите строку: ";
    string s;
    cin >> s;
    add(sequences, s);

    cout << "¬ведите шаблон: ";
    string pattern;
    cin >> pattern;

    for (int i = 0; i < length(sequences); i++) {
        string current = get(sequences, i);
        cout << current << " Ч ";
        if (matchPattern(current, pattern))
            cout << "соответствует шаблону " << endl;
        else
            cout << "не соответствует шаблону " << endl;
    }

    destroy(sequences);
    destroy(patterns);
    return 0;
}
