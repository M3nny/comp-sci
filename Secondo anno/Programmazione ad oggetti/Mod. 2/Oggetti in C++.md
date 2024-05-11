[[Guida a C++|C++]] è un linguaggio **fortemente tipato multi-paradigma/multi-stile** con molteplici standard in evoluzione negli anni.

A differenza di [[Guida a Java|Java]], <u>non esiste una visibilità di default</u>.
```cpp
class animal {
protected:
	int weight;
	double speed;
public:
	// constructor
	animal(int w, double sp) : weight(w), speed(sp) {}
    // copy constructor
    animal(const animal& a) : animal(a.weight, a.speed) {}
    
    virtual void eat(const animal& a) {
        weight += a.weight;
    }
}
```

È buona regola passare dove possibile i parametri per **const reference**.
>Nota che se non venissero passati per reference nel copy constructor avverrebbe una ricorsione infinita.

#### Virtual
La keyword `virtual` abilita l'override mettendo il metodo in virtual table abilitando in questo modo il **dynamic dispatching**.
Se il figlio non mettesse `virtual` nel suo _override_ della funzione, ne **bloccherebbe l'override** da parte di eventuali figli più in basso nella gerarchia. 
>La funzione comunque è in virtual table a causa del padre che ha specificato `virtual`.
### Ereditarietà
L'**ereditarietà** può avvenire in tre modi in base a come si vuole **subsumere**, in alcuni casi non si vuole che il tipo venga subsunto e quindi ne si limita il polimorfismo (solitamente si usa `public`).
- `public`: le sezioni _public_ e _protected_ della classe padre **rimarranno** _public_ e _protected_ anche nella classe figlio
- `protected`: le sezioni _public_ e _protected_ della classe padre **diventeranno** entrambe _protected_ nella classe figlio
- `private`: le sezioni _public_ e _protected_ della classe padre **diventeranno** entrambe _private_ nella classe figlio

```cpp
class dog : public animal {
protected:
	bool has_pedigree
}
```

### Costruttori
È buona regola inizializzare i campi con le **initializer list** in quanto allocheranno direttamente la memoria con i valori specificati, questo perchè vengono chiamati i costruttori dei campi dell'oggetto.
```cpp
animal() : weight(), speed() {}
```

>Java non si pone questo problema dell'inizializzazione o meno dei campi, in quanto sono tutti puntatori e li inizializza tutti a `NULL`.

Nota che un costruttore di un oggetto che prende in input un altro oggetto dello stesso tipo è un **copy constructor**, il costruttore di sopra potrebbe essere realizzato come segue:
```cpp
// int weight
// double speed
animal() : weight(0), speed(0) {}
```

Il **padre** in C++ è considerato un campo da inizializzare, a differenza di Java dove `super()` deve essere chiamato prima di fare modifiche a `this`, infatti in C++ i campi del padre vanno inizializzati con il suo costruttore:
```cpp
								  // "super"
dog(int w, double sp, bool ped) : animal(w, sp), has_pedigree(ped) {}
```

### Dichiarazione e costruzione
In C++ a differenza di C, <u>non si dichiara</u>, si **costruisce**, infatti pure tipi primitivi come `int` se non specificato chiamano il _default constructor_ che li inizializza a $0$.

È possibile specificare se si vuole allocare l'oggetto nello **stack** oppure nell'**heap**:
```cpp
animal* a1 = new animal(7, 2.34); // alloco nell'heap
animal a2(7, 2.34); // alloco nello stack
```
>Si alloca nell'heap **solo** se c'è la keyword `new`.

>[!Info] Ridefinizione degli operatori
>In C++ è possibile ridefinire gli operatori in quanto nello stack si avranno **valori**, mentre nell'heap **indirizzi**, ha senso quindi modificare il comportamento degli operatori per i valori.
>
>In Java questo non si può fare perchè di base non ha senso dato che tutto è un puntatore è l'operazione di assegnamento di un puntatore è solo una.

Soltanto i tipi **reference e pointer** subsumono, gli oggetti allocati nello stack, no:
```cpp
animal* a1 = new animal(7, 2.34); // alloco nell'heap
animal a2(7, 2.34); // alloco sullo stack

// copy constructor
animal a3(a2); // allocato sullo stack perchè non c'è la new
a2.eat(*a1);
a2.eat(a3);

dog fido(60, 45.34, false);
animal a5 = fido; // copy constructor
animal& a6 = fido; // nuova reference, non è un copy constructor

a6.eat(a2); // chiama eat di dog 
a5.eat(a2); // eat di animal perchè a5 è un animal

dog* fufi = new dog(1, 100., true);
animal* a7 = fufi;
a7->eat(a2); // chiama eat di dog
```

