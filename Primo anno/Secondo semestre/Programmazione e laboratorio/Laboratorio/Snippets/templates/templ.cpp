#include <iostream>
#include <vector>

template<typename T>
struct container {
    container(){};
    container(T const& y): x(y) {} // lista di inizializzazione
    void increment(){x++;}
    T const& get(){return x;}

    // ++x
    int operator++() {
        x = x + 1;
        return x;
    }

    // x++
    int operator++(int) {
        int tmp = x;
        ++x;
        return tmp;
    }

private:
    T x;
};

template<typename T> // posso mettere anche class al posto di typename
T max(T const& x, T const& y) {
    if (x > y) return x;
    return y;
}

template<class T1, class T2>
bool are_equal(T1 const& x, T2 const& y) {
    return x == y;
}

// --- standard nomi dei parametri formali per overloading operatori ---
// lhs: left-hand side
// rhs: right-hand side


template<typename T>
struct m_container {
public:
    m_container(): m_data(nullptr), m_size(0) {}
    ~m_container() {
        if (m_data != nullptr)delete[] m_data;
    }

    // T deve avere operator<<(ostream T)
    // deve avere membri pubblici first, second
    // deve esistere un cast implicito da Z al tipo di T::first e T::second
    template<typename Z>
    void build_from(Z const* items, uint64_t n_items) { // Z è const, non items, se faccio *(items++) è ok ma se faccio *(items)++ no
        m_size = n_items / 2;
        if (n_items != 0) {
            m_data = new T[m_size];

            for (uint64_t i = 0; i != m_size; ++i, items += 2) {
                m_data[i].first = *items;
                m_data[i].second = *(items++);
            }
        }
    }

    void print() {
        for (uint64_t i = 0; i < m_size; i++) {
            std::cout << m_data[i] << " "; // TODO: fix operator visibility
        }
        std::cout << std::endl;
    }
private:
    T* m_data;
    uint64_t m_size;
};

typedef std::pair<int, int> my_pair;
std::ostream& operator<<(std::ostream& lhs, my_pair const& rhs) {
    lhs << "(" << rhs.first << "," << rhs.second << ")";
    return lhs;
}

int main() {
    // se non specifico il tipo lo capisce a compile time se può
    std::cout << max(1,2) << std::endl;
    std::cout << are_equal<int, double>(1, 0.5) << std::endl;

    container<int> x(5);

    // ---
    m_container<my_pair> y;
    std::vector<double> vec {1,2,3,4,5,6};
    y.build_from<double>(vec.data(), vec.size());
    y.print();

    return 0;
}
