#### Liste vs Vector
Uso le liste se voglio eseguire spesso operazioni di aggiunta di elementi in testa o in coda, mentre il vector se accederò più spesso agli elementi centrali (accesso diretto con vector), ma un vector sarebbe scomodo per aggiungere elementi in testa in quanto dovrebbe eseguire uno shift di tutti gli elementi di una posizione.

## Singly linked list
Si tratta di una struttura dati contenente:
- Dato
- Puntatore al prossimo elemento

Può essere anche **circolare** se trattata come tale, l'implementazione della struttura dati comunque non cambierebbe.
```cpp
class List_int {
public:
    List_int();
    List_int(const List_int& s);
    ~List_int();
    void append(int e);
    void prepend(int e);
private:
    struct cell {
        int info;
        cell* next;
    };
    typedef cell* pcella;
    pcella h;
    void append_ric(pcella& testa, int e);
};

List_int::List_int() { // Default constructor
    h = nullptr; // lista vuota
}

List_int::List_int(const List_int& s) { // Copy constructor
    cell* pc = s.h;
    h = nullptr;
    while (pc != nullptr) {
        append(pc->info);
        pc = pc->next;
    }
}

List_int::~List_int() { // Distruttore
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

// funzione cappello, imposta i parametri iniziali per un'altra funzione
void List_int::append(int e) {
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
```

## Doubly linked list
Questa struttura dati contiene
- Puntatore all'elemento precedente
- Dato
- Puntatore all'elemento successivo

In questo modo è più facile fare una append dato che avrò anche un puntatore all'ultimo elemento oltre che al primo.
```cpp
class ListDL {
public:
    ListDL();
    ListDL(const ListDL& s);
    ~ListDL();
    void append(int e);
private:
    struct cella {
        int info;
        cella* next;
        cella* prev;
    };
    typedef cella* pcella;
    pcella head, tail;
};

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
```
