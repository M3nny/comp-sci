#include "list.hpp"
#include <vector>
#include <iostream>

struct List_int::impl {
    std::vector<int> v;
};

List_int::List_int() {
    pimpl = new impl;
}

List_int::List_int(const List_int& l) {
    pimpl = new impl;
    pimpl->v = l.pimpl->v; // deep copy del vector
}

List_int::~List_int() {
    delete pimpl;
}

void List_int::prepend(int el) {
    pimpl->v.resize(pimpl->v.size()+1);
    for (int i = pimpl->v.size()-1; i > 0; i--) {
        pimpl->v.at(i) = pimpl->v.at(i-1);
    }
    pimpl->v.at(0) = el;
}

void List_int::append(int el) {
    pimpl->v.push_back(el);
}

void List_int::stampa() const {
    for (auto e:pimpl->v) {
        std::cout << e << std::endl;
    }
}
