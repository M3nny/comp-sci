Abbiamo già visto come [[Triennale/Secondo anno/Programmazione ad oggetti/Mod. 2/Thread|creare thread in Java]], e abbiamo visto come la keyword `synchronized` permetta:
- Ad ogni oggetto di avere un **mutex implicito**
- Di eseguire eseguire metodi in mutua esclusione
- Ad ogni oggetto di usare `wait(), notify() e notifyall()`

```java
class Contatore {
    private int count = 0;
	
    synchronized void incrementa() {
        count++;
    }
	
    int valore() {
        return (count);
    }
}

public class Interferenze extends Thread {
    static final int MAX = 1000000;
    Contatore c;
	
    Interferenze(Contatore cont) {
        c = cont;
    }
	
    public void run() {
        for (int i = 0; i < MAX; i++)
            c.incrementa(); // metodo in mutua esclusione
    }
	
    public static void main(String args[])
    throws InterruptedException {
        Thread t[] = new Thread[2];
        Contatore cont = new Contatore();
		
        // crea i 2 thread e li esegue
        for (int i = 0; i < 2; i++) {
	        // passa il monitor ai thread
            t[i] = new Interferenze(cont);
            t[i].start();
        }
		
        // attende la terminazione
        for (int i = 0; i < 2; i++) t[i].join();
    }
}
```

In questo codice viene mostrato come due thread possano agire sullo stesso contatore in mutua esclusione.

