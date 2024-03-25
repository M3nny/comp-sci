Se $G$ è [[Tipologie#Grafo Connesso|connesso]] allora:
$$|E|\geq |V|-1$$
**Caso base**: prendendo in considerazione un singolo vertice senza archi, si ha:
- $|E| = 0$
- $|V| = 1$
risulta essere vera la proprietà
**Passo induttivo**: assumiamo che valga fino a $n-1$ e lo dimostro per $n$:

Indichiamo con $z\in V$ un nodo da togliere da $G$, otteniamo il seguente grafo indotto: $G'=G[V\setminus \{z\}]$.

Dopo aver tolto $z$, $G'$ potrebbe essere connesso oppure no, in base a quale nodo togliamo, per cui l'ipotesi non può essere applicata interamente, e non sapendo il numero di componenti connesse $k$ di $G'$, applichiamo l'ipotesi induttiva su tutte.

Indicando con $E_i$, $V_i$ il numero di archi e vertici della $i$-esima componente connessa, vogliamo dimostrare che $|E_i|\geq |V_i|-1$:
$$\begin{flalign}
|E|&=\sum_{i=1}^k(\underbrace{|E_i|}_{|V_i|-1}+\underbrace{\deg(z)}_\text{archi del nodo rimosso})\\
&\geq\sum_{i=1}^k(|V_i|-1)+\deg(z)\quad\text{(maggiorazione)}\\
&\geq\sum_{i=1}^k(|V_i|)-k+\deg(z)\\
&\geq |V|-1+\deg(z)-k
\end{flalign}$$
Nell'ultima riga viene scritto $-1$ per via di $z$ che non appartiene a $G'$ in quanto viene tolto.

La dimostrazione finisce se riusciamo a dimostrare che $\deg(z)-k\geq 0$.
Abbiamo però che $\deg(z)\geq k$ di sicuro in quanto il grafo inizialmente era connesso, quindi $z$ aveva _almeno_ un arco che lo collegava a tali componenti connesse, per cui dato che $\deg(z)-k$ è $\geq 0$, otteniamo:
$$\begin{flalign}
|E|&\geq|V|-1+\deg(z)-k\\
&\geq|V|-1
\end{flalign}$$

---
### Componente connessa
Dato un grafo $G=(V,E)$, una **componente connessa** di $G$ è un sottoinsieme di vertici $V'$ tale che:
- Il sottografo indotto $G[V']$ è connesso
- La componente connessa non deve appartenere ad un'altra più grande, ovvero $V'$ non è contenuto in nessun insieme di vertici che induca ad un sottografo connesso

Un esempio è il seguente grafo, il quale contiene $3$ componenti connesse:
![[Componenti connesse.svg]]
**Proprietà**: l'insieme delle componenti connesse di un grafo formano una [[Gli insiemi#Partizione|partizione]] di $V$.