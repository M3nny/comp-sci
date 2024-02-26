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

// errore di compilazione: Animal non possiede il metodo bark()
// bisogna eseguire il casting a Dog
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

## Eccezioni
Possiamo decidere che tipo di eccezione lanciare in base ad alcuni fattori:
**Checked**:
- Quando avviene è possibile gestirla
- Generalmente avviene poche volte
- Comporta un try-catch ad ogni sua invocazione per sapere se è andata a buon fine
**Unchecked**:
- L'anomalia non è in nostro controllo
- L'anomalia avviene poco spesso
- Non serve dichiarare che si lancia l'eccezione

Inoltre quando usiamo una eccezione _checked_, bisogna estenderla da `Exception` (secondo lo standard), e poi è necessario riportare a cascata sulle funzioni che la chiamano che anch'esse lanciano quel tipo di eccezione.
È possibile estendere anche `RuntimeException` per le eccezioni _unchecked_, però generalmente non è richiesto.

### Oggetti in memoria
Un oggetto occuperà in memoria:
- La somma della dimensione dei suoi campi, dove:
	- Tutti i **reference type** occupano 8 byte (puntatore per architetture a 64 bit)
	- I tipi **primitivi** occupano la loro grandezza rispettiva (e.g. `int`: 4 byte)
- **Virtual table**

>[!Virtual table]
>Java per garantire il dynamic dispatching fa tenere in memoria agli oggetti la propria **virtual table**, la quale contiene tanti puntatori quanti sono i metodi dell'oggetto in questione.

Quando viene chiamata una funzione dell'oggetto, viene eseguita una `jump` all'indirizzo presente nella _virtual table_, così anche in caso di _subsumption_, l'oggetto chiamerà la funzione corretta, questo perchè quando viene passato ad una funzione, assieme ai suoi campi viene passata anche la _virtual table_ con i suoi metodi specifici.

>I costruttori sono fuori dalla virtual table, in quanto gli oggetti non possono essere costruiti polimorficamente, questo significa che a destra dell'operatore di assegnamento viene sempre specificato il tipo.

Quando viene chiamato un costruttore, esso _non inizializza_ i campi, li _riassegna_, infatti i campi vengono inizializzati dal compilatore con il loro valore di default:
- Tipi numerici: `0`
- Booleani: `false`
- Reference type: `null`

