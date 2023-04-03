#include <iostream>
#include <limits>
#include <cassert>
#include <vector>

/* Grammar:
 * L (lista di statement) -> S. | S;L
 * E (expression)-> P | E + P | E - P
 * P (produttoria) -> T | P * T | P / T
 * T (carattere terminale) -> double | (E) | var
 * S (statement) -> var = E | p(E)
 */

// var: {a, b, c, ..., z} \ {p}

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
        if (c >= '0' && c <= '9') { // 0 e 9 caratteri ascii
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
    char get_var_name() const {return m_type;}

    bool is_double() const {return m_type == 0 and m_value != inf;}
    bool is_open() const {return m_type == '(';}
    bool is_close() const {return m_type == ')';}
    bool is_add() const {return m_type == '+';}
    bool is_sub() const {return m_type == '-';}
    bool is_mul() const {return m_type == '*';}
    bool is_div() const {return m_type == '/';}
    bool is_eq() const {return m_type == '=';}
    bool is_var() const {return m_type >= 'a' and m_type <= 'z' and m_type != 'p';}
    bool is_print() const {return m_type == 'p';}
    bool is_dot() const {return m_type == '.';}

private:
    double m_value;
    double m_type;
};

double vars[256];

double E(const std::vector<token>& t, int& i);
void L(const std::vector<token>& t, int& i);

// token corrente (da leggere) t[i]
double T(const std::vector<token>& t, int& i) {
    // T -> double | (E) | var

    double res = 0;
    if (t[i].is_double()) {
        res = t[i].get_value();
        i++; // mangio i token t[i]
    } else if (t[i].is_var()){
        res = vars[t[i].get_var_name()]; // estrae il valore della variabile con nome t[i]
        i++; // consumo il token var
    } else {
        assert(t[i].is_open());
        i++; // consumo (
        res = E(t, i); // E incrementa i
        assert(t[i].is_close());
        i++; // consumo )
    }
    return res;
}

double P(const std::vector<token>& t, int& i) {
    // P -> T oppure P * T oppure P / T
    double res = T(t, i);
    token tok = t[i];

    while (tok.is_mul() or tok.is_div()) {
        i++; // consumo * oppure /
        if (tok.is_mul()) res *= T(t, i);
        if (tok.is_div()) res /= T(t, i);
        tok = t[i];
    }
    return res;
}

double E(const std::vector<token>& t, int& i) {
    // E -> P oppure E + p oppure E - P
    double res = P(t,i); // P incrementa i fino alla posizione successiva a P
    token tok = t[i];

    while (tok.is_add() or tok.is_sub()) {
        i++; // consumo + oppure -
        if (tok.is_add()) res += P(t, i); // leggo il P successivo
        if (tok.is_sub()) res -= P(t, i); // leggo il P successivo
        // i punta al token successivo a P
        tok = t[i];
    }
    //(debug): std::cout << "Parziale: " << res << std::endl;
    return res;
}

void S(const std::vector<token>& t, int& i) {
    // S -> var = E | p(E)

    if (t[i].is_var()) {
        // S -> var = E
        char c = t[i].get_var_name();
        i += 2; // consumo il token 'var'ed il token '='
        double res = E(t, i);
        vars[c] = res;

    } else { // S -> p(E)
        assert(t[i].is_print());
        i += 2; // consumo 'p' e '('
        double res = E(t, i);
        i++; // consumo '('
        std::cout << res << std::endl;
    }
}

void L(const std::vector<token>& t, int& i) {
    // L -> S. | S;L
    S(t, i); // consumo il primo statement S

    if (t[i].is_dot()) {
        i++; // consumo il '.'
        return;
    }
    i++; // consumo ';'
    L(t, i);
}


int main () {
    std::vector<token> tokens;

    do {
        token t;
        std::cin >> t;
        tokens.push_back(t);

    } while (!tokens.back().is_dot());
    int i = 0;
    L(tokens, i);
    return 0;
}
