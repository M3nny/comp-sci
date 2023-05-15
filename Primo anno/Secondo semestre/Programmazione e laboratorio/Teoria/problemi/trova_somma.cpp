// dato un vector di int dire se si può formare una somma s con n addendi
#include <vector>
bool trova_somma(const std::vector<int>& v, int s, int add, int pos) {
    bool risp;
    if (add == 0 && s == 0) {
        return true;
    } else if (add == 0){
        return false;
    }
    // se il primo or è true, non verifico la seconda condizione (or cortocircuitato)
    risp = trova_somma(v, s-v.at(0), add-1, pos+1) || trova_somma(v, s, add, pos+1); // backtracking
    if (pos > v.size()) {
        return false;
    }

    return risp;
}
