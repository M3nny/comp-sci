#include <iostream>
#include <vector>
using namespace std;

void leggi(vector<int>& tr) {
    int len;
    cin >> len;
    tr.resize(len);
    for (auto& e:tr) { // dato che sto usando la reference posso cambiare e
        cin >> e;
    }
}

void leggi_copia(vector<int>* tr) { // copia l'indirizzo di memoria
    int len;
    int e;
    cin >> len;
    (*tr).resize(len);
    for (int i = 0; i < len; i++) {
        cin >> (*tr).at(i);
            // oppure tr->at(i);
    }
}

void accumulo() {
    vector<int> v;
    int sum = 0;
    leggi_copia(&v);

    for (int i = 0; i < v.size(); i++) { // invariante: sum contiene ad ogni iterazione la somam degli elementi della partizione visitata
        sum += v.at(i);
    }
    sum = 0;

    // sostituisco con il for-each
    for (auto e:v) { // in python sarebbe (for element in v), all'interno della varibile e viene copiato il valore nella posizione associata del vettore
        sum += e;   // posso solo leggere con questo ciclo, non devo modificare la grandezza dell'array all'interno del ciclo
    }
    // auto controlla staticamente il tipo della variabile il tipo alla quale è assegnata (ovviamente non posso dichiarare e basta uan variabile con auto)
    cout << sum;

    vector<int> nuovo;
    nuovo = v; // copio v dentro a nuovo
}

void contatore() {
    vector<int> v;
    leggi(v);
    int pari = 0;
    for (auto e:v) {
        if (e%2 == 0) {
            pari += 1; // invariante: contiene il numero di elementi pari dell'array nella porizone visitati tra 0 e i-1
        }
    }

}

void multi_vector() {
    vector<vector<int>> matrice;
    int nr, nc;
    cin >> nr;
    cin >> nc;
    matrice.resize(nr);
    for (auto& e:matrice) {
        e.resize(nc);
    }

    for (auto r:matrice) {
        for (auto& e:r) {
            e = 0;
        }
    }

    for (auto r:matrice) {
        for (auto& e:r) {
            cout << e;
        }
        cout << endl;
    }

}

int main () {
    /*--- algoritmo per accumulo ---*/
    //accumulo();
    /*--- algoritmo per contatore---*/
    //contatore();
    /*--- vector multidimensionali ---*/
    multi_vector();
}
