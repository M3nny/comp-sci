Tutto è un oggetto.

**variabile**: oggetto a cui è assegnato un identificatore.

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

---
#### Left & Right value
Quando ho un assegnamento ho un left e right value, il compilatore per prima cosa guarda se il valore a destra e sinistra sono compatibili
**Left value**: indirizzo di memoria
**Right value**: valore assegnato all'indirizzo di memoria

b = a = a + 2 -> b = (a = a + 2)

---
In c++ `int k{12}` controlla che non sto facendo narrowing, con `int k{12.3}` da errore (questo da c++ 14)

- Si chiama **definizione** se sto allocando memoria, posso dichiarare nomi senza definirli con le reference

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
cout << x << " " << y << endl;
}
```
