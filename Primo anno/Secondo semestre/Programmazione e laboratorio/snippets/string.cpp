#include <iostream>
#include <string>
#include <vector>

using namespace std;

void foo(string s); // passaggio per copia
void foo(string& s); // passaggio per reference
void foo(const string& s); // leggo e basta con passaggio epr reference

void string_intro() {
    string s1, s2;
    cin >> s1;
    cin >> s2;

    if (s1 == s2) { // fa quello che ci aspettiamo
        cout << "Le stringhe sono uguali";
    }

    s1 = s2; // s1 ora è s2

    if (s1 > s2) {
        cout << "s1 viene prima di s2 nell'alfabeto";
    }

    string s3;
    s3 = s1 + s2; // concatena le stringhe
    s3 = s1 + "ciao";
}

bool palindroma(const string& s) {
    bool risp = true;
    int i = 0;

    while (i < s.length()/2 && risp) {
        if (s.at(i) != s.at(s.length() - i - 1)) {
            risp = false;
        }
        i++;
    }
    return risp;
}

// Dato un vettore di stringhe produrre la stringa che concatena le stringhe
string concatena(const vector<string>& vs) {
    string res;
    for (const auto& el:vs) {
        res += el;
    }
    return res;
}

int main () {
    vector<string> vs;
    string concatenata;

    vs.push_back("hello");
    vs.push_back("world");
    vs.push_back("c++");
    concatenata = concatena(vs);
}
