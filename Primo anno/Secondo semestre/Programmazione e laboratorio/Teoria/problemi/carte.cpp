#include <iostream>
#include <vector>
#include <cstdlib> // metto c davanti alla libreria che voglio importare di c
// ML per scoprire prossimo numero pseudo casuale

void inizializza(std::vector<int>& v, int carte) {
    v.resize(carte);

    for (int i = 0; i < carte; i++) {
        v.at(i) = i;
    }
}

void stampa(const std::vector<int>& v) { // con const pur avendo una reference non vado a modificare il parametro
    for (int i = 0; i < v.size(); i++) {
        std::cout << v.at(i) << std::endl;
    }
}

int estrai(std::vector<int>& v) {
    int da_estrarre = rand()%v.size();
    int result = v.at(da_estrarre);

    v.at(da_estrarre) = v.at(v.size()-1);
    v.pop_back();

    return result;
}

int main () {
    std::vector<int> mazzo;
    int ncarte;
    srand(time(NULL));

    std::cin >> ncarte;

    inizializza(mazzo, ncarte);
    stampa(mazzo);
    
    std::cout << "Carte estratte:"<< std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << estrai(mazzo) << std::endl;
    }

    std::cout << "Mazzo rimanente" << std::endl;
    stampa(mazzo);

    return 0;
}
