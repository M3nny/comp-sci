#include <iostream>

// posso dare una valore di default al tempalte nel caso non venisse specificato
template<typename T = double, int N = 100> // N deve essere conosciuto a compilaton time (non può essere una variabile)
struct my_sequence {
public:
    void set(int i, T value) {
        vec[i] = value;
    }
    T get(int i) {
        return vec[i];
    }
private:
    T vec[N]; // array statico lungo N
};

int main () {
    my_sequence<int, 5> seq;
    seq.set(3, 15);

    my_sequence<> seq2; // array statico di 100 double
    my_sequence<int> seq3; // array statico di 100 int
}
