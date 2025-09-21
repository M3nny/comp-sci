### Componente connessa
Dato un grafo $G=(V,E)$, una **componente connessa** di $G$ è un sottoinsieme di vertici $V'$ tale che:
- Il sottografo indotto $G[V']$ è connesso
- La componente connessa non deve appartenere ad un'altra più grande, ovvero $V'$ non è contenuto in nessun insieme di vertici che induca ad un sottografo connesso

Un esempio è il seguente grafo, il quale contiene $3$ componenti connesse:
![[Componenti connesse.svg]]
**Proprietà**: l'insieme delle componenti connesse di un grafo formano una [[Gli insiemi#Partizione|partizione]] di $V$.

---
### Condizione necessaria per la connettività
Se $G$ è [[Tipologie#Grafo Connesso|connesso]] allora è **necessario** (ma **non sufficiente**) che:
$$|E|\geq |V|-1$$
**Dimostrazione per induzione su** $n=|V|$:
**Caso base**: prendendo in considerazione un singolo vertice senza archi, si ha:
- $|E| = 0$
- $|V| = 1$
risulta essere vera la proprietà
**Passo induttivo**: assumiamo che valga fino a $n-1$ e lo dimostro per $n$:

Indichiamo con $z\in V$ un nodo da togliere da $G$, otteniamo il seguente grafo indotto: $G'=G[V\setminus \{z\}]$.

Dopo aver tolto $z$, $G'$ potrebbe essere connesso oppure no, in base a quale nodo togliamo, per cui l'ipotesi non può essere applicata interamente, e non sapendo il numero di componenti connesse $k$ di $G'$, applichiamo l'ipotesi induttiva su tutte.

Indicando con $E_i$, $V_i$ il numero di archi e vertici della $i$-esima componente connessa, vogliamo dimostrare che $|E_i|\geq |V_i|-1$:
$$\begin{flalign}
|E|&=\sum_{i=1}^k(\underbrace{|E_i|}_{|V_i|-1})+\underbrace{\deg(z)}_\text{archi del nodo rimosso}\\
&\geq\sum_{i=1}^k(|V_i|-1)+\deg(z)\quad\text{(maggiorazione)}\\
&=\sum_{i=1}^k(|V_i|)-k+\deg(z)\\
&= |V|-1+\deg(z)-k
\end{flalign}$$
Nell'ultima riga viene scritto $-1$ per via di $z$ che non appartiene a $G'$ in quanto viene tolto.

La dimostrazione finisce se riusciamo a dimostrare che $\deg(z)-k\geq 0$.
Abbiamo però che $\deg(z)\geq k$ di sicuro in quanto il grafo inizialmente era connesso, quindi $z$ aveva _almeno_ un arco che lo collegava a tali componenti connesse, per cui dato che $\deg(z)-k$ è $\geq 0$, otteniamo:
$$\begin{flalign}
|E|&\geq|V|-1+\deg(z)-k\\
&\geq|V|-1
\end{flalign}$$

### Condizione sufficiente per la connettività
La condizione precedente non è sufficiente per dimostrare che un grafo è connesso.
Una condizione **sufficiente** per la connettività è la seguente:
$$\forall u\in V,\space \deg(u)\geq\frac{n-1}{2}$$

**Dimostrazione per assurdo**:
Assumiamo che $G$ sia un grafo **non connesso** e che abbia (per semplicità) un numero di componenti connesse (cc) $\geq 2$, indichiamo con $V_1$ e $V_2$ due cc di $G$, abbiamo che $n=|V|\geq |V_1|+|V_2|$, ed indichiamo: $n_1=|V_1|$ e $n_2=|V_2|$.

Prendendo un $u_1\in V_1$ si avrà $\deg(u_1)\geq \frac{n-1}{2}$, all'interno di $V_1$ la cardinalità dei vertici è la seguente: $|V_1|\geq\frac{n-1}{2}\underbrace{+1}_{u_1\text{ stesso}}=\frac{n+1}{2}$, e possiamo dire lo stesso della seconda cc, ovvero: $|V_2|\geq\frac{n-1}{2}\underbrace{+1}_{u_2\text{ stesso}}=\frac{n+1}{2}$.

Abbiamo quindi:
$$\begin{flalign}
|V|&\geq|V_1|+|V_2|\\
&\geq\frac{n+1}{2}+\frac{n+1}{2}\\
&\geq n+1
\end{flalign}$$
ma questo è assurdo, non è possibile che $|V|=n\geq n+1$.

---
### Condizione necessaria per l'aciclicità
A differenza dei grafi _connessi_, i quali devono essere abbastanza [[Triennale/Secondo anno/Algoritmi e strutture dati/Mod. 1/Grafi/Introduzione#Densità|densi]], i grafi **aciclici** devono avere un numero ridotti di archi, infatti se ne avessero troppi si presenterebbero dei cicli.

Se $G$ è **aciclico**, allora deve essere vero:
$$|E|\leq |V|-1$$
**Dimostrazione per induzione su** $n=|V|$:
**Caso base**: per $n=1$ risulta essere vera perchè $|E|\leq 1-1$.
**Passo induttivo**: sia $z$ un nodo da togliere da $G$, si consideri il grafo indotto $G[V\setminus\{z\}]=G'$, chiamiamo $k$ il numero di cc di $G$ indicate da $V_1,...,V_k$.

Essendo le cc sottografi di $G$, il quale è _aciclico_, allora anche esse saranno acicliche.
Applicando l'ipotesi induttiva sulle cc otteniamo: $|E_i|\leq |V_i|-1\space\forall_{i,...,k}$.
$$\begin{flalign}
|E|&=\sum_{i=1}^k(|E_i|)+\deg(z)\\
&\leq\sum_{i=1}^k(|V_i|-1)+\deg(z)\\
&\leq\sum_{i=1}^k(|V_i|)-k+\deg(z)\\
&\leq |V|-1+\deg(z)-k
\end{flalign}$$

Dobbiamo dimostrare che $\deg(z)-k\leq 0$ per verificare la proprietà, ovvero: $\deg(z)\leq k$.

Se $\deg(z)$ fosse maggiore di $k$ però si avrebbero più archi di quante sono le componenti connesse, formando così un ciclo, che è assurdo, quindi:
$$\begin{flalign}
|E|&\leq|V|-1+\deg(z)-k\\
&\leq|V|-1
\end{flalign}$$

### Riflessioni sui grafi complementari
Sulla base che $G$ sia connesso oppure no, possiamo avere le seguenti combinazioni con $\overline{G}$ (ovvero il suo [[Tipologie#Grafo complemento|complementare]]):

|     | $G$         |            | $G'$        |       |
| --- | ----------- | ---------- | ----------- | ----- |
| 1.  | Connesso    | $\implies$ | Connesso    | Falso |
| 2.  | Connesso    | $\implies$ | Disconnesso | Falso |
| 3.  | Disconnesso | $\implies$ | Connesso    | Vero  |
| 4.  | Disconnesso | $\implies$ | Disconnesso | Falso |

1. Se $G$ è connesso, il suo complementare potrebbe non esserlo, basti pensare ad un grafo completamente connesso, il suo complementare sarà vuoto.
2. Considerando il grafo circolare $C_5$ e $\overline{C_5}$ possiamo notare come entrambi siano connessi, quindi l'implicazione è falsa
![[Grafi isomorfi pentagono.svg]]
3. Supponendo di avere $k$ componenti connesse, abbiamo tre casi:
	1. I due nodi in $G$ sono in due cc diverse, e quindi nel complemento essi saranno connessi
	2. I due nodi sono nella stessa cc:
		2.1. In $G$ non sono connessi, quindi in $\overline{G}$ sono connessi direttamente
		2.2 In $G$ non sono connessi, allora in $\overline{G}$ sono connessi da un cammino che passa per un'altra cc

4. Basti pensare che $G$ sia vuoto, allora $\overline{G}$ sarà pieno, quindi l'implicazione è falsa

