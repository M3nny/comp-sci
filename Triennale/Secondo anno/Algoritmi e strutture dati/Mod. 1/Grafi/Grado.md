## Grafi non orientati
Dato un grafo _non orientato_ $G=(V,E)$ con $u\in V$:
$$\underbrace{N(u)}_{\text{intorno di }u}=\{v\in V|(u,v)\in E\};\quad\underbrace{\deg(u)}_{\text{grado di }u}=|N(u)|;$$
ovvero: <u>il grado di un nodo è pari alla cardinalità del suo</u> **intorno** ($N$).
![[Grado di un grafo.svg]]
<u>Non è possibile avere</u> $n$ <u>vertici con grado diverso</u>, in quanto $0\leq \deg(u)\leq n-1$, infatti dovrebbe esistere un nodo con grado $0$ ed uno con grado $n-1$, ma questo è assurdo perchè il primo indica che non è collegato con nessun'altro nodo, mentre il secondo indica che è collegato con tutti.

### Lemma della stretta di mano
<u>Vale solo per grafi non orientati</u>:
$$\sum_{u\in V}\deg(u)=2m$$
**Corollario**:
Se $G$ è un grafo non orientato, allora il numero di vertici di grado dispari è pari.

**Dimostrazione**:
Definiamo $P=\{u\in V|\deg(u)\text{ è pari}\}$ e  $D=\{u\in V|\deg(u)\text{ è dispari}\}$, dal lemma della stretta di mano otteniamo:
$$\begin{flalign}
	2m&=\sum_{u\in V}\deg(u)\\
	&=\sum_{u\in P}\deg(u)+\sum_{u\in D}\deg(u)\\
	&=\sum_{u\in P}\underbrace{2\cdot f(u)}_{\text{grado di un numero pari}}+\sum_{u\in D}\underbrace{2\cdot f(u)+1}_{\text{grado di un numero dispari}}\\
	&=2\sum_{u\in P}f(u)+2\sum_{u\in D}f(u)+|D|\\
	&=2\sum_{u\in V}f(u)+|D|\\
	&\implies |D| = 2m-2\sum_{u\in V} f(u)=\underbrace{2(m-\sum_{u\in V}f(u))}_{\text{pari}}
	\end{flalign}
	$$

#### Grafo regolare
$G=(V,E)$ è $k$-**regolare**, se $\forall u\in V$, si ha $\deg(u)=k$, ovvero se tutti i nodi hanno lo stesso grado.

**Proprietà**:
- $2$-regolare $\implies$ $n=m$
- $3$-regolare $\implies$ $n$ è pari
- $4$-regolare $\implies$ $m$ è pari

## Grafi orientati
Il concetto di grado **cambia nei grafi orientati**, innanzitutto distinguiamo:
- **in-degree**: numero di archi entranti nel nodo
- **out-degree**: numero di archi uscenti dal nodo
$$\underbrace{\text{in-deg}(i)=\sum_{j=1}^na_{ji}}_\text{somma colonna i}\quad \underbrace{\text{out-deg}(i)=\sum_{j=1}^na_{ij}}_\text{somma riga i}$$
inoltre la somma degli archi entranti è uguale alla somma degli archi uscenti:
$$\sum_{i=1}^n\text{in-deg}(i)=\sum_{i=1}^n\text{out-deg}(i)=m$$
