#include "list.hpp"

// --- start iterator ---
template<typename Val>
list<Val>::iterator::iterator(node* p) : m_ptr(p) {}

template<typename Val>
// la firma è lunga, la spezzo in due righe
typename list<Val>::iterator::reference
list<Val>::iterator::operator*() const { // restituisce reference al Val contenuto nella cella puntata da m_ptr
    return m_ptr->val;
}

template<typename Val>
// su list<int> l'operator non viene usato perchè è un tipo primitivo, avrebbe più senso con pair
typename list<Val>::iterator::pointer
list<Val>::iterator::operator->() const { // restituisce un puntatore al Val contenuto nella cella puntata da m_ptr
    return &(m_ptr->val);
}

template<typename Val>
typename list<Val>::iterator& list<Val>::iterator::operator++() { // incrementa it e lo restituisce
    m_ptr = m_ptr->next;
    return *this;
}

template<typename Val>
typename list<Val>::iterator list<Val>::iterator::operator++(int) { // restituisce it e lo incrementa
    iterator it = {m_ptr}; // posso usare anche iterator it = iterator(m_ptr), esenzialmente sto chiamando il costruttore
    ++(*this); // uso l'operatore definito precedentemente
    return it;
}

template<typename Val>
bool list<Val>::iterator::operator==(typename list<Val>::iterator const& rhs) const {
    // true solo se it1 e it2 puntano alla stessa area di memoria
    return m_ptr == rhs.m_ptr;
}

template<typename Val>
bool list<Val>::iterator::operator!=(typename list<Val>::iterator const& rhs) const {
    // true solo se it1 e it2 non puntano alla stessa area di memoria
    return m_ptr != rhs.m_ptr;
}

template<typename Val>
list<Val>::iterator::operator bool() const {
    // true sse l'iteratore punta ad una cella
    // false se punta a nullptr
    // può anche essere return m_ptr;
    return m_ptr != nullptr;
}

template<typename Val>
typename list<Val>::iterator list<Val>::begin() {
    // è possibile scrivere anche return {m_ptr};
    return iterator{m_front}; // chiamo il costruttore e inizializzo
}

template<typename Val>
typename list<Val>::iterator list<Val>::end() {
    return iterator{nullptr}; // nel nostro caso la cella dopo l'ultima è sempre nullptr
}
// --- end iterator ---

template<typename Val>
list<Val>::list() : m_front(nullptr), m_back(nullptr) {}

template<typename Val>
list<Val>::list(Val v) : list() { // chiama il costruttore di default prima di eseguire questa funzione
    push_front(v);
}

// list<Val> l1 {l2};
// list<Val> l1 = l2;
// list<Val> l1 (l2);
template<typename Val>
list<Val>::list(list<Val> const& rhs) : list() { // chiamo il default constructor
    std::cout << "copy constructor" << std::endl;
    *this = rhs; // copy assignment
}

template<typename Val>
list<Val>::list(list<Val>&& rhs) : list() {
    std::cout << "move constructor" << std::endl;
    *this = std::move(rhs); // move assigment
}

template<typename Val>
list<Val>::~list() {
    while (not empty()) pop_front();
}

template<typename Val>
typename list<Val>::node const* list<Val>::front() const { // ogni volta che si ritorna un template si mette typename d'avanti
    return m_front;
}

template<typename Val>
typename list<Val>::node const* list<Val>::back() const {
    return m_back;
}

template <typename Val>
void read_list(list<Val>& list) {
    uint64_t list_size = 0;
    Val v;
    std::cin >> list_size;                       // fa inserire la lunghezza della lista da input
    for (uint64_t i = 0; i != list_size; ++i) {  // fa inserire elemento per elemento da input
        std::cin >> v;
        list.push_back(v);
    }
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

template<typename Val>
void list<Val>::pop_back() {
    if (m_front == m_back) {
        pop_front();
        return;
    }

    node* ptr = m_front;
    while (ptr->next != m_back) { // ptr sarà il puntatore al penultimo elemento
        ptr = ptr->next;
    }

    delete m_back;
    m_back = ptr;
    ptr->next = nullptr;
}

template<typename Val>
list<Val>& list<Val>::operator=(list<Val> const& rhs) {
    std::cout << "copy assignment" << std::endl;
    if (this != &rhs) { // se i due oggetti sono diversi (altrimenti sono nel caso l1 = l1 che sono nella stessa area di memoria)
        while (not empty()) pop_front(); // mai chiamare esplicitamente il distruttore, perchè elimina l'oggetto in se
        *this += rhs;
    }
    return *this;
}

template<typename Val>
list<Val>& list<Val>::operator=(list<Val>&& rhs) {
    std::cout << "move assignment" << std::endl;
    if (this != &rhs) {
        while(not empty()) pop_front();
        m_front = rhs.m_front;
        m_back = rhs.m_back;
        rhs.m_front = rhs.m_back = nullptr;
    }
    return *this;
}

template<typename Val>
bool list<Val>::operator==(list<Val> const& rhs) const {
    auto ptr1 = front();
    auto ptr2 = rhs.front();
    while (ptr1 or ptr2) {
        if ((ptr1 and !ptr2) or (!ptr1 and ptr2) or (ptr1->val != ptr2->val)) {
            return false;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    return true;
}

template<typename Val>
bool list<Val>::operator!=(list<Val> const& rhs) const {
    return !(*this == rhs);
}

// l1: 1,2,3
// l2: 4,5
// l1 += l1 = 1,2,3,4,5
template<typename Val>
list<Val>& list<Val>::operator+=(list<Val> const& rhs) {
    auto ptr = rhs.front();
    while (ptr) {
        push_back(ptr->val);
        ptr = ptr->next;
    }
    return *this;
}

// aggiungo un elemento alla fine della lista
template<typename Val>
list<Val>& list<Val>::operator+=(Val const& rhs) {
    push_back(rhs);
    return *this;
}

template<typename Val>
Val const& list<Val>::operator[](uint64_t i) const{ // per sua natura non è safe, se facciamo l1[x] dove x è fuori, da errore
    uint64_t pos = 0;
    auto ptr = front();
    while (pos++ < i) {
        ptr = ptr->next;
    }
    return ptr->val;
}

template<typename Val>
Val& list<Val>::operator[](uint64_t i) { // è una ridondanza, ma serve
    uint64_t pos = 0;
    auto ptr = front();
    while (pos++ < i) {
        ptr = ptr->next;
    }
    return ptr->val;
}

// --l1
template<typename Val>
list<Val>& list<Val>::operator--() {
    pop_front();
    return *this;
}

// l1--
template<typename Val>
list<Val>& list<Val>::operator--(int) {
    pop_back();
    return *this;
}

template<typename Val>
std::ostream& operator<<(std::ostream& os, list<Val> const& list) {
    if (list.empty()) return os;
    for (auto ptr = list.front(); ptr != nullptr; ptr = ptr->next) { // il nome del tipo è nascosto ma con auto funziona perchè il compilatore lo conosce
        os << ptr->val;
        if (ptr->next) os << " -> ";
    }
    return os;
}
