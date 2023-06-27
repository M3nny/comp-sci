- **Tipo**: insieme di valori sul quale sono definite delle operazioni.
- **Oggetto**: regione della memoria con un _tipo_ associato.
- **Variabile**: oggetto a cui è assegnato un nome.
- **Dichiarazione**: introduce un nuovo nome (e.g. `int a`)
- **Definizione**: una dichiarazione che istanzia la memoria per un oggetto. Nota che la dichiarazione `extern int a` non è una _definizione_ in quanto introduce un nuovo nome che però è allocato altrove.

**Left value**: indirizzo di memoria
**Right value**: valore assegnato all'indirizzo di memoria

- Posso sommare/sottrarre un intero ad un indirizzo di memoria.
- Posso sottrarre due indirizzi di memoria ma non sommarli.

```cpp
const int a = 3; // valore costante
constexpr int b = 3; // valore costante inizializzato a compile time
```

**Invariante del ciclo**: una proprietà delle variabili che è vera prima e dopo ogni esecuzione (e.g. nel trovare il massimo su un array, la variabile max sarà sempre il valore massimo fino a quel punto in cui si è arrivati a scorrere l'array).

**Reference**: indica un altro nome per una variabile, deve essere inizializzata subito.

- **Passaggio per copia**: viene creato un ambiente (distrutto alla fine della funzione) dove vengono allocati in memoria tutti i parametri formali ed il loro valore viene inizializzato valutando i loro parametri effettivi.
- **Passaggio per reference**: non alloco nuovo spazio in memoria, uso direttamente la variabili effettive con un altro nome.

---
##### Vector
- In **C** per passare un'array ad una funzione gli posso solo passare il puntatore al primo elemento, mentre se è dentro ad una struct lo copio tutto.
- In **C++** se non specifico nulla lo passo per copia, altrimenti se uso la reference gli passo solo il puntatore al primo elemento.
**Capacità**: quanti elementi può tenere in memoria (raddoppiata quando viene sforata la capacità massima).
**Size**: quanti elementi sono presenti al suo interno.

---
##### Templates
A differenza della macro in C che sono sostituzioni di testo, i templates (di funzione e di classe) consentono di definire funzioni e classi generiche, inoltre lavorano a livello di compilazione in questo modo il compilatore controlla se il tipo passato al template può essere effettivamente usato.
Ad un template posso assegnare un **tipo di default** ad un template, il quale però può cambiare in base a cosa viene passato effettivamente, mentre se assegno un **valore di default** esso non potrà cambiare tipo, ma solo valore (non-type parameter)

---
### Classi
- Se non esiste un costruttore di copia viene eseguita una shallow copy, problematico nel caso di una delete in quanto dopo che viene eliminato l'ultimo oggetto (quello copiato) elimina anche l'area di memoria dell'oggetto originale.
- Con la dicitura **const** dopo un metodo di classe specifichiamo che quel metodo non altera lo stato della classe.
- Con le **liste di inizializzazione** possiamo allocare in memoria un oggetto direttamente con dei valori al posto di allocarlo e poi inizializzare i valori.
```cpp
// costruttore con lista di inizializzazione
token() : m_value(inf), m_type(0) {}
```

**Idioma pimpl**: Nascondiamo l'implementazione della parte privata della classe su un altro file, questo è possibile perchè sappiamo a compile time quale è la dimensione della classe privata, ovvero un puntatore all'implementazione attuale (i puntatori hanno sempre dimensioni di 8 byte). Inoltre in questo modo se viene modificata la dichiarazione della classe oppure l'implementazione, non bisogna ricompilare entrambi, ma solo la parte modificata.

**Struttura dati astratta**: definisce un insieme di operazioni su un insieme di valori senza specificarne l'implementazione interna, fornisce quindi un'interfaccia generica per lavorare con dati strutturati (e.g. liste, stack, code, alberi...)
