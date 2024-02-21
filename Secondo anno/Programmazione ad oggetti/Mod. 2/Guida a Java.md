- **Dichiarazione**: introduzione di un nuovo nome con tipo associato
	`int var;`
- **Inizializzazione**: assegnazione del primo valore ad una variabile
	`var = 1;`
- **Dichiarazione con inizializzazione (binding)**: `int var = 1;`
- **Assegnazione**: cambiare il valore di una variabili già inizializzata
- **Parametri**: nella firma della funzione
- **Argomenti**: passati alla funzione

Esistono principalmente due **paradigmi** di programmazione:
- **Imperativo**: è possibile eseguire l'assegnazione
- **Funzionale**: è possibile solamente usare l'inizializzazione (i cicli si fanno con la ricorsione)

La programmazione ad oggetti è uno **stile**.
## Java
java è un linguaggio imperativo orientato agli oggetti class centrico (il codice è sempre all'interno di una classe).

Ciò che differenzia un linguaggio ad oggetti dagli altri è il **polimorfismo**, uno dei suoi aspetti più importanti è la **sussunzione (subsumption)**, ovvero qualunque oggetto di una data classe $X$, è anche istanza della superclasse $X$.

>[!Tip] Assunzione e sussunzione
>- **Assunzione**: dato un concetto generico ne assumo uno più dettagliato
>- **Sussunzione**: dato un concetto dettagliato ne sussumo uno più generico

Una classe è un **tipo**, una variabile è la locazione di memoria dove verrà istanziato l'**oggetto**.

Tutti gli oggetti vengono passati per **reference**, mentre i tipi primitivi per **copia**.

```java
class Animal {
	protected int weight;
	public Animal(...) {...}
	
	public void eat(Animal a) {this.weight += a.weight;}
}

class Dog extends Animal {
	private boolean pedegree;
	public dog(...) {...}
	
	public void bark() {...}

	@Override
	public void eat(Animal A) {this.weight += a.weight*2;}
}

// Main
Dog fido = new Dog (20, false);
Dog pippo = fido; // fido si chiama anche pippo ora
Animal pluto = new Dog (40, true);

// Animal non possiede il metodo bark()
// errore di compilazione a causa del dispatch statico
pluto.bark();

// viene invocato eat di Dog a causa del dispatch dinamico
pluto.eat(fido);
```

- **Dispatch dinamico** (sul ricevitore): viene chiamata la funzione del tipo dinamico a runtime
- **Dispatch statico** (sui parametri): seleziona il metodo da eseguire guardando il tipo statico a compile time

## JDK
Il **JDK** (Java Development Kit) rappresenta la standard library di Java, di seguito è rappresentata la gerarchia di `ArrayList` tramite **UML** (Unified Modelling Language):

![[UML ArrayList.svg]]
## Generics
```java
// Collection<T>: T è parametro
// Iterable<T>: T è argomento
public interface Collection<T> extends Iterable<T> {...}
```

Se non ci fossero stati i generics, bisognerebbe usare `Object` come parametro per generalizzare una funzione.

Consideriamo `Collection`, se si fosse usato `Object` avremmo potuto metterci dentro di tutto, ma con il `get()` non si saprebbe cosa si è estratto, portando a vari errori di _assunzione_ di tipo.

>`contains(Object o)` di `Collection` è un rimasuglio di java originale che è rimasto senza generics per 10 anni (dovuto quindi alla retro-compatibilità).

