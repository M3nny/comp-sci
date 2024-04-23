[[Guida a C++|C++]] è un linguaggio **fortemente tipato multi-paradigma/multi-stile** con molteplici standard in evoluzione negli anni.

A differenza di [[Guida a Java|Java]], <u>non esiste una visibilità di default</u>.
```cpp
class animal {
private:
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

La keyword `virtual` abilita l'override mettendo il metodo in virtual table abilitando in questo modo il **dynamic dispatching**.

L'**ereditarietà** può avvenire in tre modi in base a come si vuole **subsumere**, in alcuni casi non si vuole che il tipo venga subsunto e quindi ne si limita il polimorfismo (solitamente si usa `public`).
- `public`: le sezioni _public_ e _protected_ della classe padre **rimarranno** _public_ e _protected_ anche nella classe figlio
- `protected`: le sezioni _public_ e _protected_ della classe padre **diventeranno** entrambe _protected_ nella classe figlio
- `private`: le sezioni _public_ e _protected_ della classe padre **diventeranno** entrambe _private_ nella classe figlio

```cpp
class dog : public animal {...}
```

