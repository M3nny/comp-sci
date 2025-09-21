#include <iostream>
#include <vector>

using namespace std;

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

/*
l'invariante è la soglia, dove alla sua sinistra abbiamo l'array ordinato e alla sua destra l'array disordinato
man mano la soglia si sposta verso destra finchè non rimangono più elementi disordinati.
*/
void bubble(vector<int>& v) {
    for (int soglia = 0; soglia <= v.size(); soglia++) {
        for (int i = v.size() - 1; i > soglia; i--) {
            if (v.at(i) < v.at(i - 1)) {
                swap(v.at(i), v.at(i - 1));
            }
        }
    }
}

void print_vector(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v.at(i);
    }
    cout << "\n";
}

int main() {
    vector<int> v;
    v.push_back(3);
    v.push_back(1);
    v.push_back(2);
    
    print_vector(v);
    bubble(v);
    print_vector(v);

    return 0;
}
