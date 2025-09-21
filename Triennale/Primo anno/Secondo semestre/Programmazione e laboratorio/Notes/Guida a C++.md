- **Tipo**: insieme di valori sul quale sono definite delle operazioni.
- **Oggetto**: Regione della memoria con un _tipo_ associato.
- **Variabile**: oggetto a cui è assegnato un nome.
- **Dichiarazione**: introduce un nuovo nome (e.g. `int a`)
- **Definizione**: si dice tale se sto allocando memoria (una dichiarazione è anche una definizione), posso dichiarare nomi senza definirli con le reference. Nota che la dichiarazione `extern int a` non è una _definizione_ in quanto introduce un nuovo nome che però è allocato altrove.

``` c
int *p = (int*)malloc(100)
``` 
Sotto un'ottica di C, questa istruzione allocherebbe 2 oggetti, 1 che ha nome, ovvero p e 1 senza nome, ovvero il malloc.

- **Compilazione**: traduzione da linguaggio a codice oggetto (vicino al linguaggio macchina)
- **Linking**: collega i file oggetto e genera l'eseguibile

---
Se il cambio di tipo porta a perdita di informazioni si parla di **narrowing**

Es:
``` cpp
int a;
double 3.14;
a = b; // narrowing (avviene casting implicito + perdità di informazione)
b = a; // avviene casting implicito
```

In c++ `int k{12}` controlla che non sto facendo narrowing, con `int k{12.3}` da errore (questo da c++ 14)

---
#### Left & Right value
Quando ho un assegnamento ho un left e right value, il compilatore per prima cosa guarda se il valore a destra e sinistra sono compatibili
**Left value**: indirizzo di memoria
**Right value**: valore assegnato all'indirizzo di memoria

b = a = a + 2 -> b = (a = a + 2)

- `&` prende in input una variabile (lvalue) e restituisce un numero (rvalue) (e.g. restituisce int*).
- `*` prende in input un'indirizzo di memoria, quindi un numero (rvalue) e restituisce una variabile (lvalue).

- Posso sommare/sottrarre un intero ad un indirizzo di memoria.
- Posso sottrarre due indirizzi di memoria ma non sommarli.

---
#### Codice pulito
```cpp
const int a = 7; // è una variabile intera che non può essere cambiata
constexpr int a = 7; // è un'espressione che non può essere modificata (simile al define in C)

while (cond) {
    blocco;
}

for (;cond;) { // non useremo mai il for come il while
    blocco;
}
```
- Non useremo break, continue e goto
- Una funzione o calcola o stampa
- Il controllo dei tipi è fatto staticamente su C perchè sono controllati nella compilazione

##### Cicli
- **Invariante** del ciclo è la descrizione della proprietà delle variabili che non cambiano al suo interno, ovvero è una proprietà vera prima e dopo ogni iterazione. Ad esempio nella funzione $max$ avrò che la variabile $m$ sarà sempre e comunque il valore massimo fino a quel punto in cui si è arrivati a scorrere l'array.
- Dove si può scrivere il for si usa il for e non il while
- Dentro al blocco for non modificheremo la variabile usata per l'iterazione, quindi quando si usa il for siamo certi di quante volte itera (dato che non andremo ad usare break e/o modificare la variabile di iterazione)

---
#### References
A differenza di C che esegue il _passaggio per copia di un indirizzo di una variabile_, su C++ usiamo il _passaggio per referenza o indirizzo_.

Non dobbiamo avere a che fare direttamente con puntatori, vengono usate le **referenze**, ovvero assegnamo un'altro nome ad una variabile, quando cambia una delle due, entrambe vengono cambiate.
Non posso solamente dichiarare una referenza, devo anche inizializzarla subito.
```cpp
double a;
double& b = a; // devo dire a quale variabile fa riferimento
```

In questo modo è possibile passare variabili alle funzione alle quali la funzione può cambiare valore senza istanziare nuova memoria e gestire puntatori. 
```cpp
void swap(int& a, int& b) {
	int c;
	c = a;
	a = b;
	b = c;
}

int main () {
int x = 3, y = 4;
swap(x,y); // passaggio per referenza
cout << x << " " << y << endl; // flush immediato dell'output, utile per debug
}
```

