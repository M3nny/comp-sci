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
## Interfacce
Le classi normalmente possono avere solo una superclasse al massimo, ma se volessimo creare una classe con metodi di sottoclassi diverse, non sarebbe possibile.

Le **interfacce** risolvono questo problema definendo solo le firme dei metodi che vogliamo aggiungere alla nostra sottoclasse tramite `implements`.
```java
interface Loadable {
	public void chargeLoad(double l);
}

interface Printable {
	public void print();
}

class Truck extends Car implements Loadable, Printable {...}
```
Quindi:
- Una classe può estendere al massimo un'altra classe
- Una classe può implementare più interfacce

Da java 8, è possibile, oltre a dichiarare i metodi nelle interfacce, definirli, così da avere una implementazione di default, questo è possibile assegnando `default` ad i metodi interessati nell'interfaccia.
```java
interface Loadable {
	default public void chargeLoad(double l) {...}
}
```

>Implementare delle interfacce che hanno la stessa firma di un metodo dichiarato `default` è proibito dal compilatore.

#### Estendere interfacce
La logica con cui si estendono le interfacce è come quella delle classi.
```java
interface Loadable {
	public void charge();
}

interface LoadableUnloadable extends Loadable {
	public void uncharge();
}
```
