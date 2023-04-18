#pragma once // importa solo una volta questo file
// container list<val>

#include <iostream>

template<typename Val>
class list {
    struct node {
        Val val;
        node* next;
    };
public:
    list(); // default constructor
    list(list<Val> const&); // copy constructor
    ~list(); // distruttore
    list(Val v); // lista di un elemento
    node const* front() const; // puntatore alla prima cella
    node const* back() const; // puntatore all'ultima cella

    void push_front(Val v); // aggiunge un elemento all'inizio della lista
    void push_back(Val v); // aggiunge un elemento alla fine della lista

    void pop_front(); // rimuove il primo elemento
    void pop_back(); // rimuove l'ultimo elemnto

    bool empty() const; // vero se la lista è vuota

    list<Val>& operator=(list<Val> const&); // l1 = (l2 = l3)
    bool operator==(list<Val> const& rhs) const; // controlla se *this è uguale a rhs, rispettivamente (l1 == l2)
    bool operator!=(list<Val> const& rhs) const; // controlla se *this è diverso da rhs, rispettivamente (l1 != l2)
    list<Val>& operator+=(list<Val> const& rhs); // l1 += l2
    list<Val>& operator+=(Val const& rhs); // l1 += 3

    // chiamato con Val const& x = l1[3];
    // c'è la versione const perchè e.g. nell'peratore == prometto che userò solo funzioni const, non poss quindi usare [] non const
    Val const& operator[](uint64_t i) const; // accede alla cella i-esima l1[3] e ritorna una const reference (non posso fare l1[3] = 4)
    // chiamato con Val& x = l1[3];
    Val& operator[](uint64_t i); // accede alla cella i-esima l1[3] e ritorna una reference (posso fare l1[3] = 4)
    list<Val>& operator--(); // --l1; rimuove il primo elemento con pop_front()
    list<Val>& operator--(int); // l1--; (si differenzia con un dummy argument) rimuove l'ultimo elemento usando pop_back()
private:
    node* m_front; // puntatore all'inizio
    node* m_back; // puntatore alla fine
};