---
#### Passaggio di parametri
Nei passaggi per **copia** viene creato un ambiete (distrutto alla fine dell'esecuzione della funzione) della funzione ovvero vengono allocati in
memoria tutti i parametri formali (contenuti nella firma) ed il loro valore viene inizializzato valutando i loro parametri effetivi.

_Con static mantengo vivo l'ambiente alla fine della funzione_

``` c
void esempio (int a, double b) { // i parametri formali vegnono inizializzati con i valori dei parametri attuali

}

int main () {
    int k;
    esempio(123, 25); // il 25 ottiene una promozione di tipo
}
```

Nel passaggio di parametri per **reference** il parametro a e b non viene istaziato in memoria, per cui se ho un parametro da 1MB viene più agevole
dato che non creo un ambiente e copio 1MB.
Nel passaggio di refrenza a differenza di quello epr copia mi interessa il right value

``` cpp
int esempioRef(int a, double& b) {

}

int main () {
    int x;
    double p;

    esempioRef(x, p); // p deve essere double, non può essere altro
}
```

**Esempio**:
``` c
struct s { // pesa almeno come un intero ed un double
    int a;
    double b;
};
typedef struct s ts; // in cpp typedef sparisce, posso usare direttamente s senza scrivere struct davanti

void foo(ts x) {
    x.a = 12;
    x.b = 12.3;
}

int main () {
    ts y;
    foo(y);
}
```

---
#### Vector
Mentre in C se passo un array ad una funzione, gli passo solo il puntatore al primo elemento (non posso fare altrimenti), e se l'array è dentro una
struct lo copia tutto. In C++ se passo il vector, lo passo tutto per copia, mentre per se uso l'& gli passo solo il puntatore al primo elemento.

``` cpp
#include <vector>
using namespace std;

void foo(vector<int> par); // copio tutto il vettore
void foo(vector<int>& par); // lo passo per reference, quindi non istanzio nuova memoria

int main () {
    vector<double> v; // <double> e <int> sono template
    vector<int> v2(20); // posso specificare quanti elementi ha al suo interno

    v.push_back(13.4); // inserisco elementi senza preoccuparmi della lunghezza dell'array
    v[0] = 15.1; // scrivo dentro ad un array, da usare solo se si è sicuri che contenga l'elemento specificato (è più veloce di v.at)
    v.at(3) = 15.1; // usiamo questo perchè controlla se effettivamente l'array contenga un quarto elemento
    v.size(); // ritorna la lunghezza dell'array

}
```

- **Capacità**: quanti elementi può tenere in memoria, viene raddoppiata quando con l'aggiunta di un elemento sforo la capacity, viene ridotta quando il vector ha almeno metà capacità vuota (non ci sono elementi effettivi).
- **Size**: quanti elementi effettivi contiene al suo interno.

Vedi **algoritmi di scorrimento per vector** nel file ```vector.cpp```

```cpp
void leggi(vector<int>& tr) {
    int len;
    cin >> len;
    tr.resize(len);
    for (auto& e:tr) { // dato che sto usando la reference posso cambiare e
        cin >> e;
    }
}

void leggi_copia(vector<int>* tr) { // copia l'indirizzo di memoria
    int len;
    int e;
    cin >> len;
    (*tr).resize(len);
    for (int i = 0; i < len; i++) {
        cin >> (*tr).at(i);
            // oppure tr->at(i);
    }
}

void accumulo() {
    vector<int> v;
    int sum = 0;
    leggi_copia(&v);

	/*
	invariante: sum 
	contiene ad ogni iterazione la somma degli elementi
	della partizione visitata
	*/
    for (int i = 0; i < v.size(); i++) {
        sum += v.at(i);
    }
    sum = 0;

    /*
    Sostituisco con il for-each;
    
    In python sarebbe (for element in v), all'interno della varibile e viene 
    copiato il valore nella posizione associata del vettore;
    
    Posso solo leggere con questo ciclo, non devo modificare la grandezza
    dell'array all'interno del ciclo
    */
    for (auto e:v) { 
        sum += e;
    }
    
    /* 
    auto controlla staticamente il tipo della variabile il tipo alla
    quale è assegnata (ovviamente non posso dichiarare e basta una
	variabile con auto)
	*/
    cout << sum;

    vector<int> nuovo;
    nuovo = v; // copio v dentro a nuovo
}

void contatore() {
    vector<int> v;
    leggi(v);
    int pari = 0;
    /*
    Invariante: pari
    contiene il numero di elementi pari dell'array nella porizone
    visitati tra 0 e i-1
    */
    for (auto e:v) {
        if (e%2 == 0) {
            pari += 1; 
        }
    }

}

void multi_vector() {
    vector<vector<int>> matrice;
    int nr, nc;
    cin >> nr;
    cin >> nc;
    matrice.resize(nr);
    for (auto& e:matrice) {
        e.resize(nc);
    }

    for (auto r:matrice) {
        for (auto& e:r) {
            e = 0;
        }
    }
}
```

---
#### Memoria dinamica
La gestione della memoria in C non è tipata, sa solo quanti byte sta allcoando
```c
int *p = (int*)malloc(100); // l'oggetto puntato da p è un oggetto dinamico
```

C++ supporta nativamente l'uso di oggetti dinamici (quindi senza importare standard library)
```cpp
int *p;
p = new int; // prende in input un tipo e ritorna il primo byte della memoria allocata
delete p; // prende in input il primo byte dell'indirizzo di memoria allocato da new

int size;
cin >> size;
p = new int[size]; // alloco in memoria dinamica un array, non lo useremo
delete[] p; // elimina tutto l'array
```

---
#### Stringhe
```cpp
#include <iostream>
#include <string>

using namespace std;

void foo(string s); // passaggio per copia
void foo(string& s); // passaggio per reference
void foo(const string& s); // leggo e basta con passaggio epr reference

int main () {
    string s1, s2;
    cin >> s1;
    cin >> s2;

    if (s1 == s2) { // fa quello che ci aspettiamo
        cout << "Le stringhe sono uguali";
    }

    s1 = s2; // s1 ora è s2

    if (s1 > s2) {
        cout << "s1 viene prima di s2 nell'alfabeto";
    }

    string s3;
    s3 = s1 + s2; // concatena le stringhe
    s3 = s1 + "ciao";
}
```

#### Funzione cappello
Con la **funzione cappello** impostiamo i parametri iniziali per un'altra funzione (che magari è privata all'interno di una classe)

