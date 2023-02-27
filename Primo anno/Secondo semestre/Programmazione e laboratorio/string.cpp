#include <iostream>
#include <string>

using namespace std;

void foo(string s); // passaggio per copia
void foo(string& s); // passaggio per reference
void foo(const string& s); // leggo e basta con passaggio epr reference

int main () {
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
