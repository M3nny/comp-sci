Java è un linguaggio fortemente "tipato", dove i tipi dei campi, parametri... sono conosciuti a compile time, si dice quindi che è **statically typed**.
### Principio di sostituzione
Si può usare una istanza della superclasse come istanza della sottoclasse, ovviamente se la sottoclasse ha metodi in più, non potranno essere chiamati.

```java
int race (Vehicle v1, Vehicle v2, double length) {
	v1.accelerate(Math.random()*10);
	v2.accelerate(Math.random()*10);
}

// Main
race(new Car(), new Car());
race(new Truck(), new Truck());
race(new Car(), new Truck());
```
Ogni sottoclasse avrà il suo modo di accelerare, e anche la quantità di accelerazione potrà essere diversa.

Una estensione di una classe è anche detto **sottotipo**, in quanto fornisce una **interfaccia più ampia** dato che tutte le occorrenze della classe padre possono essere sostituite dal figlio.

### Polimorfismo
Dopo aver visto i concetti di **ereditarietà** e **subtyping**, possiamo affermare che la stessa classe ha comportamenti diversi, come nell'esempio riportato di sopra, ogni `Vehicle` può essere un sottotipo della classe `Vehicle`, per cui potrà avere dei metodi sovrascritti che si comportano in modo diverso.

### Tipi statici e dinamici
- I tipi **statici** sono determinati a compile tipe
- I tipi **dinamici** sono determinati durante l'esecuzione

```java
Car c = new Car(); // static == dynamic type
Vehicle v = new Car(); // dynamic subtype
```
Nel primo caso il tipo statico corrisponde con il tipo dinamico, nel secondo caso il tipo statico è una superclasse del tipo dinamico.

Non è possibile fare il contrario però, ovvero:
```java
Car v = new Vehicle(); // sbagliato
```

è possibile inoltre eseguire il **casting** <u>da un tipo ad un suo sottotipo</u>, tramite:
```java
Vehicle v = new Car();
Car c = (Car) v;
```

Per controllare il tipo dinamico, si usa `instanceof`, il quale ritornerà `true` sse, il tipo dinamico dell'espressione è un tipo (o sottotipo) del tipo dato.
```java
Vehicle v = new Car();
if (v instanceof Car) {...}

Car c = new Car();
if (c instanceof Vehicle) {...} // non ha senso, è sempre vero

if (c instanceof Bicycle) {...} // proibito, sempre falso
```

---
## Generics
I tipi generici ci permettono di usare metodi e classi, con il tipo che passiamo al template (vedi [[Guida a C++#Templates|templates in C++]]).

```java
public class HashMap<K, V> {
	public V get(K key) {...}
	public V put(K key, V value) {...}
}

public class FuelTypeCache {
	Hashmap<String, FuelType> map = ...;
	FuelType getFuelTypeFromName(String n) {
		return map.get(n);
	}
}
```

I tipi generici in java sono **invarianti**, ovvero non si può assegnare un espressione con un tipo generico ad un avariabile con un tipo generico diverso (anche se è sottotipo dell'altro).

Non è necessario passare esplicitamente il tipo generico quando si istanziano classi o quando vengono chiamati metodi generici, questo perchè il tipo viene dedotto.
```java
public class List<V> {
	public void add (V el) {...}
}

// main
List<Vehicle> v1 = new List<>();
v1.add(new Cat(...));
```

Potremmo volere restringere il tipo di dato possibile, questo è possibile aggiungendo `extends` accanto al tipo generico nella dichiarazione del metodo, così facendo solo i sottotipi del tipo da cui estende sono permessi, inoltre ora possiamo usare tutte le componenti della classe padre da cui estende.

```java
<T extends Vehicle> T race(T v1, T v2, double length) {...}
```
