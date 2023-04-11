#include <iostream>
#include <cassert>

class ListDL {
public:
    ListDL();
    ListDL(const ListDL& s);
    ~ListDL();
    void append(int e);
    void print() const; // non modifica lo stato della classe
    int& at(int pos);
    bool operator== (const ListDL& l) const;

    /* ridefinire '=' crea problemi in quanto:
        * 1. assegnamenti in catena
        * 2. distruggere lo stato del oggeto che sto assegnando
        * 3. la distruzione dello stato non deve interrompere la valutazione dell'espressione a dx dell'assegnamento
    */
    const ListDL& operator= (const ListDL& l); // ritorno const ref. per efficienza
    ListDL operator+ (const ListDL& l) const; // concateno gli elementi di l1 con quelli di l2
    ListDL operator* (unsigned int n) const; // aggiunge in coda la lista ripetuta n volte

private:
    struct cella {
        int info;
        cella* next;
        cella* prev;
    };
    typedef cella* pcella;
    pcella head, tail;

    void copy(pcella h);
};

ListDL::ListDL() {
    head = nullptr;
    tail = nullptr;
}

ListDL::ListDL(const ListDL& s) {
    copy(s.head); // ci serve anche dopo
}

ListDL::~ListDL() {

}


void ListDL::copy(pcella h) {
    head = nullptr;
    while (h != nullptr) {
        append(h->info);
        h = h->next;
    }
}

// con tail il costo di una append è costante
void ListDL::append(int e) {
    pcella nuova = new cella;
    nuova->info = e;
    nuova->next = nullptr;
    nuova->prev = tail;
    if (tail != nullptr) {
        tail = nuova;
    } else {
        head = nuova;
    }
    tail = nuova;
}

void ListDL::print() const {
    pcella pc = head;
    while (head != nullptr) {
        std::cout << pc->info;
        pc = pc->next;
    }
    std::cout << std::endl;
}

int& ListDL::at(int pos) {
    if (pos >= 0) {
        pcella pc = head;
        while (pc != nullptr && pos > 0) {
            pc = pc->next;
            pos--;
        }
        assert(pc != nullptr);
        return pc->info;
    } else {
        pos = -pos -1;
        pcella pc = tail;
        while (pc != nullptr && pos > 0) {
            pc = pc->prev;
            pos--;
        }
        assert(pc != nullptr);
        return pc->info;
    }
}

bool ListDL::operator == (const ListDL& l) const {
    pcella pc1 = head;
    pcella pc2 = l.head;
    bool uguali = true;
    while (pc1 != nullptr && pc2 != nullptr && uguali) {
        if (pc1->info != pc2->info) {
            uguali = false;
        } else {
            pc1 = pc1->next;
            pc2 = pc2->next;
        }
    }
    return (pc1 == pc2);
}

const ListDL& ListDL::operator= (const ListDL& l) {
    if (this != &l) { // non sto auto-assegnando
        // distruzione dello stato
        pcella pc = head;
        while (pc != nullptr) {
            pc = pc->next;
            delete head;
            head = pc;
        }
        head = nullptr;
        tail = nullptr;

        pc = l.head;
        while (pc != nullptr) {
            append(pc->info);
            pc = pc->next;
        }
    }
    return *this;
}

ListDL ListDL::operator+ (const ListDL& l) const { // move semantics, quando sta per morire ris, sposta lo stato di ris nel nuovo oggetto
    ListDL ris;
    pcella pc = head;
    while (pc != nullptr) {
        ris.append(pc->info);
        pc = pc->next;
    }
    pc = l.head;
    while (pc != nullptr) {
        ris.append(pc->info);
        pc = pc->next;
    }
    return ris;
}

ListDL ListDL::operator* (unsigned int n) const {
    ListDL ris;
    for (int i = 0; i < n; i++) {
        pcella pc = head;
        while (pc != nullptr) {
            ris.append(pc->info);
            pc = pc->next;
        }
    }
    return ris;
}

int main () {
    // fix: segfault
    ListDL l1, l2;
    l1.append(5);
    l2.append(5);
    if (l1 == l2) {
        std::cout << "uguali" << std::endl;
    }

    l1 = l1 * 10; // overloaded *, 10 * l1 non va perchè ora * non è commutativo, l'overload va se a sx c'è ListDL e a dx un uint
}
