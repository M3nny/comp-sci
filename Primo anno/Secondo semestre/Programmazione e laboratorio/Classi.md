>[!Info]
>Le stringhe in Pascal hanno lunghezza massima di 255 char, la prima cella è riservata per descrivere la lunghezza della stringa stessa

Le dichiarazioni delle classi vanno generalmente messe all'interno di un `header` file, mentre la definizione delle loro funzioni all'interno di un file `cpp` 

## Visibilità
Possiamo nascondere all'utilizzatore dell'oggetto parti della sua classe (metodi/variabili) di appartenenza grazie alle keyword:
- **public**: _rende accessibile_ all'utilizzatore questa parte di classe
- **private**: _nasconde_ questa parte di classe all'utilizzatore

Da notare che oggetti della stessa classe possono accedere alle rispettive parti private.

## Costruttori
Il **costruttore** della classe **è un metodo** che viene chiamato ogni volta che un oggetto di quella classe viene istanziato.
- Deve essere **pubblico**
- Se non ha alcun parametro formale si chiama **costruttore di default**
- Possiamo definire un **costruttore per copia** (copy constructor) il quale gestisce come viene passato l'oggetto per copia, utile in classi grandi perchè definisce cosa viene copiato e cosa no.

Inoltre si chiama come la classe stessa, se non ne è stato definito uno, c++ ne crea uno vuoto in automatico.

## Distruttore
Esiste solo un distruttore, il quale è senza parametri formali e viene chiamato automaticamente quando l'oggetto della classe va fuori scope.

```cpp
class stringPascal {
public:
	// costruttore di default
    stringPascal();
    
    // costruttore grazie a cui posso inizializzare l'oggetto con una stringa
    stringPascal(const string& s);
    
    // costruttore per copia (copy constructor)
    stringPascal(const stringPascal& s);
	
	// distruttore (preceduto da ~)
    ~String_Pascal();
    
    void print();
    void set(const string& s);
    void set_char(int pos, char c);
    char get_char(int pos);
    void set_size(int dim);
private:
    unsigned char buff[256];
};
```

## Metodi
La definizione dei metodi (normalmente su file diverso) avviene ponendo il nome della classe prima del metodo (dichiarato in precedenza) che si vuole definire.

```cpp
void stringPascal::set(const string& s) {
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

// overloading dei costruttori
stringPascal::stringPascal(const string& s) {
    set(s);
}

// buff accede a s.buff (passato alla funzione) anche se è privato dato che fanno parte delle stessa classe
stringPascal::stringPascal(const stringPascal& s) {
    buff[0] = s.buff[0];
    for (int i = 1; i <= buff[0]; i++) {
        buff[i] = s.buff[i];
    }
}
```

### Modalità di copia
- **Shallow copy**: copio il puntatore, ora viene condivisa la stessa area di memoria
- **Deep copy**: copio i contenuti dell'altra area di memoria nella mia area di memoria, i cambiamenti ad una delle due aree di memoria non influenzerà l'altra.
```cpp
int main() {
    stringPascal x; // chiama il costruttore di default per l'oggetto x
    stringPascal y;
    x.set("Hi");
    y.set("Hello");
    x = y; // copio bit per bit lo stato di x in y
    
    // definisce 2 oggetti: un puntatore stringPascal ed un new stringPascal
    stringPascal* p = new stringPascal;
    
    string cpps = "Hi";
    
    /* definisco subito l'oggetto grazie al costruttore definito sopra
    che mi permette di dare in input una stringa durante
    la dichiarazione stessa dell'oggetto */
    stringPascal z(cpps); 
    stringPascal w(z);
}
```

Con la dicitura **const** dopo il metodo di una classe, andiamo a specificare che quel metodo non altera lo stato della classe e quindi può essere chiamato da una funzione che contiene parametri formali del tipo const&

```cpp
class String_Pascal {
public:
    void print_const() const; 
};
```

### Liste di inizializzazione
Possiamo istanziare un oggetto (con il costruttore di default) in memoria direttamente con dei valori che specifichiamo al posto di allocarlo e poi inizializzare i valori.
Questo meccanismo è molto utile per istanze di grandi oggetti.

```cpp
// costruttore con lista di inizializzazione
token() : m_value(inf), m_type(0) {}

// costruttore classico
token() {
	m_value = inf;
    m_type = 0;
}
```

- La dimensione di una struct non è uguale alla somma delle dimensione dei suoi campi, ci potrebbero essere dei campi di allineamento

### Problema del default copy constructor
Assumendo che nel costruttore di String_Pascal usiamo una **new** e nel distruttore una **delete**, quando non definisco il copy constructor, e uso quello di default, **copio bit per bit lo stato della classe s in t**:
```cpp
String_Pascal s(string);
String_Pascal t = s;
```
t prende lo stato di string pascal s, t punta alla stessa memoria di s, quando va fuori scope viene prima chiamato il distruttore di t (allocato per ultimo) e fa il delete, s nel frattempo non sa che t ha fatto la delete, e in quel momento che muore s, viene chiamato il distruttore di s, ma **l'area di memoria a cui puntava è già stata distrutta dal distruttore di t**.

Il copy constructor di default quindi esegue una _shallow copy_, dobbiamo ridefinire il copy constructor per eseguire una deep copy.
