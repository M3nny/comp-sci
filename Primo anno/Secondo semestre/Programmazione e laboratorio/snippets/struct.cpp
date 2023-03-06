#include <iostream>

using namespace std;

struct somma_struct { // default pubblica
    int x;
    int y;
    int sum() {
        return x + y;
    }
};

class somma_class { // default privata
    int x;
    int y;
    public:
        int get_x() {
            return x;
        }
        int get_y() {
            return y;
        }
        void set_xy(int x, int y) {
            this -> x = x; // this indica che sto usando le variabili interne all'oggetto
            this -> y = y;
        }
        int sum() {
            return x + y;
        }
};

int main () {
    somma_struct a, b;

    a.x = 4;
    a.y = 6;
    b.x = 23;
    b.y = 27;

    cout << "--- struct ---" << endl;
    cout << "somma struct: " << a.sum() << endl; // 10
    cout << "somma struct: " << b.sum() << endl; // 50

// -------------------------------

    somma_class s;
    s.set_xy(3, 2);

    cout << "--- class ---" << endl;
    cout << "x: " << s.get_x() << " y: " << s.get_y() << endl;
    cout << "somma classe: " << s.sum() << endl;
}
