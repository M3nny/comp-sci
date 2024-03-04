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

## Problema del taglio delle aste
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

Possiamo dare una caratterizzazione più semplice al problema usando una sola chiamata ricorsiva:
1. Tagliare un pezzo in modo definitivo
2. Suddividere ulteriormente in modo ottimale la parte rimanente

$$\begin{cases}
r_0=0\\
r_n=\max_{1\leq i\leq n}\{\underbrace{p_i}_{\text{prezzo esatto}}+\underbrace{r_{n-i}}_{\text{ricavo ottimale}}\}
\end{cases}
$$
dove $p_i$ sarà il prezzo della parte sinistra che non verrà più tagliata, mentre $r_{n-i}$ sarà il ricavo ottimale della parte destra che eventualmente sarà tagliata (il ricavo massimo potrebbe essere anche dato senza effettuare un taglio).

```
cut_rod(p, n)
	if (n == 0)
		return 0
	else
		q = -1
		for i = 1 to n
			q = max(q, p[i] + cut_rod(p, n-i))
		return q
```

>$q$ è stato inizializzato a $-1$ perchè non possono esserci prezzi negativi, sarebbe dovuto essere $-\infty$ altrimenti.

**Complessità**: $T(n)$ è il numero di chiamate ricorsive di `cut_rod` quando la chiamata viene fatta con il secondo parametro uguale a $n$.

$$T(n)=\begin{cases}1&n=0\\1+\sum\limits_{i=1}^nT(n-i)&n>0\end{cases}$$
poniamo $j=n-i$
$$T(n)=1+\sum_{i=1}^nT(n-i)=1+\sum_{j=0}^{n-1}T(j)$$
Dimostriamo per induzione che $T(n)=2^n$:
**Caso base**: $n=0$, $T(0)=1=2^0$
**Caso induttivo**: assumiamo vero che per $n$ vale $T(n)=2^n$ e lo dimostriamo per $n+1$
$$\begin{flalign}
T(n+1)=1+\sum_{j=0}^{n+1-1}T(j)&=1+\sum_{j=0}^{n-1}T(j)+T(n)\\
&=T(n)+T(n)=2T(n)\\
&=2\cdot2^n=2^{n+1}
\end{flalign}$$
La complessità di `cut_rod` è esponenziale, ovvero $T(n)=2^n$, è anche visibile attraverso l'albero di ricorsione per $n=4$:
![[Albero ricorsione taglio aste.svg]]
**Osservazioni**:
1. Lo stesso problema viene risolto più volte
2. I sotto-problemi _distinti_ sono pochi ($n$)

È possibile usare un approccio dinamico se:
- I sotto-problemi sono un numero polinomiale
- Ciascuno si risolve in tempo polinomiale (data la soluzione dei sotto-problemi)

Vediamo come funzionano i due metodi per applicare una soluzione dinamica:

### Top-down:
- Salva in una struttura dati le soluzioni dei problemi già risolti (_memoization_), questo metodo farà uso della ricorsione
- L'approccio è pressochè identico alla definizione ricorsiva ad eccezione di un controllo in più e della divisione in due funzioni: quella principale che inizializza la struttura dati e quella ausiliaria che fa il lavoro
- Risolve solo i problemi strettamente necessari

```
memoized_cut_rod(p, n)
	Sia r[0,...,n] un nuovo vettore
	for i = 0 to n
		r[i] = -1
	return memoized_cut_rod_aux(p, n, r)

memoized_cut_rod_aux(p, j, r)
	if r[j] < 0
		if j == 0
			r[j] = 0
		else
			q = -1
			for i = 1 to j
				q = max(1, p[i] + memoized_cut_rod_aux(p, j-i, r))
		return r[j]
```

Se viene trovato che $r[i]\geq 0$ vuol dire che il problema è già stato risolto, inoltre l'`if` può essere evitato nella funzione ausiliaria ed essere aggiunto a quella principale.

**Complessità** (analisi aggregata):
una chiamata ricorsiva per risolvere un problema precedentemente risolto termina immediatamente, dunque si giunge al ramo `else` <u>una sola volta</u> per ciascun sotto-problema.

