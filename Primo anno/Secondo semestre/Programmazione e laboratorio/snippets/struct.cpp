#include <iostream>

using namespace std;

struct copia {
    int x;
    int y;
    int sum () {
        return x + y;
    }
};

int main () {
    copia c, c1;

    c.x = 4;
    c.y = 6;
    c1.x = 23;
    c1.y = 27;

    cout << c.sum(); // 10
    cout << c1.sum(); // 50
}
