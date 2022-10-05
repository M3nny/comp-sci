# Insiemi
Un insieme è una collezione **non ordinata** di **elementi** distinti.

- Se un insieme è grande lo posso **descrivere** come <u>elementi che soddisfano una proprietà</u> che risulta essere vera per ogni elemento all'interno dell'insieme, possiamo quindi rappresentarli in maniera descrittiva:
  $$w=\{n\in \mathbb{N}| n \text{ è multiplo di 11}=\{11,22,33,...\}$$
  Possiamo indicare con:
  - $\mathbb{X}^+$ gli elementi positivi di $\mathbb{X}$.
  - $\mathbb{X}^-$ gli elementi negativi di $\mathbb{X}$.
  - $\mathbb{X}^{\geq}$ gli elementi non negativi di $\mathbb{X}$ (zero compreso).

Due insiemi **si dicono uguali** se hanno gli **stessi elementi**, <u>non importa l'ordine</u>.

## Appartenenza
L'appartenenza di un elemento ad un insieme viene scritta come:
$$x\in \mathbb{X} \quad 3\in\{0,1,2,3\}$$
Mentre se non appartiene:
$$3\notin \{0,1,2\}$$

## La cardinalità
- La cardinalità di un insieme è il numero di elementi al suo interno e viene indicata con $|A|$.
- Diciamo che un insieme è finito quando $|A|$ è un numero naturale.

## Coppie, triple, ..., ennuple
- Una coppia si scrive con parentesi tonde $(1,2)$ e l'ordine in questo caso è importante: $(1,2) \neq (2,1)$.
- Possiamo mettere anche delle coppie all'interno di un'insieme:
$$S_1=\{(x,y)|x<y\}=\{(1,2),(3,7),(1,5)\}$$

## Prodotto cartesiano
Il prodotto cartesiano di due insiemi viene descritto come:
$$X\times Y=\{(x,y): x\in X \land y \in Y\}$$
Quando si ha il prodotto con un insieme e se stesso, come nel caso del **piano cartesiano** si ottiene:
$$\mathbb{R}\times \mathbb{R}=\mathbb{R}^2$$
La cardinalità di un prodotto cartesiano è uguale al prodotto delle cardinalità degli insiemi coinvolti: $X\times Y = |X|\cdot |Y|$.

Per indicare il prodotto di $n$ insiemi di $A_i$ (più prodotti con se stesso) possiamo usare la seguente forma:
$$\Uppi_{i=1}^nA_i$$
Il quale avrà cardinalità $|A|^n$.

## Insiemi particolari

### Insieme vuoto
- L'**insieme vuoto** non contiene elementi ed ha cardinalità 0.
- Può essere definito dalla proprietà: $\emptyset=\{x:x\neq x\}$.

### Singleton
- Un insieme composto da **un solo elemento** (quindi con cardinalità 1) è chiamato **singleton**.

### Insieme delle parti
- L'insieme delle parti è l'insieme di tutti i sottoinsiemi di $A$ e si indica con $\mathcal{P}(A)$.
>[!Example]
>**Esempio 1**
>Se $A=\{0,1\}$ allora
>$$\mathcal{P}(A)=\{\emptyset, \{0\},\{1\},\{0,1\}\}$$
>
>**Esempio 2**
>![[Parti contenuto.png]]
- La **cardinalità dell'insieme delle part**i se $|A|=2$ allora $|\mathcal{P}(A)|=2^2=4$.
$$\text{Se } |A|=n \text{ allora} |\mathcal{P}(A)| = 2^n$$

## Relazioni

### Contenuto o uguale
$$A\subseteq B \quad \iff \quad x\in A\implies x\in B$$
$$A\subset B \implies A\neq B$$
- L'insieme vuoto è contenuto in ogni insieme.

### Unione
$$A\cup B = \{x|(x\in A) \lor (x\in B)\}$$
Per trovare la cardinalità di insiemi uniti proseguiremo nel seguente modo:
$$|A\cup B| = |A|+|B|-|A+B|$$
- **Intersezione**: $A\cap B = \{x|(x\in A) \land (x\in B)\}$.
- **Complementazione**: $B\setminus A=\{x|x\in B \land x \notin A\}$, dove l'insieme complementare si indica con $\overline{A}$.
- **Differenza simmetrica**: $A \Delta B = (A/B)\cup (B/A)$ 
![[Differenza simmetrica.png]]

## Proprietà delle operazioni sugli insiemi
>[!Info]
![[Idempotenza.png]]
![[Assorbimento.png]]
![[Commutativa.png]]
![[Associativa.png]]
![[Distributiva.png]]
![[Complementazione.png]]
![[De morgan.png]]

## Partizione
Dato un insieme $X$ ed una famiglia $A_1, A_2, ..., A_k$ di sottoinsiemi <u>non</u> vuoti di $X$, diciamo che gli insiemi $A$ formano una partizione se:
- L'**unione** di tutti i sottoinsiemi da come risultato l'insieme padre
$$A_1\cup A_2 \cup ... A_k=X$$
- L'**intersezione** di qualsiasi sottoinsieme con un altro da origine all'insieme vuoto (praticamente devono avere elementi in comune i sottoinsiemi)
$$A_i\cap A_j=\emptyset \text{ per ogni i,j }\in \{1, ..., k\}$$



