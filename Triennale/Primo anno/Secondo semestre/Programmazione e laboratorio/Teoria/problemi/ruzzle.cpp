// Data una stringa mi metto sulla posizione nella matrice contenente la prima lettera, poi controllo quelle vicine
// il problema diventa: è possibile formare la stringa a partire dalla posizione (i,j)?
// la tabella è 4x4
#include <vector>

/*
* t: tabellone
* u: cella usata
* s: parola
* i,j: cella corrente
*/
bool trova_parola(const std::vector<std::vector<char>> &t, std::vector<std::vector<bool>>& u, std::string s, int i, int j) {
    if (i < 0 || i >= 4 || j < 0 || j >= 4) return false;
    else if (s.length() == 0) return true;
    else {
        if (s.at(0) != t.at(i).at(j) || u.at(i).at(j)) return false;
        else {
            bool found = false;
            u.at(i).at(j) = true;
            s.erase(s.begin(), s.begin());
            for (int r = i-1; r <= i+1; r++)
                for (int c = j-1; c <= j+1; c++)
                    if (!found) found = trova_parola(t, u, s, r, c);
            if (!found) u.at(i).at(j) = false;
            return found;
        }
    }
}

// trova la lettera iniziale
bool trova_tabella(const std::vector<std::vector<char>>& t, std::vector<std::vector<bool>>& u, std::string s) {
    bool found = false;
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 4; c++)
            if (!found)
                found = trova_parola(t, u, s, r, c);
    return found;
}
