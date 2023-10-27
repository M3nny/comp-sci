Solitamente in java le capsule sono contenute in file `.jar` i quali sono file compressi che contengono i file `.class` ed un file `MANIFEST.MF` il quale specifica alcune informazioni del tipo:
- Versione del manifesto
- Chi ha creato il file jar
Il file jar inoltre può anche essere eseguibile se si specifica dove si trova il metodo main.

Una parte fondamentale per consegnare un buon codice incapsulato è la **documentazione**, **javadoc** è lo standard per documentare le API di una libreria java.
```java
/**
 * Se non specifico nessun tag sto scrivendo la descrizione
 * generale di un metodo/classe/campo
 *
 * @author Me
 * @version 1.3 (specifica la versione della classe, ma si può specificare anche nel manifesto)
 * @since 1.2 (da che versione esiste il metodo/classe/campo)
 * @param tmp (spiega cosa rappresenta una variabile)
 * @return (specifica cosa ritorna una funzione)
 * @throws (specifica che eccezione lancia)
 * @deprecated (se non si usa più. un metodo ad esempio)
 * @requires precondizione
 * @ensures postcondizione
 * @invariant invariante dell'oggetto (non del ciclo)
*/
```

Si dovrebbero documentare: metodi, campi e classi **pubblici** ma solitamente non serve documentare quelli _privati_, mentre per quelli _protected_ dipende da caso in caso.

Per generare la documentazione di un file:
```bash
javadoc <file>
```
