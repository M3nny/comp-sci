Possiamo **specializzare** gli oggetti **estendendone** le loro funzioni grazie al polimorfismo.

<u>Una classe può avere solo un padre, ma un padre può avere più figli.</u>
La classe specializzata potrà **sovrascrivere i metodi** della classe padre (superclasse) per adattarli alla sua specializzazione oppure potrà **aggiungerne di nuovi**, lo steso vale con i campi.

Per prima cosa il costruttore della classe figlio deve **chiamare il costruttore della classe** padre tramite `super()`.
Inoltre per usare metodi/campi della classe padre bisogna precederli con `super.` il quale è analogo a `this.` della classe attuale.

Un figlio può accedere oltre ai campi _public_ del padre anche a quelli _protected_ (vedi [[Information hiding#Modificatori di accesso|modificatori di accesso]])
### Classi astratte
Sono **classi che non implementano tutti i metodi che dichiarano**, non possono essere istanziate, però i figli possono completare tutti i metodi mancanti ed essere istanziati, nel caso non li implementassero tutti, allora devono anch'essi essere astratti.

```java
abstract public class Vehicle {
	protected double speed;
	abstract public void accelerate (double a);
	
	public Vehicle (double speed) {
		this.speed = speed;
	}
}

public class Car extends Vehicle { // eredita da Vehicle
	private FuelType fuelType;
	private double fuel;
	
	public Car(double speed, FuelType fuelType, double fuel) {
		super(speed); // costruttore del padre
		this.fuelType = fuelType;
		this.fuel = fuel;
	}

	public void accelerate(double a) {
		super.speed += a; // campo del padre
		this.fuel -= a * fuelType.fuelConsumption;
	}
}
```

### Overriding
Se un metodo della sottoclasse è **uguale** ad un metodo della classe padre, si parla di **overriding**, è comunque possibile chiamare il metodo originale del padre all'interno della classe figlio tramite `super.method()`.

```java
public class Vehicle {
	protected double speed;
	public void accelerate (double a) {
		this.speed += a;
	}
}

public class Car extends Vehicle {
	public void accelerate (double a) {
		super.accelerate(a); // chiamo la funzione del padre
		this.fuel -= a * fuelType.fuelConsumption;
	}
}
```

I <u>modificatori d'accesso non fanno parte della firma del metodo</u>, questo significa che si può allargare o diminuire la visibilità di un metodo quando si esegue l'overriding.
>I metodi **final** e **static**, <u>non possono essere sovrascritti</u>.
### Overloading
Parliamo di **overloading** quando un metodo di una classe ha lo **stesso nome** ma parametri e/o valore di ritorno diverso.

```java
public class Vehicle {
	public void accelerate (double a) {
		this.speed += a;
	}
	
	public int accelerate () { // overloading di accelerate
		this.speed += 100;
		return 1;
	}
}
```

### Classi e metodi final
A differenza dei campi `final` ai quali si può assegnare un valore solo una volta, le classi `final` **impediscono di essere estese**, mentre i metodi `final` **impediscono di essere sovrascritti**.

I **costruttori** ed i metodi `abstract`, <u>non possono essere preceduti</u> da `final`.

### Riassunto sui modificatori
|          | Class | Field | Method | Static | Final | Abstract |
| -------- |:-----:|:-----:|:------:|:------:|:-----:|:--------:|
| Static   |  ❌   |  ✅   |   ✅   |        |       |          |
| Final    |  ✅   |  ✅   |   ✅   |   ✅   |       |          |
| Abstract |  ✅   |  ❌   |   ✅   |   ❌   |  ❌   |          |
- **Static**:
	- **Field**: il campo è condiviso tra tutte le istanze della classe
	- **Method**: permette al metodo di essere chiamato anche senza nessun oggetto istanziato
- **Final**:
	- **Class**: la classe non può essere estesa
	- **Field**: il campo dopo essere stato inizializzato è read-only
	- **Method**: non si può eseguire l'override del metodo
- **Abstract**: 
	- **Class**: una classe che non può essere istanziata, ma solo estesa
	- **Method**: un metodo con solo la firma, può essere implementato dalle classi figlio 

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