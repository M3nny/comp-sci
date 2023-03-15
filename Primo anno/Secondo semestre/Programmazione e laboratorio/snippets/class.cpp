#include <iostream>
#include <string>

using namespace std;

// stringhe pascal hanno lunghezza massima di 255
// la prima lettera rappresenta quanto è lunga la stringa (si evita \0 alla fine)

// le funzioni vanno definite all'interno della classe se la classe è usata solo nel file in cui è descritta

class String_Pascal { // classe da mettere nel file .h
public:
    String_Pascal(); // costruttore di default
    String_Pascal(const string& s); // costruttore grazie a cui posso inizializzare l'oggetto con una stringa
    String_Pascal(const String_Pascal& s);
    ~String_Pascal(); // distruttore
    void print();
    void print_const() const; // const indica che il metodo print non altera lo stato della classe e quindi può essere chiamato su una const reference
    void print_x2(String_Pascal input);
    void set(const string& s);
    void set_char(int pos, char c);
    char get_char(int pos);
    void set_size(int dim);
    char at(int);
private:
    unsigned char buff[256];
};

void String_Pascal::set(const string& s) { // definizione delle classi da mettere nel file .cpp
    if (s.length() <= 255) {
        buff[0] = s.length();
    } else {
        buff[0] = 255;
    }
    for (int i = 1; i <= buff[0]; i++) {
        buff[i] = s.at(i-1);
    }
}

void String_Pascal::print() {
    for (int i = 1; i <= buff[0]; i++) {
        cout << buff[i];
    }
    cout << endl;
}

void String_Pascal::print_x2(String_Pascal input) { // input chiama il copy constructor
    input.print();
    input.print();
}

String_Pascal::String_Pascal() {
    cout << "costruttore di default chiamato" << endl;
    buff[0] = 0;
}

String_Pascal::~String_Pascal() { // ci può essere solo il distruttore di default
    cout << "distruttore chiamato" << endl;
}

String_Pascal::String_Pascal(const string& s) { // overloading dei costruttori
    cout << "costruttore con parametro chiamato" << endl;
    set(s);
}

/* nel passaggio per copia viene usato questo costruttore
* utile in classi grandi perchè definisce cosa viene copiato e cosa no
* oggetti della stessa classe possono accedere alle rispettive parti private, in questo caso buff[] */
String_Pascal::String_Pascal(const String_Pascal& s) { // costruttore per copia (copy constructor)
    cout << "costruttore per copia chiamato" << endl;
    buff[0] = s.buff[0];
    for (int i = 1; i <= buff[0]; i++) {
        buff[i] = s.buff[i];
    }
}

char String_Pascal::at(int pos) {
    if (pos < buff[0]) {
        return buff[pos];
    } else {
        return -1;
    }
}

int main() {
    String_Pascal x; // chiama il costruttore per l'oggetto x
    String_Pascal y;
    x.set("Hi");
    x.print();
    y.set("Hello");
    y.print();
    x = y; // copio bit per bit lo stato di x in y
    x.print();

    // definisce 2 oggetti: un puntatore stringPascal ed un new stringPascal
    String_Pascal* p = new String_Pascal; // chiamo il copy constructor

    /* se avessi avuto 2 puntatori avrei copiato solo il puntatore (shallow copy)
     * (deep copy se copio sia il puntare ed i suoi contenuti) */

    /*il costruttore della classe è un metodo che viene chiamato ogni volta che essa viene dichiarata
     * deve essere pubblico, se non ha alcun parametro formale si chiama costruttore di default
     * si chiama come la classe stessa, se non è stato definito uno, c++ ne crea uno vuoto in automatico */

    string cpps = "Bye";
    String_Pascal z(cpps);
    z.print();
    cout << z.at(1) << endl;
    String_Pascal q = z;

    String_Pascal w(z);
    w.print_x2(z);
    delete p; // chiamo il distruttore
}