Per risolvere un sotto-problema di dimensione $j$, il `for` effettua $j$ iterazioni, il numero totale di iterazioni del `for` per tutte le chiamate ricorsive della funzione ausiliaria è:
$$\sum_{j=1}^nj=\frac{n(n+1)}{2}=\Theta(n^2)$$
considerando che la funzione principale esegue $n$ iterazioni per inizializzare il vettore, il costo di `memoized_cut_rod` è:
$$T(n)=\Theta(n)+\Theta(n^2)=\Theta(n^2)$$
### Bottom-up:
- Ordina i sotto-problemi da quelli più piccoli a quelli più grandi e memorizza le soluzioni ottenute, questo metodo non userà la ricorsione
- Utilizza una sola funzione, l'approccio non è uguale a quello definito ricorsivamente in quanto si raggiungerà la soluzione tramite il semplice uso dell'iterazione
- Risolve tutti i sotto-problemi

```
bottom_up_cut_rod(p, n)
	Sia r[0,...,n] un nuovo vettore
	r[0] = 0
	for j = 1 to n
		q = -1
		for i = 1 to j
			q = max(q, p[i] + r[j-i])
		r[j] = q
	return r[n]
```

**Complessità**:
$$\sum_{j=1}^n\Theta(1)\cdot j=\Theta(1)\cdot\frac{n(n+1)}{2}=\Theta(n^2)$$

>[!Tip]
>L'ordine di grandezza di top-down e bottom-up non cambia, tuttavia in questo caso specifico è più efficiente quello bottom-up in quanto anche il top-down risolve tutti i sotto-problemi, ma a differenza sua, bottom-up è iterativo il che lo rende migliore.

#### Posizione dei tagli
Al momento abbiamo $r[0,...,n]$, il cui $i$-esimo elemento memorizza il ricavo massimo per il problema di dimensione $i$, ci serviremo ora anche di $s[1,...,n]$ il cui $i$-esimo elemento memorizzerà la posizione del primo taglio che determina la soluzione ottima per il problema di dimensione $i$.

```
pos_bottom_up_cut_rod(p, n)
	Siano r[0,...,n] e s[1,...,n] due nuovi vettori
	r[0] = 0
	for j = 1 to n
		q = -1
		for i = 1 to j
			if q < p[i] + r[j-i]
				q = p[i] + r[j-i]
				s[j] = i
		r[j] = q
	return r, s
```

La **complessità** è sempre $T(n)=\Theta(n^2)$.

Per visualizzare la sequenza dei tagli definiamo la seguente funzione:
```
print_cut_rod_solution(p, n)
	r, s = pos_bottom_up_cut_rod(p, n)
	while n > 0
		print(s[n])
		n -= s[n]	
```

L'algoritmo stampa il taglio ottimo per un'asta di lunghezza $n$, dopo l'esecuzione di `pos_bottom_up_cut_rod`, considerando i valori nella tabella iniziale, otteniamo il seguente vettore $s$:

|  $i$   |  1  |  2  |  3  |  4  |  5  |  6  |  7  |
|:------:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
| $s[i]$ |  1  |  2  |  3  |  2  |  2  |  6  |  1  |

Supponendo di avere la lunghezza iniziale $n=7$, abbiamo che $s[7]=1$, per cui sappiamo che il primo taglio verrà eseguito nella posizione $1$, la lunghezza restante è pari a $7-1=6$, $s[6]=6$ questo vuol dire che dobbiamo conservare l'asta nella sua lunghezza attuale, dopo questo taglio la lunghezza è pari $0$ e non c'è più nulla da tagliare.

La sequenza di taglio $1,6$ è proprio una soluzione ottimale che avevamo trovato inizialmente, la quale ritorna un ricavo di $18$.

La **complessità** è data dal ciclo `while` sommato alla funzione `pos_bottom_up_cut_rod`, ovvero $T(n)=O(n)+\Theta(n^2)=\Theta(n^2)$.
