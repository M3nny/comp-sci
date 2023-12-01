Ogni classe ha **Object** come superclasse, essa rappresenta la classe in cima alla gerarchia.
Esistono alcune operazioni universali che sono possibili con qualsiasi _object_.
#### Equals
Indica se un oggetto è dello stesso tipo di un altro.
```java
Car car1 = new Car(0);
Car car2 = new Car(0);

car1.equals(car2) // true
car1 == car2 // false
```
#### Clone
Esegue una _shallow copy_ dell'oggetto.
```java
o.equals(o) // true (stesso contenuto)
o.clone == o // false (oggetto diverso)
```
#### HashCode
Ritorna l'hashcode dell'oggetto.
```java
x.equals(y) // implica che:
x.hashCode() == y.hashCode()
```

## Collections
Per **collections** si intendono strutture dati, dove in cima alla gerarchia di quest'ultime troviamo gli iteratori.
#### Sets
Rappresentano una collezione senza elementi duplicati, esistono vari tipi di set, ad esempio **HashSet**.
```java
public class Car {
	double speed;
	double fuel;
	FuelType fuelType;
	public void refuel(Set<FuelTank> tanks) {
		 for(FuelTank ft : tanks)
			 this.refuel(ft);
	}
}

Set<FuelTank> tanks = new HashSet<FuelTank>();
tanks.add(t1);
tanks.add(t2); 
tanks.add(t1); // non viene aggiunto nulla
myCar.refuel(tanks);
```

Per ogni collezione è possibile usare gli iteratori, è possibile scorrerne gli elementi tramite un for strutturato come segue: `for (t v1: v2)`, dove `v2` deve essere iterabile.

Un altro esempio di _set_, sono i **TreeSet**, dove gli elementi sono ordinati usando il loro _ordine naturale_ (la classe implementa l'interfaccia `Comparable`) oppure usando dei comparatori.
```java
class FuelTank implements Comparable<FuelTank> {
	private FuelType type;
	private double amount;
	public int compareTo(FuelTank o) {
		if(amount==o.amount)
			return this.type.compareTo(o.type);
		else
			return amount-o.amount;
	 }
}
```

>[!Attention]
>Anche se in un set posso aggiungere solo elementi diversi, è possibile modificare quelli già dentro per essere uguali ad altri elementi all'interno del set.
>
>Problema risolvibile oggetti immutabili o usando tipi particolari di set.
#### String
Le stringhe vengono trattate da java come un array di byte (`final`) immutabile (una volta creato non può essere cambiato), su di esse possiamo fare varie operazioni:
```java
String a = “abc“;
String a1 = new String(“abc“); // altro modo di istanziare una stringa

String b = a + “def“; // "abcdef"
String c = a.concat(“def“); // "abcdef"
String d = c.replace(ʻaʻ, ʻgʻ); // "gbcdef"
String e = c.substring(0, 3); // "abc"
String[] f = c.split(“d“); // {"abc", "ef"}
```

>Stampare un oggetto manderà in output il nome e hashcode di quest'ultimo.

### Wrappers
Per ogni tipo primitivo esiste un wrapper che lo rappresenta, è meno efficiente ma è più strutturato, e consente di convertire un tipo ad un altro.

>Ogni tipo primitivo è un oggetto.