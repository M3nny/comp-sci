Nella migliore delle ipotesi una funzione hash distribuisce le chiavi $k$ in modo uniforme ed indipendente nell'intervallo $0\leq k<1$.
$$h(k)=\lfloor k\cdot m\rfloor\quad\text{(H.U.I.)}$$
**Ipotesi**: le chiavi sono numeri naturali.
Questa ipotesi non è restrittiva in quanto ci si può riportare a numeri naturali tramite varie codifiche.

### Metodo della divisione
$$h(k)=k\text{ mod } m$$
In questo metodo il valore dell'hashing sarà dato dal resto della divisione tra la chiave e la dimensione della tabella hash.
- **Vantaggio**: facile da calcolare
- **Svantaggi**: rende la dimensione della tabella un <u>dato critico</u>

Sono da evitare alcuni valori per $m$, in particolare le potenze di $2$: se $m=2^p$, $h(k)$ rappresenta i $p$-bit meno significativi di $k$, così il valore hash dipenderà solo dagli ultimi bit, vorremmo che usasse tutti i bit della divisione, inoltre usando gli ultimi bit, essi si ripeteranno con più frequenza portando ad una distribuzione non uniforme.

Una buona scelta per $m$ è un numero primo non troppo vicino ad una potenza di $2$ o $10$.
>[!Example]
>Volendo memorizzare $2000$ elementi e prevedendo una media di $3$ collisioni, cerco un numero primo vicino a $\frac{n}{3}=\frac{2000}{3}\simeq 666.6$, scelgo arbitrariamente $701$, questo valore permette di distribuire in modo opportuno gli elementi nella tabella perchè $\frac{n}{3}\leq 701$.


### Metodo della moltiplicazione
$$h(k)=\lfloor m\cdot k\rfloor,\quad k\in[0,1[$$
L'idea è quella di trasformare $k$ in un numero $\in[0,1[$ per poi applicare la funzione hash:
1. Fisso una costante $A\in]0,1[$
2. Calcolo $k\cdot A$
3. Estraggo la parte frazionaria: $(k\cdot A)\text{ mod }1$

La funzione hash sarà quindi:
$$h(k)=\lfloor m\cdot((k\cdot A)\text{ mod }1)\rfloor$$
**Vantaggi**:
- La dimensione $m$ della tabella hash, non è un <u>valore critico</u>
- Funziona bene con tutti i valori di $A$
- L'informatico Donald Knuth ha osservato che l'algoritmo funziona bene con l'inverso del rapporto aureo: $A\simeq\frac{\sqrt{5}-1}{2}=0.618034$

#### Semplificare il calcolo
Sia $w$ la lunghezza di una [[Linguaggio macchina MIPS#Istruzioni e linguaggio macchina|word]] di memoria, assumiamo che $k$ entri in una singola word.
Scelgo un intero $q\in]0,2^w[$ e $m=2^p$, con $p\in]0,w]$.
Pongo $A=\frac{q}{2^w}<1$, il prodotto tra $k\cdot A$ diventerà:
$$k\cdot A=\frac{k\cdot q}{2^w}$$
![[Metodo della moltiplicazione semplificato.svg]]
Siamo interessati ai $p$ bit più significativi (quindi alla parte frazionaria) della word meno significativa del prodotto $k\cdot q$. (inizio della seconda word):
$$
\begin{flalign}
h(k)&=\lfloor m\cdot((k\cdot A)\text{ mod }1)\rfloor\\
&=\Big\lfloor \Big(2^p\cdot\Big(\frac{k\cdot q}{2^w}\Big)\Big)\text{ mod }1\Big\rfloor\\
&=((k\cdot q)\text{ mod }2^w)\gg(w-p)
\end{flalign}
$$
**Hashing universale (randomizzato)**: invece di avere una singola funzione hash $h$, si ha un insieme $\mathcal{H}$ di quest'ultime, all'inizio dell'esecuzione il programma ne sceglierà una casualmente.
Questo viene fatto per evitare possibili attacchi, dove, sapendo la funzione di hashing di partenza si vanno ad inserire valori che andranno mappati tutti in una singola cella, compromettendo la performance del programma.
