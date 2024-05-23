Usato per generalizzare il `coutingSort` principalmente, ma può essere usato anche con altri algoritmi di ordinamento stabili.

**Assunzione**: tutti i numeri sono composti da $d$ cifre, dove quella meno significativa è in posizione $1$, mentre quella più significativa in posizione $d$.

```
radixSort(Array A, int d)
	for i = 1 to d
		ordinamento stabile sulla cifra i (e.g. countingSort)
```

![[Radix sample.svg]]
>La stabilità dell'algoritmo ausiliario è fondamentale affinchè l'algoritmo sia corretto.

### Analisi correttezza
Avviene per induzione sulla colonna da ordinare.

**Caso base**: se $i=1$ ordino l'unica colonna ed ho finito.
**Passo induttivo**: assumiamo che le cifre delle colonne $1,...,i-1$ siano ordinate, dimostriamo che un algoritmo stabile sulla colonna $i$ lascia le colonne $1,...,i$ ordinate.
- Se $2$ cifre in posizione $i$ sono uguali, per la stabilità rimangono nello stesso ordine e per l'ipotesi induttiva sono ordinate
- Se $2$ cifre in posizione $i$ sono diverse, l'algoritmo di ordinamento sulla colonna $i$ le ordina e le mette in posizione corretta
Dunque l'algoritmo è corretto.

### Analisi della complessità
**Lemma**: dati $n$ numeri di $d$ cifre, dove ogni cifra può variare fino a $k$ valori possibili, la procedura `radixSort` ordina correttamente i numeri nel tempo $\Theta(d(n+k))$, se l'ordinamento stabile utilizzato dalla procedura impiega un tempo $\Theta(n+k)$.

**Dimostrazione**:
- Abbiamo dimostrato per induzione la correttezza dell'algoritmo
- Per ogni iterazione, il costo è dato da $\Theta(n+k)$
- Il ciclo `for` compie $d$ iterazioni
- Il costo totale è $\Theta(d(n+k))$
---

Come ripartire le chiavi (i numeri) in cifre?
e.g. word di 32 bit, la spezzo in 4 byte, quindi:
$$b=32\quad r=8\quad d=4$$
con $c_i\in[0,...,2^r-1]$.
**Lemma**: dati $n$ numeri di $b$ bit, ed un intero $>0:r\leq b$, il `radixSort` ordina correttamente questi numeri in tempo:
$$\Theta\Big(\Big(\underbrace{\frac{b}{r}}_d\Big)\cdot(n+\underbrace{2^r}_k)\Big)$$
se l'algoritmo stabile usato richiede un tempo $\Theta(n+k)$ per input nell'intervallo $[0,...,k]$.

**Dimostrazione**: per $r\leq b$
- Spezziamo ogni numero in $\lceil\frac{b}{r}\rceil$ cifre di $r$ bit ciascuna
- Ogni cifra varia in $[0,...,2^r-1]$
- Applico `countingSort` con $k=2^r-1$
- Ogni passaggio richiede $\Theta(n+k)=\Theta(n+2^r)$
- Esegue $d=\lceil\frac{b}{r}\rceil$ passaggi

Allora il tempo di esecuzione totale è $\Theta\Big(\Big(\frac{b}{r}\Big)\cdot(n+2^r)\Big)$.

Dati i valori di $n$ e $b$, voglio scegliere il valore $r$ con $r\leq b$ che rende minore: $$\Big(\underbrace{\frac{b}{r}}_{r\text{ grande vantaggioso}}\Big)\cdot(n+\underbrace{2^r}_{r \text{ grande svantaggioso}})$$
- Se $b<\lfloor\log n\rfloor$, allora per qualsiasi valore $r\leq b$ si ha che $(n+2^r)=\Theta(n)$.

Scelgo $r$ più grande possibile, ovvero $r=b$, ottenendo:
$$\Big(\frac{\cancel{b}}{\cancel{b}}\Big)\cdot(n+2^b)=\Theta(n)\quad\text{dato che }2^b\text{ sarà sempre }\leq n$$
- Se $b\geq\lfloor\log n\rfloor$, allora scegliamo $r$ che sia massimo sotto la condizione che $n\geq 2^r$, quindi $r=\log n$, ottenendo:
$$\Big(\frac{b}{\log n}\Big)\cdot(n+2^{\log n})=\Theta\Big(\frac{nb}{\log n}\Big)$$

Se $b\leq \log n$, e.g. $b=c\log n$ con $c$ costante, allora i numeri variano in:
$$0,...,2^b-1=0,...,2^{c\log n}-1=0,...,n^c-1$$
Il tempo di esecuzione del `radixSort` è:
$$\Theta\Big(\frac{nc\cancel{\log n}}{\cancel{\log n}}\Big)=\Theta(n)$$

Si deduce che, con un intervallo di cifre: $[0,...,n^c-1]$ con $n$ numeri:
- `countingSort`: $\Theta(n+n^c)=\Theta(n^c)$
- `radixSort`: $\Theta(n)$

---

Segue un `radixSort` che ordina un array di $n$ elementi compresi tra $0$ e $n^4 -1$  utilizzando un cambio di base, in questo caso viene usata come base la lunghezza dell'array, ovvero `A.length` (che sarebbe $n$), ciò significa che in base $n$, i valori saranno tutti lunghi $4$ **cifre** rendendo il range degli elementi minore di quello della lunghezza dell'array, in questo modo viene garantito un ordinamento in tempo lineare.
```
radixSort(array A)
	base = A.length()
    for i = 1 to 4
        countingSort(A, base, i)

countingSort(array A, int base, int i)
    B[1...A.length]
    C[0...base]
    
    for j = 0 to base
        C[j] = 0
	
    for j = 1 to A.length
        C[digit(A[j], base, i)]++
	
	// somme prefisse (crescente)
        for j = 1 to base
            C[j] += C[j-1]
    // somme postfisse (decrescente)
        for j = base-1 down to 0
            C[j] += C[j+1]
	
    for j = A.length down to 1
        B[C[digit(A[j], base, i)]] = A[j]
        C[digit(A[j], base, i)]--
	
    A = B

digit(int x, int base, int i)
    return (x / (base^(i-1))) % base
```