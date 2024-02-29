La **programmazione dinamica** è una tecnica per progettare algoritmi, si applica quando:
- Il problema si riduce ad un insieme di sotto-problemi più piccoli

Diversamente dal [[Secondo anno/Basi di dati/Mod. 2/Decomposizione|divide et impera]], i sotto-problemi sono **sovrapposti**, questo vuol dire che molti sotto-problemi si ripetono, e nel caso del _divide et impera_ bisognerebbe risolverli ogni volta che ricapitano.

**Idea**: ogni sotto-problema viene risolto una singola volta, viene memorizzata la sua soluzione e la si riutilizza quando si incontra lo stesso problema.

È adatta a **problemi di ottimizzazione**, ovvero problemi che hanno molte soluzioni e se ne vuole scegliere <u>una</u> ottima.

Per sviluppare un algoritmo di programmazione dinamica bisogna:
1. Fornire una caratterizzazione della struttura di una soluzione ottima
2. Dare una definizione ricorsiva del valore di una soluzione ottima
3. Calcolare il valore di una soluzione ottima (top-down, bottom-up)
4. Individuare una soluzione ottima in base alle informazioni calcolate al passo 3

### Problema del taglio delle aste
Un'azienda produce asta d'acciaio e le vende a pezzi:
- Le aste prodotte hanno lunghezza $n$
- Sul mercato i pezzi hanno un prezzo che dipende dalla lunghezza

Si vuole trovare il modo di tagliare le aste tale che il taglio massimizzi il guadagno dell'azienda, considerando che il costo del taglio è irrilevante.

**Input**: un'asta di lunghezza $n$ e una tabella di prezzi $p_i$ con $i\in[1,n]$.
**Output**: <u>un</u> ricavo massimo per un'asta di lunghezza $n$, che si può ottenere tagliando l'asta e vendendo i singoli prezzi.

Tabella prezzi:

| Lunghezza ($p_i$) | 1   | 2   | 3   | 4   | 5   | 6   | 7   |
| ----------------- | --- | --- | --- | --- | --- | --- | --- |
| Prezzo ($i$)      | 1   | 5   | 8   | 9   | 10  | 17  | 17  |

Delle soluzioni ottime, considerando il modo in cui tagliare l'asta seguito dal profitto, sono:
- $2+2+3=18$
- $6+1=18$ 
- $2+3+2=18$
- $...$

Supponendo di tagliare pezzi interi maggiori di zero, in ogni posizione $1,2,3...,n-1$ posso decidere se tagliare oppure no, ogni posizione ha quindi $2$ scelte, il che porta a $2^{n-1}$ possibili combinazioni.

Con il _brute force_ si otterrebbe una complessità esponenziale: $\Theta(2^n)$.

Il ricavo massimo può essere espresso ricorsivamente nel seguente modo, indicando con $r_i$ il ricavo dal taglio in posizione $i$, e con $p$ il prezzo:
$$r_n=\max\{\underbrace{p_n}_\text{Prezzo senza tagli},\space (r_1+r_{n-1}),\space (r_2+r_{n-2}),\space ...,\space (r_{n-1}+r_1)\}$$

Quando, come in questo caso, la soluzione è esprimibile come combinazione di soluzioni ottime di sotto-problemi, si dice che vale la **proprietà della sottostruttura ottima**.
