#include <iostream>

using namespace std;

string bin(uint64_t n) {
    if (n == 0) return "0";
    if (n == 1) return "1";
    return bin(n/2) + (n%2 ? string{"1"} : string{"0"});
}

int main() {
    uint64_t n = 5;
    cout << bin(n) << endl;
}
