Il **paradigma funzionale** rende il codice più robusto con meno bug solitamente.
Sebbene Java sia imperativo e class-centrico, da Java 8+ è possibile programmare in maniera **pseudo funzionale**.

### Puntatori a funzione in C
Prima di guardare come Java implementa il suo approccio pseudo funzionale, guardiamo l'approccio di C.

```c
int func(double x) {...}

// main
int(*g)(double) = func;
```

Il nome della variabile che contiene il puntatore alla funzione `func` è `g`, il nome è **immerso nel tipo**, dove il tipo in questo caso è tutto quello a sinistra di `=`.

vediamo come implementare il `for_each`:
```c
void for_each(int* a, size_t len, void(*f)(int)) {
    for (int i = 0; i < len; i++)
	    f(a[i]); // applico la funzione f passata come parametro
}
void print_int(int n) {
	printf("%d\n", n);
}

// main
int A[10] = ...
for_each(A, 10, print_int)
```

Non è possibile però applicare direttamente la funzione `printf` in quanto C non supporta le funzioni lambda.

### Interfacce funzionali in Java
In Java esistono $4$ interfacce per esprimere una funzione:

|                      |                                        Ritorna                                         |                                      Non ritorna                                       |
| :------------------: | :------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------: |
|   **Prende input**   | [Function](https://docs.oracle.com/javase/8/docs/api/java/util/function/Function.html) | [Consumer](https://docs.oracle.com/javase/8/docs/api/java/util/function/Consumer.html) |
| **Non prende input** | [Supplier](https://docs.oracle.com/javase/8/docs/api/java/util/function/Supplier.html) |     [Runnable](https://docs.oracle.com/javase/8/docs/api/java/lang/Runnable.html)      |

Non possono essere espresse tutte con `Function` ritornando `void`, perchè `void` non è un tipo. è solo una keyword che indica che la funzione non ha return statement.
>Volendo è possibile definire una classe vuota `Void` usata per quando si _deve_ ritornare qualcosa ma _non si vuole_ ritornare qualcosa, utile per far valere il polimorfismo.

### Lambda in Java
Le funzioni sono entità del primo ordine, proprio come `int, string, ...` e qualsiasi tipo di oggetto, in quanto le posso manipolare.

Implementiamo la funzione `forEach` utilizzando una nostra interfaccia che imita quella di `Consumer`:
```java
interface MyFunction<T> {
	void apply(T x);
}

public static <T> void forEach(Collection<T> c, MyFunction<T> f) {
	for (T x : c) {
		f.apply(x);
	}
}

// main
List<Integer> l = List.of(1,2,3,4);

// Simulazione lambda con anonymous class
forEach(l, new MyFunction<Integer>() {
	@Override
	public void apply(Integer x) {
		System.out.println(x);
	}
});
```

in questo esempio abbiamo:
- Usato la funzione di ordine superiore `forEach` la quale prende in input un'altra funzione
- Simulato una funzione lambda con una classe anonima

Java però permettere di usare espressioni lambda vere e proprie, facendo riferimento all'esempio precedente chiameremo `forEach` come:
```java
forEach(l, x -> System.out.println(x));
forEach(l, (Integer x) -> System.out.println(x));
```

dove l'intero secondo argomento è una **funzione lambda**.
Non è necessario specificare il tipo di `x`, ma volendo è possibile.

Se volessimo cambiare operazione da fare su ogni elemento di `l` basterebbe cambiare funzione passata a `forEach` oppure cambiare la lambda; se volessimo incrementare di $1$ il valore degli elementi dovremo creare un **side effect** in quanto con `MyFunction` non abbiamo un tipo di ritorno:
```java
// questa funzione incrementa i valori copia nella funzione forEach
// ritornati da iterator
forEach(l, x -> x = x + 1);
```

Se volessimo usare una lambda più complessa che contiene più di una espressione, dovremo usare le grafe `{}`, ad esempio se voglio incrementare l'elemento solo se è maggiore di $5$ procederò come segue:
```java
// questa funzione incrementa i valori copia nella funzione forEach
// ritornati da iterator
forEach(l, x -> {if (x > 5) x = x + 1;});
```

### Ritornare valori - map
Questa volta non vogliamo side effects, bensì vogliamo creare una nuova lista con i valori modificati dalla lambda, creiamo una nuova funzione `map`:
```java
interface Function<A, B> {
	B apply(A x);
}

public static <A, B>
Collection<B> map(Collection<A> c, Function<A, B> f) {
	Collection<B> r = new ArrayList<>();
	for (A x : c) {
		B b = f.apply(x);
		r.add(b);
		// oppure: r.add(f.apply(x));
	}
	return r;
}

Collection<Integer> r1 = map(l2, x -> x + 1);
Collection<Integer> r2 = map(l2, x -> {return x + 1;});
```

volendo è possibile specificare il return, ma non è necessario se si scrive una sola espressione.

Se voglio una lista che mi indica se in posizione `i` l'elemento è positivo o meno scriverò:
```java
Collection<Boolean> r3 = map(l2, x -> x > 0);
```

### Filter
La funzione `filter` permette di ritornare una collezione contenente i soli elementi che rispettano una determinata condizione.

**Filter pura**: crea una nuova collezione e lascia inalterata quella passata in input
```java
public static <T>
List<T> filter(Iterable<T> c, Function<T, Boolean> f) {
    List<T> r = new ArrayList<>();
    for (T x : c) {
		if (f.apply(x))
			r.add(x);
	}
	return r;
}

// main
List<Integer> l = List.of(1,2,3,4,5);

// 00111 => r = 3,4,5
Collection<Integer> r = filter(l, x -> x > 2);
```

è possibile usare anche l'interfaccia [Predicate](https://docs.oracle.com/javase/8/docs/api/java/util/function/Predicate.html) la quale riassume:
`Function<T, Boolean>` in `Predicate<T>`.
Non serve cambiare altro, se non il modo in cui viene chiamata la funzione, ovvero al posto di `apply` si usa `test`, il main rimane invariato.

**Filter impura**: modifica la collezione passata in input
```java
public static <T>
void filterImpure(Iterable<T> c, Function<T, Boolean> f) {
	Iterator<T> it = c.iterator();
	while (it.hasNext()) {
		if (!f.apply(it.next()))
			// rimuove l'ultimo elemento ritornato da next()
			it.remove();
	}
}

// main
List<Integer> l = new ArrayList<>(List.of(1,2,3,4,5));

// 00111 => l = 3,4,5
filterImpure(l, x -> x > 2);
```

in questo caso però è stata usata `ArrayList` in quanto il tipo di lista ritornato da `List.of` è **immutabile**, questo vuole dire che non supporta operazioni come la `remove`.

#### Restrizione dei tipi
Il **tipo in input** (parametro nella firma della funzione) è **più amplio possibile** (più vicino a `Object`) pur sempre considerando le funzioni che si dovranno usare con quel tipo, negli esempi sopra serviva solo l'iteratore.

Il **tipo di ritorno** è solo **un livello di gerarchia verso l'alto**.

>[!Tip]
>Anche volendo non si potrebbe ritornare il container specifico passato in input tramite qualche meccanismo di generics in quanto Java non lo consentirebbe, questo perchè non possiede "il tipo del tipo" ([Kind](https://docs.scala-lang.org/scala3/reference/other-new-features/kind-polymorphism.html)), infatti dovrebbe possedere due tipi di generics, cosa che non ha.


### Trasformazione sintattica delle lambda
Le funzioni lambda in realtà sono **zucchero sintattico**, in quanto esse vengono trasformate in [[Tipi di classi#Anonima|anonymous class]], questo perchè sono state introdotte tardi nel linguaggio.

La trasformazione avviene a **compile time** utilizzando i tipi dedotti della lambda, ovvero:
- Tipo di input della funzione
- Tipo di ritorno

l'unica cosa che non è possibile sapere in modo "assoluto", sono:
- Nome dell'interfaccia con cui costruire la anonymous class
- Nome del metodo da applicare

queste ultime due informazioni **sono ricavate dal contesto** di passaggio.

Ciò porta a situazioni limite di questo genere:
```java
public static <A, B>
Collection<B> map(Collection<A> c, PippoFunction<A, B> f) {...}

// lhs ha tipi diversi con rhs uguali!
Function<Zoo.Dog, Zoo.Cat> f = (d) -> new Zoo.Cat(d.getWeight());
PippoFunction<Zoo.Dog, Zoo.Cat> g = (d) -> new Zoo.Cat(d.getWeight());

// errore
List<Zoo.Cat> cats = map(dogs, f); // usa Function

// corretto
List<Zoo.Cat> cats2 = map(dogs, g); // usa PippoFunction

// corretto
// dezucchera automaticamente e sceglie correttamente PippoFunction 
List<Zoo.Cat> cats3 = map(dogs, (d) -> new Zoo.Cat(d.getWeight())); 
```

Java in pratica dezucchera qualsiasi lambda, purchè sia rappresentabile in una anonymous class, inoltre l'interfaccia usata per costruirla dovrà contenere **solo 1 metodo**, in questa maniera il compilatore saprà per certo il nome del metodo da chiamare all'interno della anonymous class.

