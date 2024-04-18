La **firma** di un metodo comprende:
- Nome del metodo
- Numero di parametri
- Ordine dei parametri
- Tipo di parametri

questo vuol dire che **non comprende** neanche il **tipo di ritorno**, ciò rende Java **context-dependent**.

### Co-varianza
La **co-varianza** sul **tipo di ritorno** è <u>generalmente ammessa</u> dai linguaggi di programmazione.

Questo vuol dire che il tipo di ritorno può essere più specifico (o uguale) nella funzione con **override** rispetto a quella originale, ma non è possibile che il tipo ritornato sia più generale del tipo ritornato nella funzione originale.

```java
public static class A {
	public A m() { return new A(); }
}

public static class B extends A  {
	@Override
	public B m() { return this; } // sta covariando assieme a this
}
```

usando la superclasse dei numeri `Number`:
```java
public static class A {
	public Number m() { return 1.3; }
}

public static class B extends A  {
	@Override
	public Integer m() { return 2; }
}

// main
A a = new B();
Number n = a.m();
```

`a` possiede tipo effettivo `B`, il binding ha successo in quanto verrà ritornato un `Integer`, il quale subsume a `Number`.

### Contro-varianza
La **contro-varianza** sul **tipo di ritorno** <u>non è generalmente ammessa</u> dai linguaggi di programmazione, essa consisterebbe nel ritornare un tipo più generale nel metodo con override rispetto a quello del metodo originale. 

```java
public class A {
	public Integer m() { return 1; }
}

public static class B extends A  {
	@Override
	public Number m() { return 2.45; } // illegale
}

public static void main(String[] args) {
	A a = new B();
	Integer n = a.m();
}
```

in questo caso abbiamo che il metodo con _override_ ritorna qualcosa più generale di `Number`, ovvero `Integer` e l'assegnamento non funzionerebbe in quanto si aspetta un `Integer` o qualcosa che può subsumere ad `Integer`, ma ritornando un `Number`, che è più generale, non è possibile.

Questo è il motivo per cui la contro-varianza sul tipo di ritorno è illegale, infatti Java lancia un errore quando il tipo di ritorno è più generale del metodo originale.


La **contro-varianza** sul **tipo dei parametri** è <u>generalmente ammessa</u> dai linguaggi di programmazione, tuttavia **Java non la ammette**, il motivo ha origini storiche:
	inizialmente Java non possedeva i _generics_, e quando li ha introdotti ha dovuto utilizzare degli "accrocchi" (inventati dai creatori di [Haskell](https://www.haskell.org/) ) per farli funzionare, infatti quando trasforma il codice in bytecode, viene eseguita la **type erasure**, ovvero toglie tutti i generics e li sostituisce con il loro **upper bound** (e.g. `<T extends String> => String`), e se non viene esplicitamente dichiarato, verrà usato `Object`.
	Per questo motivo è difficile risalire al tipo originale, infatti non si è voluto implementare questo ulteriore meccanismo.

```java
public class A {
	public void p(List<Integer> l) {...}
	public void p(List<String> l) {...} // overload non valido
	
	// dopo type erasure
	public void p(List l) {}
	public void p(List l) {}
}
```

l'**overload non è valido** in quanto, dopo la _type erasure_ quei tipi sarebbero uguali.

```java
public class A {
	public void p(List<Integer> l) {...}
	public void p(List l) {} // overload non valido
}
```

neanche così andrebbe bene, per lo stesso motivo.

