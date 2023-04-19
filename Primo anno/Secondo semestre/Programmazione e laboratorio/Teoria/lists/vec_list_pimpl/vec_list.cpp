#include <iostream>
#include <vector>
#include "vec_list.hpp"

#define MAXE 10 // numero di elementi

struct ListDL::impl {
    std::vector<int> v;
    int head, tail, free;
};

ListDL::ListDL() {
    pimpl = new impl; // in idioma pimpl, la prima operazione da fare è quella di istanziare new impl
    pimpl->v.resize(10*3);
    pimpl->head = pimpl->tail = -1;
    pimpl->free = 0;

    // non serve mettere il puntatore all'elemento precedente in quelli vuoti in quanto verrà rimosso il primo indicato da free e basta (successivamente)
    for (int i = 0; i < MAXE; i++) { // costruisco la catena di blocchi vuoti
        pimpl->v.at(i*3+2) = (i+1)*3;
    }
    pimpl->v.at((MAXE-1)*3+2) = -1;
}

// sarebbe sbagliato fare un semplice pimpl = s.pimpl; perchè punterebbero alla stessa area di memoria, quando uno muore, muore anche l'altro
ListDL::ListDL(const ListDL& s) {
    pimpl = new impl;
    pimpl->v = s.pimpl->v;
    pimpl->head = s.pimpl->head;
    pimpl->tail = s.pimpl->tail;
    pimpl->free = s.pimpl->free;
}

ListDL::~ListDL() {
    delete pimpl;
}

void ListDL::prepend(int e) {
    if (pimpl->free != -1) { // ci sono blocchi liberi
        int nuovo = pimpl->free;
        pimpl->free = pimpl->v.at(pimpl->free+2);
        pimpl->v.at(nuovo) = -1;
        pimpl->v.at(nuovo+1) = e;
        pimpl->v.at(nuovo+2) = pimpl->head;

        if (pimpl->head != -1) { // ho almeno un elemento
            pimpl->v.at(pimpl->head) = nuovo;
        }

        pimpl->head = nuovo;

        if (pimpl->tail == -1) { // aggiorno tail se ho la lista vuota
            pimpl->tail = nuovo;
        }
    } // non si può inserire se non ci sono blocchi vuoti
}

void ListDL::append(int e) {
    if (pimpl->free != -1) { // ci sono blocchi liberi
        int nuovo = pimpl->free;
        pimpl->free = pimpl->v.at(pimpl->free+2);
        pimpl->v.at(nuovo) = pimpl->tail;
        pimpl->v.at(nuovo+1) = e;
        pimpl->v.at(nuovo+2) = -1;

        if (pimpl->tail != -1) { // ho almeno un elemento
            pimpl->v.at(pimpl->tail+2) = nuovo;
        }

        pimpl->tail = nuovo;

        if (pimpl->head == -1) { // aggiorno head se ho la lista vuota
            pimpl->head = nuovo;
        }
    } // non si può inserire se non ci sono blocchi vuoti
}

void ListDL::print() const {
    std::cout << "Head: " << pimpl->head << ", ";
    std::cout << "Tail: " << pimpl->tail << ", ";
    std::cout << "Free: " << pimpl->free << std::endl;

    for (int i = 0; i < MAXE; i++) {
        std::cout << i*3 << ": ";
        std::cout << "[" << pimpl->v.at(i*3) << ", " << pimpl->v.at(i*3+1) << ", " << pimpl->v.at(i*3+2) << "]" << std::endl;
    }
    std::cout << std::endl;
}

int& ListDL::at(int pos) {
    int pc = pimpl->head;

    while ( pc != -1 && pos > 0) {
        pc = pimpl->v.at(pc+2);
        pos--;
    }

    if (pc != -1)
        return pimpl->v.at(pc+1);
    else
        return pimpl->v.at(MAXE*3);
}


const ListDL& ListDL::operator=(const ListDL& l) {
    if (this != &l) { // controllo per autoassegnamento
        pimpl->v = l.pimpl->v;
        pimpl->head = l.pimpl->head;
        pimpl->tail = l.pimpl->tail;
        pimpl->free = l.pimpl->free;
    }
    return *this;
}

// return (*pimpl == *l.pimpl) sarebbe sbagliato perchè per noi gli elementi hanno posizione arbitraria
// una lista potrebbe essere uguale anche se gli elementi sono posizionati in modo diverso
bool ListDL::operator==(const ListDL& l) const {
    bool res = true;

    int pc1 = pimpl->head;
    int pc2 = l.pimpl->head;

    while (pc1 != -1 && pc2 != -1 && res) {
        if (pimpl->v.at(pc1+1) != l.pimpl->v.at(pc2+1)) {
            res = false;
        } else {
            pc1 = pimpl->v.at(pc1+2);
            pc2 = l.pimpl->v.at(pc2+2);
        }
    }
    return (pc1 == -1 && pc2 == -1);
}

ListDL ListDL::operator+(const ListDL& l) {
    ListDL res = *this;
    int pc2 = l.pimpl->head;

    while (pc2 != -1) {
        append(l.pimpl->v.at(pc2+1));
        pc2 = l.pimpl->v.at(pc2+2);
    }
    return res;
}

int main() {
    ListDL l;
    l.print();

    l.prepend(10);
    l.prepend(20);
    l.prepend(30);
    l.print();

    l.at(1) = 200;
    l.print();

    l.append(40);
    l.print();

    return 0;
}
