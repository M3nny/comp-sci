#include <vector>

using std::vector;

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
private:
    vector<int> v;
};

List_int::List_int() {
    // vuoto: ci pensa il costruttore di vector
    // si può non implementare
}

List_int::List_int(const List_int& l) {
    v = l.v;
}

List_int::~List_int() {
    // vuoto: ci pensa il distruttore di vector
    // si può non implementare
}

void List_int::prepend(int e) {
    v.resize(v.size()+1);
    for (int i = v.size()-1; i > 0; i--) {
        v.at(i) = v.at(i-1);
    }
    v.at(0) = e;
}
