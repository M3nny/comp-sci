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

// ---

// specializzazione di template
// scrivo una implementazione alternativa in base ai parametri del template
template<typename T>
void print(T const& x) {
    std::cout << "funzione generica chiamata: " << x << std::endl;
}

// versione specializzata per std::pari<int, int>
template<> // specializzazione totale
void print(std::pair<int,int> const& x) {
    std::cout << "funzione specializzata chiamata: (" << x.first << "," << x.second << ")" <<  std::endl;
}

// ---

template<typename T>
struct A {
public:
    A() {
        std::cout << "costruttore chiamato" << std::endl;
    }
private:
    T m_val;
};

template<>
struct A<int> {
public:
    A() {
        std::cout << "costruttore specializzato chiamato" << std::endl;
    }
private:
    int m_val;
    double x;
};

// ---

// definire una classe my_pair<FirstType, SecondType> che contiene 2 tipi
// scrivere funzione get<i>(p) dove i è 0 oppure 1 e p è un my_pair
// e.g.
// my_pair<double, pair<int,int>> p;
// get(0,p) ritorna il double
// get(1,p) ritorna il pair
// get<0>(p) sarà una funzioen diversa da get<1>(p)

template<typename FirstType, typename SecondType>
struct my_pair {
    typedef FirstType first_type;
    typedef SecondType second_type;
public:
    my_pair(FirstType f, SecondType s) : first(f), second(s) {}

    FirstType first;
    SecondType second;
};

// scopo di getter: esporre una funzione get che dipende da i e Mypair
// assumo che Myòair metta a disposizione tipi first_type, second_type e memebri pubblici first, second
template<int i, typename MyPair>
struct getter;

// specializzazione parziale: solo i viene specialzizato
template<typename MyPair>
struct getter<0> {
    typedef typename MyPair::first_type return_type;
    static return_type get(MyPair const& p) {
        return p.first;
    }
};

// specializzazione parziale: solo i viene specialzizato
template<typename MyPair>
struct getter<1> {
    typedef typename MyPair::second_type return_type;
    static return_type get(MyPair const& p) {
        return p.second;
    }
};

template<int i, typename MyPair>
typename getter<i, MyPair>::return_type get(MyPair const& p) {
    return getter<i,MyPair>::get(p);
}

int main() {
    my_sequence<int, 5> seq;
    seq.set(3, 15);

    my_sequence<> seq2; // array statico di 100 double
    my_sequence<int> seq3; // array statico di 100 int

    // ---

    double y = 5.2;
    print(y);

    std::pair<int,int> mypair(1,2);
    print(mypair);

    // ---

    A<double> x2; // viene usata la classe generica
    A<int> x3; // viene usata la classe specializzata per int

    // ---

    typedef my_pair<int,double> My_pair;
    My_pair p3 {5,3.14};
    auto f = get<0>(p3);
    auto s = get<1>(p3);

    return 0;
}
