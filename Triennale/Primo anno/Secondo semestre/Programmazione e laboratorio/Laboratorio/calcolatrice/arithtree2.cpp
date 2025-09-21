#include <iostream>
#include <cassert>

// consume an arithmetic tree from std::cin and return its result
double E() {
    // E -> (double) | (+EE) | (*EE)
    // e.g. (+(3.14)(2))
    char c  = 0;
    std::cin >> c; // eat '(' ---> "+(3.14)(2))"
    assert(c == '(');
    std::cin >> c; // eat a number or + or * now i know how to handle c

    double res = 0;

    if (c > '0' and c <= '9') {
        std::cin.putback(c); // i have already read c, i put it back and re-read it, but now i handle it
        std::cin >> res; // eat a double
    } else if (c == '+') {
        res = E() + E(); // eat EE
    } else if (c == '*'){
        res = E() * E(); // eat EE
    }

    std::cin >> c;
    assert(c == ')');
    return res;
}

int main () {
    std::cout << "Insert expression: " << std::endl;
    double result = E();
    std::cout << "Result = " << result << std::endl;
}
