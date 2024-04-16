I thread in Java creano solamente **side-effects** in quanto utilizzano la quarta forma di lambda: [[Lambda#Interfacce funzionali in Java|Runnable]].

Banalmente un thread è implementato come segue:
```java
public static class MyThread extends Thread {
	@Override
	public void run() {
		while (true) {
			System.out.println("A");
		}
	}
}

public static void main(String[] args) {
	Thread t = new MyThread();
	t.start();
	while (true) {
		System.out.println("B");
	}
	// vengono stampati burst di "A" e "B"
}
```

Dove `start()` creerà un nuovo thread ed eseguirà il suo metodo `run()`, più in specifico, ad ogni nuovo thread viene "forkata" la JVM.

Possiamo eseguire i thread in altri due modi:
```java
public static void loop(String msg) {
	while (true) {
		System.out.println(msg);
	}
}

// anonymous class
Thread t2 = new Thread(new Runnable() {
	@Override
	public void run() {
		loop("A");
	}
});
t2.start();

// lambda
Thread t3 = new Thread(() -> loop("B"));
t3.start();

// lambda senza dare un nome al thread
// non potremmo più interagire con questo thread
// neanche aspettarlo con .join
new Thread(() -> loop("C")).start();
```

## Produttore consumatore
Vediamo di seguito l'implementazione in Java attraverso i [[Monitor|monitor]] del problema del [[Produttore e consumatore|produttore e consumatore]]:
```java
public class ConsumerProducer {
    public static List<Integer> buff = new ArrayList<>();
    
    public static class Producer extends Thread {
        public Producer() {
            super("Producer"); // do un nome al thread
        }
        
        @Override
        public void run() {
            Random rnd = new Random();
            while (true) {
                int n = rnd.nextInt();
                synchronized (buff) {
                    buff.add(n);
                    buff.notify();
                }
            }
        }
    }
    
    public static class Consumer extends Thread {
        public Consumer() {
            super("Consumer");
        }
        
        @Override
        public void run() {
            while (true) {
                synchronized (buff) {
                    if (buff.isEmpty()) {
                        try {
                            buff.wait();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    int n = buff.remove(0);
                }
            }
        }
    }
	
    public static void main(String[] args) {
        Thread p = new Producer();
        Thread c = new Consumer();
        p.start();
        c.start();
		
        try {
            p.join();
            c.join();
        } catch (InterruptedException e) {}
    }
}
```

In Java al posto di usare dei [[Semafori|semafori]], viene usata la keyword `synchronized` la quale crea uno scope per identificare una **sezione critica** riguardante l'espressione contenuta in `synchronized`.

La classe `Object` mette a disposizione i metodi per la sincronizzazione tra thread, quindi qualsiasi oggetto può essere usato per garantire la mutua esclusione, normalmente si indica l'oggetto su cui avverranno le operazioni mutualmente esclusive, ma nulla vieta che si possa istanziare un oggetto qualsiasi da usare come mutex, ad esempio se avessimo fatto:
```java
Object mutex = new Object();
// ...
synchronized (mutex)
```

andrebbe bene lo stesso, l'importante è essere coerenti con l'oggetto che si vuole usare per gestire la sezione critica.

L'oggetto specificato all'interno di `synchronized` è detto **owned** da parte di quello scope, e solo gli oggetti _owned_ potranno usare le direttive di sincronizzazione come `wait` e `notify`.

- **Wait**: aspetta una notify da parte di un altro thread
- **Notify**: sveglia un thread in attesa (arbitrario)

>[!Info]
>In Java viene usato `synchronized` al posto di possibili `lock()` e `unlock()` in quanto il programma potrebbe uscire dallo scope prima di raggiungere l'unlock per svariati motivi, uno tra questi sono le eccezioni.
>
>Infatti viene eseguita l'operazione di "unlock" all'uscita dello scope in automatico.

