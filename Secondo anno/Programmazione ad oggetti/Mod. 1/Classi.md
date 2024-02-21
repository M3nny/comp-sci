Una **classe** modella oggetti del mondo reale dove:
- I **campi** sono lo **stato** dell'oggetto
- I **metodi** sono le **azioni** che può eseguire e che cambiano lo _stato_ dell'oggetto

Una volta definita la forma di un oggetto (classe) non si può più intervenire sulla sua struttura.
Dopo aver definito la classe possiamo istanziare un oggetto, i quali campi saranno variabili con valori, inizialmente decisi dal **costruttore**.
```java
class Car {
	// Campi
	double speed;
	double fuel;

	Car() { // costruttore
	    speed = 0;
		fuel = 100;
	}
	Car(double fuel) { // costruttore con parametri
	    speed = 0;
		this.fuel = fuel;
	}

    void accelerate() {
        if (fuel > 0) {
            speed += 10;
            fuel -= 10;
        } else {
            System.out.println("Out of fuel");
        }
    }
    void fullBreak() {
        speed = 0;
    }

    public static void main(String[] args) {
        Car car1 = new Car(); // alloco la memoria per l'oggetto
        Car car2 = new Car(50);

        System.out.println(car1.fuel); // 100
        System.out.println(car2.fuel); // 50
    }
}
```

Una istanza di una classe (oggetto) è allocata in memoria grazie all'operatore **new**, il quale:
- Alloca memoria per lo stato dell'oggetto
- Inizializza i campi a zero o null
- Invoca il costruttore (se non ce ne è uno specificato usa quello di default)
- Ritorna un puntatore all'oggetto istanziato
>I campi dell'oggetto sono memorizzati nell'**heap**
## Modificatori
I **modificatori** servono ad aggiungere caratteristiche e sono affiancabili a classi, campi e metodi.

- **Static** consente ai valori di un campo di essere condivisi tra tutte le istanze della classe.
>I metodi marchiati con _static_ posso invocare altri metodi _static_ e interagire solo con valori _static_

**Final** non consente la modifica di un campo dopo che è stato inizializzato la prima volta (sarà il costruttore ad inizializzarli).
```java
class Sample {
	final int final_var;
	static int static_var;

	Sample() {
        final_var = 1;
        static_var = 1;
	}

    public static void main(String[] args) {
        Sample s1 = new Sample();
        Sample s2 = new Sample();

        System.out.println(s1.static_var); // 1
        s1.static_var++;
        System.out.println(s2.static_var); // 2

        s1.final_var++; // cannot assign a value to final variable final_var
    }
}
```

### Aliasing
Quando un'area di memoria può essere visitata tramite più nomi diversi, si parla di **aliasing**, e quando si modifica la memoria usando un nome, essa sarà cambiata anche usando l'altro nome.
```java
import java.util.*;

public class Aliasing {
    public static void main(String[] args) {
        int[] array1 = {1, 2, 3};
        int[] array2 = array1;

        System.out.println(Arrays.toString(array1)); // 1, 2, 3
        System.out.println(Arrays.toString(array2)); // 1, 2, 3

        array2[0] = 10;

        System.out.println(Arrays.toString(array1)); // 10, 2, 3
        System.out.println(Arrays.toString(array2)); // 10, 2, 3
    }
}
```

#### Packages
Le classi possono essere raggruppate in **packages**, i quali possono anche essere combinati tra loro.
- Il nome con cui vengono richiamati deve rispecchiare la loro posizione nel progetto

```java
// File: MyClass.java
package sample.MyClass; // definisco questo package

// File: OtherClass.java
import sample.MyClass.*; // importo tutte le classi del package locato in sample/MyClass
```
