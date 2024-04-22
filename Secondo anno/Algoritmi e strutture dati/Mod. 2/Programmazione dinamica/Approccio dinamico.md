La **programmazione dinamica** è una tecnica per progettare algoritmi, si applica quando il problema si riduce ad un insieme di sotto-problemi più piccoli.

Diversamente dal [[Secondo anno/Basi di dati/Mod. 2/Normalizzazione/Decomposizione|divide et impera]], i sottoproblemi sono **sovrapposti**, questo vuol dire che molti sotto-problemi si ripetono, e nel caso del _divide et impera_ bisognerebbe risolverli ogni volta che ricapitano.

**Idea**: ogni sotto-problema viene risolto una singola volta, viene memorizzata la sua soluzione e la si riutilizza quando si incontra lo stesso problema.

- A quali problemi si può applicare?
	È adatta a **problemi di ottimizzazione**, ovvero problemi che hanno molte soluzioni e se ne vuole scegliere <u>una</u> ottima.

- Occorre che questi problemi abbiano due caratteristiche:
	1. Deve disporre di una **sottostruttura ottima**: una soluzione ottima di un problema è una combinazione di soluzioni ottime di sottoproblemi
	2. Presenza di **ripetizione di sottoproblemi**, il quale numero di sottoproblemi distinti deve essere piccolo rispetto al numero di possibili soluzioni

- Se valgono le prime due condizioni, ci sono due possibili approcci:
	1. **Top-down** con _memoization_: si fornisce una soluzione ricorsiva del problema in termini dei sottoproblemi, memorizzando le soluzioni dei problemi già risolti
	2. **Bottom-up**: elenca i sottoproblemi in modo ordinato e li risolve dal più piccolo fino a quello cercato

### Top-down o Bottom-up?
Se per il calcolo della soluzione globale serve <u>risolvere tutti i problemi</u>, si usa **bottom-up** in quanto non essendo una soluzione ricorsiva è più efficiente.
Se invece c'è il bisogno di <u>risolvere solo alcuni sottoproblemi</u>, si usa **top-down** in quanto evita di risolvere sottoproblemi inutili.

Per sviluppare un algoritmo di programmazione dinamica bisogna quindi:
1. Fornire una caratterizzazione della struttura di una soluzione ottima
2. Dare una definizione ricorsiva del valore di una soluzione ottima
3. Calcolare il valore di una soluzione ottima (top-down, bottom-up)
4. Individuare una soluzione ottima in base alle informazioni calcolate
	al passo 3

