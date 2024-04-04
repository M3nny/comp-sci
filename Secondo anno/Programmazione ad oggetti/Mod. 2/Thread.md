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

Dove `start()` creerà un nuovo thread ed eseguirà il suo metodo `run()`.
