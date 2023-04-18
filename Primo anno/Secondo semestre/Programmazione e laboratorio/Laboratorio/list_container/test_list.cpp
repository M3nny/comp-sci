#include <iostream>
#include "list.hpp"
#include "list.cpp"

int main() {
    list<double> l1;
    read_list<double>(l1);

    list<double> l2;
    read_list<double>(l2);

    std::cout << "liste uguali? " << (l1 == l2);
    std::cout << l1 << std::endl;

    l1.push_back(6);
    std::cout << l1 << std::endl;

    l1.push_front(0);
    std::cout << l1 << std::endl;

    l1.pop_front();
    std::cout << l1 << std::endl;

    l1--;
    std::cout << l1 << std::endl;

    --l1;
    std::cout << l1 << std::endl;


    return 0;
}
