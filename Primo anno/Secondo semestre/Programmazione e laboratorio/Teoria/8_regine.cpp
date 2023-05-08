/* Si possono posizionare 8 regine in una scacchiera senza che fra di loro siano sotto scacco?
* SI -> mostra una solzuione
* NO -> non mostrare nulla
* Matrice 8x8 char:
*   0: libero non sotto scacco
*   n >= 0: libero sotto scacco da n regine
*   -1: cella con regina
* Creiamo una soluzione con backtracking, ovvero se il risultato della ricorsione non ci va bene, lo cambiamo
*/

#include <vector>

void posiziona(std::vector<std::vector<short int>>& scac, int row, int col) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == row && j == col) {
                scac.at(i).at(j) = -1;
            } else {
                if (i == row || j == col || i-row == j-col || i+j == row + col) {
                    scac.at(i).at(j)++;
                }
            }
        }
    }
}

void rimuovi(std::vector<std::vector<short int>>& scac, int row, int col) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i == row && j == col) {
                scac.at(i).at(j) = 0;
            } else {
                if (i == row || j == col || i-row == j-col || i+j == row + col) {
                    scac.at(i).at(j)--;
                }
            }
        }
    }
}

bool regine(std::vector<std::vector<short int>>& scac, int col) {
    if (col == 8) return true; else {
        bool found = false;
        int row = 0;
        while (row < 8 && !found) {
            if (scac.at(row).at(col) == 0) {
                posiziona(scac, row, col);
                found = regine(scac, col+1);
                if (!found) {
                    rimuovi(scac, row, col); // backtracking: annullo l'ultima operazione
                    row++; // provo la prossima riga
                }
            } else {
                row++; // provo la prossima riga
            }
        }
        return found;
    }
}

