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
forEach(l, x -> x = x + 1);
```

Se volessimo usare una lambda più complessa che contiene più di una espressione, dovremo usare le grafe `{}`, ad esempio se voglio incrementare l'elemento solo se è maggiore di $5$ procederò come segue:
```java
forEach(l, x -> {if (x > 5) x = x + 1;});
```

### Ritornare valori
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

