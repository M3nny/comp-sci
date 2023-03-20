#include <iostream>

class List_int {
public:
    List_int();
    List_int(const List_int& s);
    ~List_int();
    void append(int e);
    void prepend(int e);
    bool is_empty() const;
    int& head();
    const int& head() const; // per evitare promesse da marinaio arrrrg (posso solo leggere)
    void print() const;
private:
    struct cell {
        int info;
        cell* next;
    };
    cell* h;
};

List_int::List_int() {
    h = nullptr; // lista vuota
}

List_int::List_int(const List_int& s) {
    cell* pc = s.h;
    h = nullptr;
    while (pc != nullptr) {
        append(pc->info);
        pc = pc->next;
    }
}

List_int::~List_int() {
    cell* pc = h;
    while (pc != nullptr) {
        h = h->next;
        delete pc;
        pc = h;
    }
}

void List_int::prepend(int e) {
    cell* nuova = new cell;
    nuova->info = e;
    nuova->next = h;
    h = nuova;
}
