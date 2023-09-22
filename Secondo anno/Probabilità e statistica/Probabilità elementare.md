**Teorema fondamentale del calcolo combinatorio**
Se una scelta può essere fatta in $m_i$ modi diversi, allora le possibilità di scelta totali delle $r$ scelte successive sono date da:
$$\prod_{i=1}^rm_i$$
Con 2 dadi a _sei_ facce le combinazioni possibili sono: $6\cdot 6=36$

---
## Disposizioni
Si dice disposizione una sequenza ordinata di $r$ elementi tra $n$ elementi distinti.

Possiamo distinguere come calcolare il numero di due tipi di disposizioni in un insieme di $n$ elementi prendendone $r$ alla volta:
- **Con ripetizione**:
$$D=n^r$$
- **Senza ripetizione**:
$$D=\frac{n!}{(n-r)!}$$
>[!Example]
>Quante parole lunghe 2 lettere si possono comporre con le lettere appartenenti all'insieme $n=\{I, L, A\}$?
>$D=3^2=9 \Rightarrow II, IL, IA, LI, LL, LA, AI, AL, AA$
>
>---
>Quante parole lunghe 2 lettere _diverse_ si possono comporre con le lettere appartenenti all'insieme $n=\{I, L, A\}$?
>$D=\frac{6}{1}=6 \Rightarrow IL, IA, LI, LA, AI, AL$

## Permutazioni
Si dicono permutazioni tutti i raggruppamenti tali che:
1. Ogni raggruppamento contiene tutti gli $n$ elementi del gruppo originale
2. Gli elementi di ogni raggruppamento hanno ordine diverso

Anche in questo caso possiamo calcolare il numero di due tipi di permutazioni in un insieme $n$:
- **Con ripetizione**: indicando con $n_i$ quante volte si ripete un tipo di elemento $i$
$$P = \frac{n!}{n_1\cdot n_2\cdot ...\cdot n_i!}$$
- **Senza ripetizione**: 
$$P = n!$$
>[!Example]
>Calcolare il numero di permutazioni dell'insieme $n={a, b, c, d}$
>conto il numero degli elementi e ne faccio il fattoriale: $P=4!=24$
>
>---
>Calcolare il numero di permutazioni della successione $n=(a,b,a,b,a)$
>il numero di elementi è 5, poi ho 2 elementi che si ripetono:
>- $a$ si ripete 3 volte
>- $b$ si ripete 2 volte
>$$P=\frac{5!}{3!\cdot 2!}=\frac{120}{12}=10$$
