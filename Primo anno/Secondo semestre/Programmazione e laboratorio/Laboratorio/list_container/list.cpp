#include "list.hpp"

template<typename Val>
list<Val>::list() : m_front(nullptr), m_back(nullptr) {}

template<typename Val>
list<Val>::~list() {
    while (not empty()) pop_front();
}

template<typename Val>
list<Val>::list(Val v) : list() { // chiama il costruttore di default prima di eseguire questa funzione
    push_front(v);
}

template<typename Val>
typename list<Val>::node const* list<Val>::front() const { // ogni volta che si ritorna un template si mette typename d'avanti
    return m_front;
}

template<typename Val>
typename list<Val>::node const* list<Val>::back() const {
    return m_back;
}

template<typename Val>
void list<Val>::push_front(Val v) {
    if (empty()) {
        m_front = m_back = new node {v, nullptr};
        return;
    }
    m_front = new node {v, m_front};
}

template<typename Val>
void list<Val>::push_back(Val v) {
    if (empty()) {
        push_front(v);
        return;
    }
    m_back->next = new node {v, nullptr};
    m_back = m_back->next;
}

template<typename Val>
bool list<Val>::empty() const {
    return m_front == nullptr;
}

template<typename Val>
void list<Val>::pop_front() {
    if (not empty()) {
        node* tmp = m_front;
        m_front = m_front->next;
        delete tmp;

        if (m_front == nullptr) m_back = nullptr;
    }
}
