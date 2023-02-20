- **Tipo**: insieme di valori sul quale sono definite delle operazioni.
- **Oggetto**: Regione della memoria con un _tipo_ associato.
- **Variabile**: oggetto a cui è assegnato un nome.
- **Dichiarazione**: introduce un nuovo nome (e.g. ```int a```)
- **Definizione**: si dice tale se sto allocando memoria (una dichiarazione è anche una definizione), posso dichiarare nomi senza definirli con le reference. Nota che la dichiarazione ```extern int a``` non è una _definizione_ in quanto introduce un nuovo nome che però è allocato altrove.

``` c
int *p = (int*)malloc(100)
``` 
Sotto un'ottica di C, questa istruzione allocherebbe 2 oggetti, 1 che ha nome, ovvero p e 1 senza nome, ovvero il malloc.

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

---
#### Codice pulito
```cpp
const int a = 7; // è una variabile che non può essere cambiata
constexpr int a = 7; // per costanti

while (cond) {
    blocco;
}

for (;cond;) { // non useremo mai il for come il while
    blocco;
}
```
- Non useremo break, continue e goto

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

**Capacità**: quanti elementi può tenere in memoria, viene raddoppiata quando con l'aggiunta di un elemento sforo la capacity, viene ridotta quando il 
vector ha almeno metà capacità vuota (non ci sono elementi effettivi)
**Size**: quanti elementi effettivi contiene al suo interno.
