#include <iostream>
#include <limits>
#include <cassert>
#include <vector>

// i membri di classi per convenzione vengono preceduti da m_
struct token {
    // con static, la costante inf sarà condivisa tra tutte le istanze di token, quindi che istanzio 10 token avrò solo 1 costante inf
    static constexpr double inf = std::numeric_limits<double>::max();
    // lista di inizializzazione, quando viene istanziato questo oggetto m_value e m_type prendono i valori di inf e 0
    token() : m_value(inf), m_type(0) {} // viene allocata la memoria direttamente con i valori delle variabili, utile per grandi oggetti

    /*
    *  Viene prima allocata memoria per l'oggetto e poi messi dentro i valori
    * token() {
    * m_value = inf;
    * m_type = 0;
    * }
    */

    // la funzione operator è esterna alla classe, ma dato che è friend potrà accedere a membri privati della classe
    friend std::ostream& operator << (std::ostream& os, const token& t) {
        os << "[m_value = " << t.m_value << ", m_type = " << (char)t.m_type << "]";
        return os;
    }

    friend std::istream& operator >> (std::istream& is, token& t) {
        char c;
        is >> c; // saltando gli spazi leggo il primo numero
        if ((c >= '0' && c <= '9') || c == '.') { // 0 e 9 caratteri ascii
            is.putback(c);
            is >> t.m_value;
        } else { // c è +-/*()=
            t.m_type = c;
        }
        return is;
    }

    double get_value() const {
        assert(is_double());
        return m_value;
    }

    char get_type() const {
        assert(!is_double());
        return m_type;
    }

    bool is_double() const {return m_type == 0 and m_value != inf;}
    bool is_open() const {return m_type == '(';}
    bool is_close() const {return m_type == ')';};
    bool is_add() const {return m_type == '+';};
    bool is_sub() const {return m_type == '-';};
    bool is_mul() const {return m_type == '*';};
    bool is_div() const {return m_type == '/';};
    bool is_eq() const {return m_type == '=';};

private:
    double m_value;
    double m_type;
};

int main () {
    std::vector<token> tokens;
    do {
        token t;
        std::cin >> t;
        tokens.push_back(t);
        // notare che il primo << è la funzione cout, mentre il secondo << è quello definito dalla nostra funzione
        std::cout << t << std::endl;
    } while (!tokens.back().is_eq()); // back ritorna l'ultimo elemento di un vettore
    return 0;
}
