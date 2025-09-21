Durante l'esecuzione possono avvenire vari errori e devono essere gestiti dalla eccezioni.
In java le eccezioni sono "lanciate" `thrown` e possono anche essere estese.

Le eccezioni che può lanciare ogni metodo devono essere **conosciute a compile time**, per questo bisogna specificare sia sul metodo che lancia l'eccezione e sia sul metodo che lo chiama le eccezioni che possono essere lanciate.

```java
public class NegativeSpeedException extends Exception {
	public NegativeSpeedException(double a) {
		super(“Negative speed not allowed: “+a);
	}
}

public class Vehicle {
	private double speed;
	
	/**
	* Accelerate the vehicle by the given amount.
	* @throws NegativeSpeedException
	* the given increase is negative
	* @param a the increase of speed
	*/
	public void accelerate(double a) throws NegativeSpeedException {
		if(a<0) {
			throw new NegativeSpeedException(a);
		}
		this.speed = a;
	}
}
```

Le **eccezioni sono ereditate** dalle classi figlio e vanno commentate opportunamente.

Inoltre secondo il principio di sostituzione, la classe figlio deve "stare all'interno" di quella padre, ovvero non può essere più restrittiva, per cui bisogna tenere conto delle eccezioni passate ai figli.

#### Tipi di eccezioni
Le eccezioni "fondamentali" come: out of memory, segfaults, index out of bounds...
sono chiamate **unchecked** in quanto non bisogna specificarle su un metodo (sarebbe molto verboso) e vanno usate solo quando c'è un errore non recuperabile.
Le eccezioni **checked** invece sono quelle estese da `Exception` (non da `RuntimeException` che è una sua estensione).

#### Catturare le eccezioni
Entrambi i tipi di eccezioni posso essere catturati grazie al blocco `try` che specifica il codice da controllare nel caso lanciasse una eccezione, nel caso venisse rilevata una eccezione viene eseguito il blocco `catch` il quale per buona pratica non dovrebbe mai essere vuoto e non dovrebbe catturare eccezioni generiche.

Con l'utilizzo di `finally` è possibile riportare in uno stato accettabile l'esecuzione del programma.
- Il blocco `finally` è sempre eseguito, indipendentemente dal fatto che ci sia stata una eccezione o meno
- Se il `catch` presenta un return o un lancio di una eccezione, e più tardi nel codice è presente `finally` il quale ritorna un valore o lancia una eccezione, il valore ritornato (o eccezione lanciata) nel blocco `catch` vengono scartati.
```java
int race (Vehicle v1, Vehicle v2, double length) {
	try {
		v1.accelerate(Math.random()*10.0);
		v2.accelerate(Math.random()*10.0);
	} catch(NegativeSpeedException e) {
		System.out.println("This should never happen");
		return -1;
	}
	
	finally {
		v1.fullBreak();
		v2.fullBreak();
	}
}
```

è anche possibile usare solo `catch` o `finally`.

#### Errori
Gli **errori** a differenza delle eccezioni non possono essere recuperati, nel caso una funzione li catturasse dovrebbe rilanciarli a sua volta tramite un `throw new <Exception>` all'interno del `catch` (catena di eccezioni).
Gli errori <u>non devono essere lanciati volontariamente da una funzione</u>.

#### Assertions
Nella fase di testing, viene usato `assert` per verificare che una condizione sia vera.
Di base non sono eseguiti, però possono essere abilitati tramite `java -ea`.
```java
public void accelerate(double a) {
	assert a >= 0;
	...
}
```
