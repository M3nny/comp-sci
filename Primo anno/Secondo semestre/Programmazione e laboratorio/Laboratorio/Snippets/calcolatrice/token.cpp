#include <iostream>
#include <limits>

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

    // la funzione è esterna alla classe, ma dato che è friend potrà accedere a membri privati della classe
    friend std::ostream& operator << (std::ostream& os, const token& t);

    double get_value() const;
    char get_type() const;
    bool is_double() const {return m_type == 0 and m_value != inf;}
    bool is_open() const {return m_type == '(';}
    bool is_close() const;
    bool is_add() const;
    bool is_sub() const;
    bool is_mul() const;
    bool is_div() const;
    bool is_eq() const;

private:
    double m_value;
    double m_type;
};