### Getter e setter
In C++ è sconsigliato l'utilizzo dello stile getter/setter in quanto attraverso l'uso della keyword `const` è possibile fare di meglio.

`const` è una **flag** sul tipo che una volta messa a true fa in modo che non possa più essere passato a metodi non `const`, mentre un tipo non `const` può essere passato sia metodi `const` e non.
```cpp
// read-only (getter)
const int& weight() const { return weight; }
// read-write (getter/setter)
int& weight() { return weight; }
```

La keyword `const` dopo la firma di una funzione non permette di modificare i campi di `this` (oggetto su cui è chiamato il metodo).

### Overload degli operatori
C++ avendo un paradigma **orientato ai valori**, utilizza un sistema di [[Guida a C++#Templates|templates]], ed inoltre ogni operatore è una chiamata a funzione.

```cpp
template <class T>
class matrix {
	matrix<T>& operator=(const matrix<T>& m) {
		cols = m.cols;
		v = m.v;
		return *this;
	}
}
```

È possibile ridefinire gli operatori a proprio piacimento, purchè dopo ne vengano rispettate le firme.

Quello nell'esempio è un operatore di assegnamento **eterogeneo**, ed è detto tale perchè il tipo di _lhs_ (this) è `T`, e lo stesso vale per il tipo di _rhs_.

Viene ritornato `matrix<T>&` per convenzione, in quanto questo consente concatenamento di assegnamenti, ad esempio:
```cpp
m = m2 = m3
```

ciò non sarebbe stato possibile ritornando `void` in quanto il "dezuccheramento" dell'operatore sarebbe stato il seguente:
```cpp
m.operator=(m2.operator=(m3))
// m2.operator=(m3) è OK
// ma m.operator=(void) non è valido
```

### Conversioni
I **costruttori di conversione** vengono utilizzati per convertire i valori _rhs_ di un _operatore qualsiasi_ in un oggetto costruito con i valori _rhs_ (se possibile), lo stesso vale per il passaggio di argomenti alle funzioni; l'utilizzo della keyword `explicit` ne vieta l'utilizzo.
```cpp
class animal {
    int age;
 
public:
    explicit animal(int a) {
        age = a;
    }
};
 
int main() {
    animal a1(10); // Ok
    animal a2 = 10; // No viable conversion
    animal a3 = (animal)10; // Ok con type casting
}
```

È possibile definire dei **copy constructor di "conversione"** passando un tipo diverso da `this`:
```cpp
template <class T>
class matrix {
	template <class S>
	matrix(const matrix<S>& m) : cols(m.get_cols()), v(m.get_rows() * m.get_cols()) {
		for (int i = 0; i < v.size(); i++)
			v[i] = m.v[i]; // m.v deve essere accedibile (pubblico)
	}
}
```
il **chiamante è responsabile**, e deve sapere se la conversione è fattibile.

Gli **operatori di conversione** vengono usati per convertire la classe in cui sono definiti in qualche altro tipo, la sintassi è la seguente:
`operator <toType>() {... return <toType>}`
```cpp
class kilogram {
private:
    double weight;
public:
    kilogram(double w) : weight(w) {}
};

class pound {
private:
    double weight;
public:
    pound(double w) : weight(w) {}
    operator kilogram() const {
        return kilogram(weight * 0.453592);
    }
};

int main() {
    pound p(10.0);
    
	// operatore di conversione
    kilogram k = p;
```

### Iteratori
Gli **iteratori** sono definiti all'interno delle classi e vengono utilizzati per scorrerne il contenuto, per stampare un vector si può procedere come segue:
```cpp
void printVec(vector<int>& v) {
    for (typename vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it;
    }
}

// oppure con "auto"
void printVec2(vector<int>& v) {
    for (auto it = v.begin(); it != v.end(); it++) {
        cout << *it;
    }
}

```

è consigliato usare `typename` prima di un tipo all'interno di una classe templetizzata (come `vector`) per dire al compilatore che si tratta effettivamente di un tipo e non di una variabile. 
>Non tutti gli iteratori sono implementati con i _puntatori_.

