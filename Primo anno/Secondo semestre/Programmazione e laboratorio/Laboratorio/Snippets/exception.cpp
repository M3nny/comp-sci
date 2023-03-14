#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cerr;
using std::endl;

struct myerror {
    string msg;
};

int area (int a, int b) {
    if (a < 0 or b > 0) throw myerror{"arguments must be >= 0"};
    return a * b;
}

int main () {
    try {
        cout << area(-2, 5) <<endl;
    } catch (const myerror& e) {cerr << e.msg << endl;}

    return 0;
}
