#include <iostream>
#include "list.hpp"
#include "list.cpp"

list<double> f() {
    list<double> x;
    return x;
}

int main() {
    // list<double> l1;
    // read_list<double>(l1);
    //
    // list<double> l2;
    // read_list<double>(l2);
    //
    // std::cout << "liste uguali? " << (l1 == l2);
    // std::cout << l1 << std::endl;
    //
    // l1.push_back(6);
    // std::cout << l1 << std::endl;
    //
    // l1.push_front(0);
    // std::cout << l1 << std::endl;
    //
    // l1.pop_front();
    // std::cout << l1 << std::endl;
    //
    // l1--;
    // std::cout << l1 << std::endl;
    //
    // --l1;
    // std::cout << l1 << std::endl;

    // ---

    list<double> x1;
    x1 += 5;
    x1 += 6.2;
    list<double> x2 = x1; // copy constructor
    list<double> x3 = f(); // copy elision

    std::pair<list<double>, int> p = {f(), 0}; // move constructor
    std::pair<list<double>, int> p2;
    p2 = {f(), 0}; // move assignment

    return 0;
}
