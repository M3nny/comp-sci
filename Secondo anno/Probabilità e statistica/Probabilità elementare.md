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
>
>Conto il numero degli elementi e ne faccio il fattoriale: $P=4!=24$
>
>---
>Calcolare il numero di permutazioni della successione $n=(a,b,a,b,a)$
>
>Il numero di elementi è 5, poi ho 2 elementi che si ripetono:
>- $a$ si ripete 3 volte
>- $b$ si ripete 2 volte
>$$P=\frac{5!}{3!\cdot 2!}=\frac{120}{12}=10$$

## Combinazioni
Finora sappiamo estrarre il numero di sequenze possibili di un insieme prendendo $r$ elementi alla volta, questo ci permette di estrarre anche le sequenze $AL, LA$ ad esempio che contengono gli stessi elementi.

Per estrarre il numero di **sottoinsiemi** (l'ordine non importa e non ci sono ripetizioni) di $r$ elementi da un'insieme di $n$ elementi bisogna procedere diversamente.

>[!Example]
>Quanti sono i _sottoinsiemi_ di 3 lettere dell'insieme di 5 lettere $\{A,B,C,D,E\}$?
>
>Abbiamo $\frac{5!}{(5-3)!}=60$ sequenze diverse con alcune sequenze che contengono gli stessi elementi.
>Il numero di sequenze che contengono gli stessi elementi possono essere calcolate tramite $3!=6$ ed infine per trovare il numero di sottoinsiemi:
>$$\frac{60}{6}=10$$

- Una **combinazione semplice** è quindi un _sottoinsieme_ di $r$ elementi presi alla volta da un insieme $n$.
Il numero di combinazioni semplici di $n$ elementi presi $r$ alla volta è:
$$\frac{n!}{r!(n-r)!}=\begin{pmatrix}n\\r\end{pmatrix}$$
e prende il nome di **coefficiente binomiale** $n$ su $r$.

> Tra l'altro si può anche vedere come $\frac{\text{disp. senza rip di } n}{\text{perm. senza rip. di }r}$

- **Combinazioni con ripetizione**:
$$\frac{(n+r-1)!}{r!(n-r)!}=\begin{pmatrix}n+r-1\\r\end{pmatrix}$$

>[!Example]
>Quante sono le _combinazioni_ anche con ripetizione di 3 lettere dell'insieme di 5 lettere $\{A,B,C,D,E\}$?
>Questa volta non voglio i sottoinsiemi, quindi posso cercare anche le ripetizioni del tipo: $AAA, BBB, CCC, ...$ quindi dovrò sommare al numeratore $r-1$:
>$$\frac{(5+3-1)!}{3!(5-3)!}=420$$
>

## Fenomeni aleatori
Si può pensare al termine **aleatorio** come l'opposto di _deterministico_.

Lo **spazio campionario** ($\Omega$) è l'insieme di tutti i possibili risultati di un fenomeno aleatorio dove un **evento** è un sottoinsieme $A\subset\Omega$, ed i possibili risultati singoli chiamati **singoletti** possono essere visti come insiemi contenenti un solo elemento $\{\omega\}$ detti **eventi elementari**.
Lo spazio campionario $\Omega$ viene anche chiamato **evento certo**.

- **Complementare**: $\overline{A}$ _è vero quando $A$ è falso_ e viceversa
	La negazione di $\Omega$ è l'evento impossibile ovvero $\emptyset$
- **Intersezione**: $A\cap B$ è vero quando _sia $A$ che $B$ sono veri_
- **Unione**: $A\cup B$ è vero quando almeno o $A$ o $B$ sono veri
- **Inclusione**: $A\subset B$ se $A\implies B$
- **Disgiunzione**: $A\cap B=\emptyset$ ovvero $A$ e $B$ non hanno nulla in comune

Una famiglia di eventi si dice **partizione** di $\Omega$ se ogni coppia di eventi della famiglia ha intersezione vuota e l'unione di tutte le partizioni è $\Omega$ stesso.
>[!Example]
>$\{C_1,C_2,C_3\}$ è una partizione di 3 elementi se:
>- $C_1\cap C_2=C_1\cap C_3=C_2\cap C_3=\emptyset$
>- $C_1\cup C_2\cup C_3=\Omega$

Un qualsiasi evento $A$ si può scrivere come unione delle sue intersezioni con gli elementi di una partizione:
![[Partizioni.png]]
$$A=(A\cap C_1)\cup(A\cap C_2)\cup(A\cap C_3)$$
Si può quindi scrivere ogni evento $A$ come unione numerabile delle sue intersezioni con gli elementi di una partizione:
$$A=\bigcup_{i=1}^\infty(A\cap C_i)$$

## Definizione di probabilità
La **probabilità** deve rispettare i seguenti **assiomi**:

1. **Positività**: la probabilità è un valore reale compreso tra $0$ e $1$
$$0\leq\mathbb{P}[A]\leq 1$$
2. **Normalizzazione**: la probabilità dello spazio campionario (o evento certo) è pari a $1$
$$\mathbb{P}[\Omega]=1$$
3. **Additività**: se $A_1,A_2,...$ è una sequenza di eventi incompatibili allora la probabilità dell'unione degli eventi $A_n$ è data dalla somma delle probabilità degli eventi $A_n$
$$\mathbb{P}\left[\bigcup_{n=1}^\infty A_n\right]=\sum_{n=1}^\infty\mathbb{P}[A_n]$$
### Proprietà della probabilità
>[!Interpretazione della probabilità]
>Più $\mathbb{P}[A]$ è vicina a $1$, più ci aspettiamo che l'evento si avveri

- **Complementare**: $\mathbb{P}[\overline{A}]=1-\mathbb{P}[A]$
- **Evento impossibile**: $\mathbb{P}[\emptyset]=\mathbb{P}[\overline{\Omega}]=1-\mathbb{P}[\Omega]=0$
- **Unione**: $\mathbb{P}[A\cup B]=\mathbb{P}[A]+\mathbb{P}[B]-\mathbb{P}[A\cap B]$
- **Partizione** se $C_1,C_2,...$ sono partizioni allora: $\mathbb{P}\left[\bigcup\limits_{i=1}^\infty C_i\right]=\mathbb{P}[\Omega]=1$

>[!Legge della probabilità totale]
>Se $C_1,C_2,...$ sono una partizione di $\Omega$ allora la probabilità di qualsiasi evento $A$ può essere scritta come la somma tra le intersezioni tra $A$ ed ogni partizione $C_i$:
>$$\mathbb{P}[A]=\sum_i\mathbb{P}[A\cap C_i]$$

In uno **spazio campionario finito** possiamo scrivere la probabilità dei singoli elementi di $\Omega=\{\omega_1,...,\omega_n\}$ tramite:
$$p_i=\mathbb{P}[\{\omega_i\}]=\frac{1}{n}$$
per ogni evento $A=\{\omega_1,...,\omega_n\}$ possiamo quindi scrivere:
$$\mathbb{P}[A]=\frac{\text{n° casi favorevoli}}{\text{n° casi possibili}}$$
>[!Attention]
>Questa formula vale solo se gli elementi elementari sono **equiprobabili** (e.g. lancio di un dado equilibrato)

## Popolazioni e sottopopolazioni
Immaginiamo di avere un urna con $N$ palline di cui $m$ hanno la caratteristica che ci interessa, mentre $N-m$ non hanno la caratteristica:
- $\mathbb{P}[\text{successo}]=\frac{m}{N}$
- $\mathbb{P}[insuccesso]=\frac{N-m}{N}=1-\frac{m}{n}$

**Con reinserimento** per ottenere la probabilità di estrarre $k$ palline che hanno la caratteristica devo fare molti conti: caso in cui $k=0$: $\frac{\#A_0}{\#\Omega}$, caso in cui $k=1$: $\frac{\#A_1}{\#\Omega}$ etc...
Per evitare di fare sempre tutti i conti mi basta trovare $\Omega$ e applicare la seguente formula per trovare quale è la probabilità di estrarre $k$ elementi con la caratteristica che voglio:
$$\mathbb{P}[A_k]=\binom{n}{k}\left(\frac{m}{N}\right)^k\left(1-\frac{m}{N}\right)^{n-k}$$
Dove $\binom{n}{k}$ sono tutti i modi ordinare le soluzioni, $\frac{m}{N}$ sono le probabilità di successo mentre $1-\frac{m}{N}$ le probabilità di insuccesso e gli esponenti riguardano la quantità di palline che portano al successo ed all'insuccesso.

**Senza reinserimento** la formula cambia, e si può applicare solo se:
- $n\leq N$: la quantità di palline estratte è minore o uguale a quelle presenti
- $k\leq m$: le palline estratte con la caratteristica desiderata sono minori o uguali rispetto a le palline con la caratteristica totali
- $n-k\leq N-m$: per complemento della condizione precedente abbiamo che gli elementi estratti senza la caratteristica devono essere minori o uguali di quelli totali senza caratteristica

$$\mathbb{P}[A_k]=\frac{\binom{m}{k}\binom{N-m}{n-k}}{\binom{N}{n}}$$

>[!Example]
>Ho un urna con $7$ palline, di cui: $4$ bianche e $3$ nere.
>Quale è la probabilità di estrarre _due_ palline bianche facendo _tre_ estrazioni?
>**Con reinserimento**:
>$$\mathbb{P}[A_2]=\binom{3}{2}\left(\frac{4}{7}\right)^2\left(1-\frac{4}{7}\right)^{3-2}\approx 0.41$$
>**Senza reinserimento**:
>$$\mathbb{P}[A_2]=\frac{\binom{4}{2}\binom{7-4}{3-2}}{\binom{7}{3}}\approx 0.51$$





