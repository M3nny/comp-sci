#include <iostream>

class List_int {
public:
    List_int();
    List_int(const List_int& s);
    ~List_int();
    void append(int e); // sapere bene
    void prepend(int e); // sapere bene
    bool is_empty() const;
    int& head(); // una soluzione è scrivere nella documentazione che non deve essere empty, un'altra è lanciare except
    const int& head() const; // posso solo leggere
    void print() const;
    int size() const;
    int elimina_fondo(int n);
    void ribalta();
private:
    struct cell {
        int info;
        cell* next;
    };
    typedef cell* pcella;
    pcella h;
    void append_ric(pcella& testa, int e);
    void print_ric(pcella testa) const;
    int elimina_fondo_ric(pcella& list, int n);
    void ribalta_ric(pcella& p);
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

void List_int::append(int e) { // funzione cappello, imposta i parametri iniziali per un'altra funzione ricorsiva
    append_ric(h, e);
}

void List_int::append_ric(pcella& testa, int e) {
    if (testa == nullptr) {
        testa = new cell;
        testa->info = e;
        testa->next = nullptr;
    } else {
        append_ric(testa->next, e); // testa->next passato per reference
    }
}



void List_int::prepend(int e) {
    cell* nuova = new cell;
    nuova->info = e;
    nuova->next = h;
    h = nuova;
}

bool List_int::is_empty() const {
    return (h == nullptr);
}

int& List_int::head() { // può essere scritto quello che ritorno
    return h->info;
}

const int& List_int::head() const { // ouò essere letto ma non scritto quello che ritorno
    return h->info;
}

void List_int::print() const { // anche questa è una funzione cappello
    print_ric(h);
}

void List_int::print_ric(pcella testa) const {
    if (testa != nullptr) {
        std::cout << testa->info;
        print_ric(testa->next);
    }
}

int List_int::size() const {
    int res = 0;
    pcella p = h;
    while (p != nullptr) {
        res++;
        p = p->next;
    }
    return res;
}

int List_int::elimina_fondo(int n) {
    return elimina_fondo_ric(h, n);
}

int List_int::elimina_fondo_ric(pcella& list, int n) {
    if (list == nullptr) {
        return 0;
    } else {
        int cancellati = elimina_fondo_ric(list->next, n);
        if (cancellati < n) {
            delete list; // delete non mette a null il puntatore, lo bisogna mettere manualmente
            list = nullptr;
            return cancellati + 1;
        } else {
            return n;
        }
    }
}

void List_int::ribalta() {
    ribalta_ric(h);
}

void List_int::ribalta_ric(pcella& p) {
    if (p != nullptr && p->next != nullptr) {
        pcella supp = p->next;
        ribalta_ric(supp);
        p->next->next = p;
        p->next = nullptr;
        p = supp;
    }
}

int main () {
    List_int x;
    x.prepend(7);
    x.head() = 15;
}
