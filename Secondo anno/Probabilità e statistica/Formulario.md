**Distribuzione binomiale**:
$$
\boxed{P[X=k]=\binom{n}{k}p^k(1-p)^{n-k}}\quad
\boxed{\mathbb{E}[X]=np}\quad
\boxed{Var[X]=np(1-p)}
$$
```R
dbinom(k, n, p) # Funzione di densità: P[X=k]
pbinom(k, n, p) # Funzione di ripartizione: P[X<=k]
```

- $n$: numero di estrazioni
- $k$: numero di successi desiderati
- $p$: probabilità di successo
- $\binom{n}{k}$: tutti i modi di estrarre $n$ elementi da una popolazione di $k$ elementi
- $(1-p)$: probabilità di insuccesso
---
**Distribuzione ipergeometrica**:
$$
\boxed{\mathbb{P}[X=k]=\frac{\binom{K}{k}\binom{N-K}{n-k}}{\binom{N}{n}}}\quad
\boxed{\mathbb{E}[X]=n\frac{K}{N}}\quad
\boxed{Var[X]=n\cdot\frac{K}{N}\cdot\frac{N-K}{N}\cdot\frac{N-n}{N-1}}
$$
```R
dhyper(k, K, N-K, n) # Funzione di densità: P[X=k]
phyper(k, K, N-K, n) # Funzione di ripartizione: P[X<=k]
```

- $N$: dimensione della popolazione
- $n$: numero di estrazioni
- $K$: numero di successi nella popolazione
- $k$: numero di successi osservati
- $\binom{K}{k}$: tutti i modi di estrarre $k$ successi da $K$ successi totali
- $\binom{N-K}{n-k}$: tutti i modi di estrarre $n-k$ insuccessi da $N-K$ insuccessi totali
- $\binom{N}{n}$: tutti i modi di estrarre $n$ elementi da una popolazione di $N$ elementi
---
**Distribuzione di Poisson**:
$$
\boxed{\mathbb{P}[X=k]=\frac{\lambda^k}{k!}e^{-k}}\quad
\boxed{\mathbb{E}[X]=\lambda}\quad
\boxed{Var[X]=\lambda}
$$
```R
dpois(k, lambda) # Funzione di densità: P[X=k]
ppois(k, lambda) # Funzione di ripartizione: P[X<=k]
```

- $\lambda$: numero medio di successi
- $k$: numero di successi desiderati
---
**Distribuzione geometrica**:
$$
\boxed{\mathbb{P}[X=k]=(1-p)^{x-1}p}\quad
\boxed{\mathbb{E}[X]=\frac{1}{p}}\quad
\boxed{Var[X]=\frac{1-p}{p^2}}
$$
```R
dgeom(k, p) # Funzione di densità: P[X=k]
pgeom(k, p) # Funzione di ripartizione: P[X<=k]
```

- $k$: numero di fallimenti indipendenti <u>prima</u> del primo successo
- $p$: probabilità di successo
---
**Distribuzione normale**:
$$
\boxed{f(x)=\frac{1}{\sigma\sqrt{2\pi}}e^{-\frac{1}{2}(\frac{x-\micro}{\sigma})^2}}\quad
\boxed{\mathbb{E}[X]=\micro}\quad
\boxed{Var[X]=\sigma^2}
$$
```R
dnorm(k, micro, sigma) # Funzione di densità: P[X=k]
pnorm(k, micro, sigma) # Ritorna la p corrispondente a Z <= k
qnorm(k, micro, sigma) # Ritorna la z corrispondente alla prob. p
```
- $k$: in `pnorm` si riferisce alla $\mathbb{P}[Z\leq k]=?$, in `qnorm` si riferisce a $\mathbb{P}[Z\leq z] = k$
- $\micro$: media
- $\sigma$: varianza
---
**Teorema di Bayes**:
$$\boxed{P(A|B)=\frac{P(B|A)P(A)}{P(B)}}$$
