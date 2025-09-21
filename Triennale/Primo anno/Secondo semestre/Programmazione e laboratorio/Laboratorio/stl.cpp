#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

/* Funtore (functor) = oggetto che definisce operator(x,y)
 * posso usare l'oggetto come funzione
*/
struct my_comp {
    bool operator() (int x, int y) {
        // return x > y; // pop in ordine crescente

        // Pop prima i numeri dispari poi quelli pari
        if (x%2 == 0) {
            if (y%2 != 0) return true;
        } else {
            if (y%2 == 0) return false;
        }
        return x < y;
    }
};

struct date {
    int dd;
    int mm;
    int yyyy;
};
void test_stack() { // LIFO
    std::stack<int> s;
    s.push(1); s.push(2); s.push(3);
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
}

void test_queue() { // FIFO
    std::queue<int> q;
    q.push(1); q.push(2); q.push(3);
    std::cout << q.front() << std::endl;
    q.pop();
    std::cout << q.front() << std::endl;
}

void test_priority_queue() { // leggermente più lenta di queue e stack (log(n)), ma priorità personalizzata
    std::priority_queue<int, std::deque<int>, my_comp> pq;
    /* Tipi di priority
     * Default: pop in ordine decrescente
     *  viene usata: std::priority_queue<int, std::deque<int>> pq;
     */
    pq.push(1);
    pq.push(2);
    pq.push(3);
    while (!pq.empty()) {
        std::cout << pq.top() << " -> ";
        pq.pop();
    }
    std::cout << std::endl;
}

void test_algorithm() {
    std::vector<int> v {3, 1, 2};
    my_comp c;
    // std::sort(v.begin(), v.end(), c); // se non specifico il funtore ordina in ordine crescente
    // il funtore lo usiamo solo una volta, se la funzione viene usata solo una volta possiamo usare
    // una lambda function

    std::sort(v.begin(), v.end(), 
        [](int x, int y) -> bool {return x > y;} // ordino in ordine decrescente
    );

    int w = 5;
    // devo usare auto perchè il tipo non lo so, il compilatore crea una struct con un nome creato al volo
    // dove ls sua struttura è simile a my_comp
    /* Catture di variabili dello scope attuale
     * & -> cattura per reference
     * = -> cattura per valore
     */
    auto f = [&w](int x, int y) -> bool {return x+w >y;};

    for (auto x:v) std::cout << x << std::endl;
}

void test_lambda() {
    std::vector<date> v;
    v.push_back({12,10,2000});
    v.push_back({2,7,1920});
    v.push_back({3,9,2025});
    v.push_back({23,8,1999});
    std::sort(v.begin(), v.end(), // sort per anno crescente
        [](date& d1, date& d2) {
            return d1.yyyy < d2.yyyy;
        }
    );
    for (auto x:v) std::cout << x.dd << " " << x.mm << " " << x.yyyy << std::endl;
}

int main () {
    test_stack();
    test_queue();
    test_priority_queue();
    test_algorithm();
    test_lambda();
    return 0;
}
