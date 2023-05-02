#include <iostream>
#include "list.hpp"
#include "list.cpp"

list<double> f() {
    list<double> x;
    return x;
}

int main() {
    // --- test list ---
    std::cout << "--- Test funzioni ---" << std::endl;
    list<double> l1;
    read_list<double>(l1);

    // list<double> l2;
    // read_list<double>(l2);
    // std::cout << "liste uguali? (0/1) " << (l1 == l2) << std::endl;

    l1.push_back(9);
    l1.push_front(0);
    std::cout << "Dopo push_back(9) e push_front(0):" << std::endl << l1 << std::endl;

    l1--;
    --l1;
    std::cout << "Dopo pop_back e pop_front:" << std::endl << l1 << std::endl;

    // --- test move constructor ---
    std::cout << "--- Test constructors/overloading: ---" << std::endl;
    l1 += 5;
    l1 += 6.2;
    list<double> l2 = l1; // copy constructor
    list<double> l3 = f(); // copy elision

    std::pair<list<double>, int> p = {f(), 0}; // move constructor
    std::pair<list<double>, int> p2;
    p2 = {f(), 0}; // move assignment

    // --- test iterators ---
    std::cout << "--- Test iteratori ---" << std::endl;
    std::cout << "Lista corrente: " << l1 << std::endl;

    std::cout << "Stampa usando gli iteratori: " << std::endl;
    for (auto it = l1.begin(); it != l1.end(); it++) {
        std::cout << *it << std::endl;
    }

    *l1.begin() = 9;

	std::cout << "Sintassi foreach (dopo aver modificato il primo elemento a 9): " << std::endl;
	for(auto e : l1) std::cout << e << std::endl;

	std::cout << "l1.begin() == l1.end()? (0/1): " << (l1.begin() == l1.end()) << std::endl;

	l1=l2;
	std::cout << "l1 == l2? (0/1): " << (l1 == l2) << std::endl;

	list<std::pair<int,int>> p3;
	p3 += std::pair<int,int> {1,2};
	p3 += std::pair<int,int> {3,4};
	auto ptr = p3.begin();
	ptr->first = 5;
	std::cout << "p3.begin().first = " << ptr->first << std::endl;

    return 0;
}
