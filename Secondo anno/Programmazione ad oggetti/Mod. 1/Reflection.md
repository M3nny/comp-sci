È possibile usare `<class_name>.class` per ottenere un oggetto che descrive la classe in questione.

Con le librerie `java.lang.reflect` è possibile usare le seguenti classi:
- **Field**: legge, scrive valori, ottiene i modificatori dei campi...
- **Method**: legge la dichiarazione, esegue, può cambiare l'accessibilità con `setAccessible`, ottiene i modificatori dei metodi...
- **Constructor**: elenca i tipi di costruttori

```java
import java.lang.reflect.*;
class Car {
	double speed, fuel;
	Car() {...}
	Car(double fuel) {...}
    void accelerate() {...}
    void fullBreak() {...}
}

// main
Class<Car> c = Car.class;

for(Field f : c.getDeclaredFields())
	System.out.println(f);
// double Car.speed
// double Car.fuel

for(Method m : c.getDeclaredMethods())
	System.out.println(m);
// public static void Car.main(java.lang.String[])
// void Car.accelerate()
// void Car.fullBreak()

for(Constructor t : c.getDeclaredConstructors())
	System.out.println(t);
// Car()
// Car(double)

System.out.println(c.getSuperclass()); // class java.lang.Object
System.out.println(c.getPackage()); // package
```

**Pro**:
- È possibile accedere a componenti sconosciuti a compile time
- È possibile accedere a componenti normalmente non accessibili (contro i principi OO)
**Contro**:
- Molto verbosi
- Possono causare molte eccezioni se non abbiamo ottenuto tutte le informazioni necessarie prima di eseguire un metodo ottenuto tramite reflection (e.g. problemi con la visibilità, parametri errati)

```java
import java.lang.reflect.Method;

class Test {
    private void privateMethod() {
        System.out.println("This is private");
    }
}

// main
Class<?> c = Class.forName("Test");
Object obj = c.newInstance();
Method m = c.getDeclaredMethod("privateMethod");
m.invoke(obj); // java.lang.IllegalAccessException
```

Volendo è possibile anche usare la riflessione sulle [[Annotations|annotazioni]], controllando se sono presenti nel componente tramite `isAnnotationPresent` e poi `getAnnotation`.
```java
import java.lang.reflect.*;
import java.lang.annotation.*;

@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.METHOD)
@interface annotation{
    String description() default "";
}

class Car {
	@annotation(description = "Accelera")
    void accelerate() {...}
}

// main
Class<Car> c = Car.class;

for(Method m : c.getDeclaredMethods()) {
    if (m.isAnnotationPresent(annotation.class)) {
        annotation a = m.getAnnotation(annotation.class);
        System.out.println(m + " descrizione: " + a.description());
    }
}
// void Car.accelerate() descrizione: Accelera

```

>Tutti i componenti (Field, Method, Constructor...) implementano l'interfaccia `AnnotatedElement`.
