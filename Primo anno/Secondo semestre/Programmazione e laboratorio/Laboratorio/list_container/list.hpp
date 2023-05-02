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
    struct iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Val;
        using pointer = Val*;
        using reference = Val&;
        iterator(node*); // costruttore (serve a begin() e end())
        reference operator*() const; // *it
        pointer operator->() const; // e.g. per pair si può accedere con it->first, it->second
        iterator& operator++(); // ++it
        iterator operator++(int); // it++
        bool operator==(iterator const&) const; // it1 == it2
        bool operator!=(iterator const&) const; // it1 != it2
        operator bool() const; // viene fatto un cast implicito da iterator a booleano e.g. if(it) 
    private:
        node* m_ptr;
    };

    iterator begin(); // ritorna un nuovo iterator alla prima cella della lista
    iterator end(); // ritorna un nuovo iterator alla cella dopo l'ultima contenente l'ultimo valore

    struct const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = const Val;
        using pointer = const Val*;
        using reference = const Val&;
        const_iterator(node*); // costruttore (serve a begin() e end())
        reference operator*() const; // *it
        pointer operator->() const; // e.g. per pair si può accedere con it->first, it->second
        const_iterator& operator++(); // ++it
        const_iterator operator++(int); // it++
        bool operator==(const_iterator const&) const; // it1 == it2
        bool operator!=(const_iterator const&) const; // it1 != it2
        operator bool() const; // viene fatto un cast implicito da iterator a booleano e.g. if(it) 
    private:
        node* m_ptr;
    };

    const_iterator begin() const; // ritorna un nuovo const_iterator alla prima cella della lista
    const_iterator end() const; // ritorna un nuovo const_iterator alla cella dopo l'ultima contenente l'ultimo valore

    list(); // default constructor
    list(list<Val> const&); // copy constructor
    list(list<Val>&&); // move constructor
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
    list<Val>& operator=(list<Val>&&); // move assignment
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
