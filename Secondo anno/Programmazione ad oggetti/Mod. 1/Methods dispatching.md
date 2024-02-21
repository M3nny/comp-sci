Il pattern con cui si accede ai membri di un oggetto è il seguente:
`<receiver>.<member signature>`.

La risoluzione dei metodi quando è presente l'**overriding** è possibile guardando il tipo dinamico del `receiver` e selezionando l'implementazione del metodo più specifico, ovvero quello della classe più specializzata possibile.

### Dispatch statico vs dinamico
Il **dispatching statico** non permette il polimorfismo in quanto la chiamata è risolta a compile time (dove solo i tipi statici sono conosciuti), mentre nel **dispatching dinamico** la chiamata è risolta a runtime con l'implementazione più specifica.
>I linguaggi OOP si basano sul dispatching dinamico.

Quando i metodi vengono invocati, java prosegue come segue:
1. Viene estratto il tipo dinamico del `receiver`
2. Vengono collezionati tutti i metodi della classe corrente e della superclasse
3. Usa il metodo la quale firma corrisponde con quella chiamata, ovvero:
	- Quello che ha lo stesso nome
	- Quello che ha gli argomenti più simili basandosi sul tipo statico (in caso di overloading)

In presenza di metodi `static`, viene considerato il tipo statico, non dinamico, anche in caso di overriding.
```java
public class Racing {
	public static void foo() {
		System.out.println("Racing 1");
	 }
}
public class Racing2 extends Racing {
	public static void foo() {
		System.out.println("Racing 2");
	}
}

// main
Racing2 racing2 = new Racing2();
racing2.foo(); // "Racing 2"
Racing racing3 = racing2;
racing3.foo(); // "Racing 1"
```
