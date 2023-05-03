#include <iostream>

struct cell {
    int info;
    cell* next;
};
typedef cell* List;

/* data una lista decidere se è circolare o meno
 * 0 lsita vuota
 * 1 lista circolare
 * 2 lista lineare
*/
int is_circular(List l) { // List è un puntatore alla prima cella
    if (l == nullptr) {
        return 0;
    } else {
        List pc = l;
        do {
            l = l->next;
        } while (l != nullptr && l != pc);
        if (l == nullptr) {
            return 2;
        } else {
            return 1;
        }
    }
}

void print_linear(List l) {
    while (l) {
        std::cout << l->info << " - ";
        l = l->next;
    }
    std::cout << std::endl;
}
void print_circ(List l) {
    List pc = l;
    if (l) {
        do {
            std::cout << l->info << " - ";
            l = l->next;
        } while (l != pc);
        std::cout << std::endl;
    }
}
void print (List l) {
    if (is_circular(l) == 1) {
        print_circ(l);
    } else if (is_circular(l) == 2) {
        print_linear(l);
    } else return;
}


void insert_circolare(List& l, int k) { // passo per reference perchè se inserisco su lista vuota devo fare inserimento by reference
    List n = new cell;
    n->info = k;

    if (l != nullptr) {
        n->next = l->next;
        l->next = n;
    } else { // lista vuota
        n->next = n;
        l = n;
    }
}

// Una lista con cappio (noose) è una lista che inizialmente è lineare, ma ad un certo punto comincia a girare su se stessa
// per capire se ha una cappio, mando avanti 2 puntatori alla volta (achille (a) e tartaruga (t)), poi ogni volta
// faccio partire un "giudice" (g) dall'inizio della lista.
// Normalmente il giudice trova prima la tartaruga che è più indietro di achille, quando trova achille per la prima volta prima della tartaruga, significa che in quel punto c'è un cappio (complessità n^2)

bool has_noose(List l) {
    List a, t, g;
    bool found = false;
    t = l;
    a = l->next;
    while (a != nullptr && !found) {
        g = l;
        while (g != a && g != t) {
            g = g->next;
        }
        if (g == a) {
            found = true;
        }
        t = t->next; // t = a
        a = a->next;
    }
    return found;
}

// soluzione migliore con complessità n
// togliamo il giudice, t va avanti di 1, a va avanti di 2 ogni volta, in questo modo se achille raggiunge la tartaruga prima della fine della lista
// allora la lista ha un cappio
// attenzione controllare che a non scavalchi t, controllare ad ogni passo anche se fa 2 passi alla volta

bool has_noose_n(List l) {
    List a, t;
    bool found = false;
    t = l;
    a = l->next;
    while (a != nullptr && !found) {
        if (a == t) {
            found = true;
        }
        a = a->next;
        if (a == t) {
            found = true;
        }
        a = a->next;
        if (a == t) {
            found = true;
        }
        t = t->next;
    }
    return found;
}

List newcell(int info) {
    List tmp = new cell;
    tmp->info = info;
    tmp->next = nullptr;
    return tmp;
}

int main() {
    List linear_list = newcell(0);
    List pc = linear_list;
    for (int i = 1; i < 5; i++) {
        pc->next = newcell(i);
        pc = pc->next;
    }
    print(linear_list);

    // ---
    List circular_list = newcell(0);
    pc = circular_list;
    for (int i = 1; i < 5; i++) {
        pc->next = newcell(i);
        pc = pc->next;
    }
    pc->next = circular_list;
    print(circular_list);

    // ---
    List noose_list = newcell(0);
    pc = noose_list;
    pc->next = newcell(1);
    pc = pc->next;
    List p_cappio = pc;
    for (int i = 2; i < 5; i++) {
        pc->next = newcell(i);
        pc = pc->next;
    }
    pc->next = p_cappio;
    std::cout << has_noose_n(noose_list) << std::endl;

    return 0;
}
