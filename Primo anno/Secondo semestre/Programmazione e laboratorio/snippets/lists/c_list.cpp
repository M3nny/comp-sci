#include <iostream>

struct cella {
    int info;
    cella* next;
};

typedef cella* ListaCirc;

void print(ListaCirc l) {
    ListaCirc start = l;

    do {
        l = l->next;
        std::cout<< l->info;
    } while (l != start);
}
