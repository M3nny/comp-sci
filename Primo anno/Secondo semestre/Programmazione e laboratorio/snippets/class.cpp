#include <iostream>
#include <string>

using namespace std;

// stringhe pascal hanno lunghezza massima di 255
// la prima lettera rappresenta quanto è lunga la stringa (si evita \0 alla fine)

// le funzioni vanno definite all'interno della classe se la classe è usata solo nel file in cui è descritta
class stringPascal { // classe da mettere nel file .h
public:
    stringPascal(); // costruttore di default
    stringPascal(const string& s); // costruttore grazie a cui posso inizializzare l'oggetto con una stringa
    stringPascal(const stringPascal& s);
    void print();
    void set(const string& s);
    void set_char(int pos, char c);
    char get_char(int pos);
    void set_size(int dim);
private:
    unsigned char buff[256];
};

void stringPascal::set(const string& s) { // definizione delle classi da mettere nel file .cpp
    if (s.length() <= 255) {
        buff[0] = s.length();
    } else {
        buff[0] = 255;
    }
    for (int i = 1; i < buff[0]; i++) {
        buff[i] = s.at(i-1);
    }
}

void stringPascal::print() {
    for (int i = 1; i <= buff[0]; i++) {
        cout << buff[i];
    }
}

stringPascal::stringPascal() {
    buff[0] = 0;
}

stringPascal::stringPascal(const string& s) { // overloading dei costruttori
    set(s);
}

/* nel passaggio per copia viene usato questo costruttore
* utile in classi grandi perchè definisce cosa viene copiato e cosa no
* oggetti della stessa classe possono accedere alle rispettive parti private, in questo caso buff[] */
stringPascal::stringPascal(const stringPascal& s) { // costruttore per copia (copy constructor)
    buff[0] = s.buff[0];
    for (int i = 1; i <= buff[0]; i++) {
        buff[i] = s.buff[i];
    }
}

int main() {
    stringPascal x; // chiama il costruttore per l'oggetto x
    stringPascal y;
    x.set("Hi");
    y.set("Hello");
    x = y; // copio bit per bit lo stato di x in y

    // definisce 2 oggetti: un puntatore stringPascal ed un new stringPascal
    stringPascal* p = new stringPascal;

    /* se avessi avuto 2 puntatori avrei copiato solo il puntatore (shallow copy)
     * (deep copy se copio sia il puntare ed i suoi contenuti) */

    /*il costruttore della classe è un metodo che viene chiamato ogni volta che essa viene dichiarata
     * deve essere pubblico, se non ha alcun parametro formale si chiama costruttore di default
     * si chiama come la classe stessa, se non è stato definito uno, c++ ne crea uno vuoto in automatico */

    string cpps = "Hi";
    stringPascal z(cpps);

    stringPascal w(z);
}
