A differenza dei commenti, le **annotazioni** vengono prese in considerazione dal compilatore, esse servono a fornire informazioni e ad "aggiungere codice" attorno al componente su cui viene applicata. 
Possono essere applicate a:
- Classi
- Campi
- Metodi e costruttori
- Parametri e variabili locali

Alcuni esempi di annotazioni:
```java
@override
// si assicura che è un ovverride, altrimenti da errore

@deprecated(since="2.0")
// da un warning se viene usato in una versione > 2.0

@SupressWarnings({"warning1", "warning2"})
// non mostra i warning (e.g. "deprecation")
```

### Definizione di una annotazione
Viene usato `@interface` per definire una nuova annotazione, solitamente vengono tutte messe in un file apposito `.java` e poi vengono importate.
```java
<visibilità> @interface <nome> {
	<tipo> <nome_campo>() [default <valore di default>];
} 
```
se un valore di default non è specificato, deve essere assegnato quando si usa l'annotazione in questione.

è possibile <u>annotare le annotazioni</u> per limitarne l'utilizzo **solo su componenti specifici** grazie a `@target`.
```java
@target({
	ElementType.FIELD,
	ElementType.METHOD,
	ElementType.PARAMETER
})
@interface Speed {
	String type() default "km/h";
	boolean forward();
}
```

grazie a `@retention` è possibile specificare la `RuntimePolicy`, ovvero come verrà considerata l'annotazione dal compilatore:
```
@retention(
	RetentionPolicy.<RuntimePolicy>
)
@interface ...
```
- `SOURCE`: documentazione interna, viene ignorata dal compilatore
- `CLASS`: documentazione interna ed esterna, non visibile a runtime
- `RUNTIME`: visibile a runtime, potrebbe modificare il comportamento del programma

#### JUnit test
[JUnit](https://junit.org/)è un framework di testing, il quale possiede delle annotazioni come:
- `@Test`: esegue il metodo solo in fase di testing
- `@BeforeEach`, `@AfterEach`: specifica cosa eseguire prima/dopo ogni test
- `@BeforeAll`, `@AfterAll`: specifica cosa eseguire prima/dopo tutti i test
