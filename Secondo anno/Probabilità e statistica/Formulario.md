**Distribuzione binomiale**:
$$\boxed{P[A_k]=\binom{n}{k}p^k(1-p)^{n-k}}$$
```R
dbinom(k, n, p) # Funzione di densità
pbinom(k, n, p) # Funzione di ripartizione
```

- $n$: numero di estrazioni
- $k$: numero di successi desiderati
- $p$: probabilità di successo
- $\binom{n}{k}$: tutti i modi di estrarre $n$ elementi da una popolazione di $k$ elementi
- $(1-p)$: probabilità di insuccesso

**Distribuzione ipergeometrica**:
$$\boxed{\mathbb{P}[A_k]=\frac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}}$$
```R
dhyper(k, K, N-K, n) # Funzione di densità
phyper(k, K, N-K, n) # Funzione di ripartizione
```

- $N$: dimensione della popolazione
- $n$: numero di estrazioni
- $K$: numero di successi nella popolazione
- $k$: numero di successi osservati
- $\binom{K}{k}$: tutti i modi di estrarre $k$ successi da $K$ successi totali
- $\binom{N-K}{n-k}$: tutti i modi di estrarre $n-k$ insuccessi da $N-K$ insuccessi totali
- $\binom{N}{n}$: tutti i modi di estrarre $n$ elementi da una popolazione di $N$ elementi

**Teorema di Bayes**:
$$\boxed{P(A|B)=\frac{P(B|A)P(A)}{P(B)}}$$