```cpp
void List_int::append(int e) {
	// h è una variaile privata, lo stesso la funzione append_ric
	// chi usa questa classe non sa della loro esistenza
    append_ric(h, e);
}

void List_int::append_ric(pcella& testa, int e) {
    // ...
}
```

### Overloading degli operatori
Posso specificare il comportamento degli operatori con strutture dati e classi definite al di fuori dello standard c++.
Gli operatori con overloaded non sono commutativi, hanno associatività a sinistra.

Standard nomi dei parametri formali per overloading degli operatori:
- lhs: left-hand side
- rhs: right-hand side

```cpp
class ListDL {
public:
    ListDL();
    ListDL(const ListDL& s);
    ~ListDL();
    
    // aggiunge in coda la lista ripetuta n volte
    ListDL operator* (unsigned int n) const; 

private:
    struct cella {
        int info;
        cella* next;
        cella* prev;
    };
    typedef cella* pcella;
    pcella head, tail;
};

ListDL ListDL::operator* (unsigned int n) const {
    ListDL ris;
    for (int i = 0; i < n; i++) {
        pcella pc = head;
        while (pc != nullptr) {
            ris.append(pc->info);
            pc = pc->next;
        }
    }
    return ris;
}

int main () {
    ListDL l1;
    l1.append(5);
    l1 = l1 * 10; // overloaded *
    
    // 10 * l1 non andrebbe bene 
    // l'operatore '*' è definito se a sx c'è ListDL e a dx un uint
}

```

### Templates
I **templates** sono un metodo di astrazione dei tipi, se usati consentono di generalizzare un algoritmo (se possibile) a più tipi di dato.
Ad esempio un algoritmo di sorting è uguale per tutti i tipi di default.

A differenza delle **Macro** in C, le quali semplicemente eseguono delle <u>sostituzioni di testo</u>, i **templates** <u>lavorano a livello di compilazione</u>, in questo modo il compilatore controlla se il tipo passato al template può effettivamente essere usato.

Esistono 2 tipi di templates:
- Di **funzione**
- Di **classe**, una volta che gli è stato assegnato un tipo, si dice che è una **specializzazione**

È anche possibile definire funzioni con template (anche con typename diverso) all'interno di una classe con template.

```cpp
// Funzione
template<typename T> // posso mettere anche class al posto di typename
T max(T const& x, T const& y) {
    if (x > y) return x;
    return y;
}

int main() {
	// se non specifico il tipo lo capisce a compile time se può
	std::cout << max(1,2);
	// nel caso non fosse possibile:
	std::cout << max<int, int>(3,4);
}

```

```cpp
// Classe
template<typename T>
struct container {
	// ...
    container(T const& y): x(y) {} // lista di inizializzazione
    // ...
private:
    T x;
};

int main () {
	container<int> x(5);
}
```

Posso dare una valore di default al template, il quale deve essere conosciuto a compilaton time (è una costante).
Quando questo meccanismo viene usato, si tratta di un **non-type parameter**, ovvero a differenza di un tipo di **default**, un _non-type parameter_ non può cambiare tipo, ma solo valore della costante (a compile time).

```cpp
// T è un tipo di default
// N è un non-type parameter
template<typename T = double, int N = 100> 
struct my_sequence {
public:
	// ...
private:
    T vec[N]; // array statico lungo N
};

int main () {
    my_sequence<int, 5> seq; // array statico di 5 int
    my_sequence<> seq2; // array statico di 100 double
    my_sequence<int> seq3; // array statico di 100 int
}
```
