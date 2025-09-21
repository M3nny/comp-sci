# Le relazioni
Una **relazione binaria** $\mathcal{R}$ tra $A$ e $B$ è un sottoinsieme del prodotto cartesiano $A \times B$ e la possiamo scrivere come:
$$\mathcal{R} \subseteq \{(x,y)x\in A \land y\in B\}$$
Oppure possiamo scrivere che $x$ è in relazione con $y$ in questo modo:
$$x\mathcal{R}y$$
Una relazione può anche essere **n-aria**, quindi con più di due elementi relazionati tra loro:
$$\{(x,y,z)|x,y,z\in \mathbb{Z} \land x+y=z\} \subseteq \mathbb{Z} \times \mathbb{Z} \times \mathbb{Z}=\mathbb{Z}^3$$
## Proprietà delle relazioni
Siano $A$ un insieme e $\mathcal{R} \subseteq A\times A=A^2$ una relazione. Diciamo che una relazione è:

---
### Riflessiva
Quando un elemento è relazionabile a se stesso.
$$x\mathcal{R}x \quad\text{ oppure }\quad (x,x)\in \mathcal{R}$$
**Esempio**: _numero divisibile per se stesso_.

---
### Irriflessiva
Quando <u>non è possibile</u> che un elemento si relazioni con se stesso.
$$\neg(x\mathcal{R}x) \quad\text{ oppure }\quad (x,x)\notin \mathcal{R}$$
**Esempio**: _essere minore di se stesso_.

---
### Simmetrica
Quando la relazione che lega $x$ a $y$ è valida anche per $y$ a $x$.
$$x\mathcal{R}y \implies y\mathcal{R}x\quad \text{ oppure }\quad (x,y)\in \mathcal{R} \implies (y,x)\in \mathcal{R}$$
**Esempio**: _il prodotto di x e y vale 100_.

---
### Antisimmetrica
Quando la relazione che lega $x$ a $y$ <u>non è valida</u> anche per $y$ a $x$.
$$x\mathcal{R}y \implies \neg(y\mathcal{R}x)\quad \text{ per ogni } x\neq y \in A$$

**Esempio**: _x > y_ (se 3 > 2, sicuramente 2 non è > di 3).

---
### Transitiva
$$x\mathcal{R}y\text{ e }y\mathcal{R}z \implies x\mathcal{R}z$$
$$oppure$$
$$(x,y)\in \mathcal{R} \text{ e }(y,z)\in \mathcal{R} \implies (x,z)\in \mathcal{R} \text{ per ogni x,y,z }\in A$$
**Esempio**: 
- _x=5, y=4, z=2_. 
- _5 > 4;  4 > 2;  $\implies$ 5 > 2_.

---
## Relazioni d'ordine

### Parziale
Una relazione $\mathcal{R}$ può essere definita tale se verifica le seguenti proprietà:
- RIFLESSIVA
- ANTISIMMETRICA
- TRANSITIVA

Possono esistere $x\neq y$ tali che nè $x\mathcal{R}y$ nè $y\mathcal{R}x$.
È detta **TOTALE** se soddisfa anche la seguente proprietà:
- $\forall x,y(x\mathcal{R}y \text{ oppure } y\mathcal{R}x)$.

### Parziale stretto
Una relazione $\mathcal{R}$ può essere definita tale se verifica le seguenti proprietà:
- IRRIFLESSIVA
- ANTISIMMETRICA
- TRANSITIVA

Gli **ordini parziali** vengono indicati con $\leq$ mentre quelli **parziali stretti** vengono indicati con $<$

Possiamo sempre passare <u>da parziale</u> $(\leq)$ <u>a parziale stretto</u> $(<)$:
$$x<y \iff x\leq y \land x\neq y$$
Oppure viceversa possiamo passare da un ordinamento <u>parziale stretto</u> ($<$) <u>ad uno parziale</u> ($\leq$):
$$x\leq y \iff x<y \lor x=y$$
>[!Tip]
>- Due elementi $x,y\in A$ sono **confrontabili** se $x\mathcal{R}y \lor y\mathcal{R}x$;
>- Due elementi $x,y\in A$ sono **inconfrontabili** se nè $x\mathcal{R}y$ nè $y\mathcal{R}x$.

---
## Catene e anticatene
- Un sottoinsieme $X$ di un insieme [parzialmente ordinato](###Parziale) $A$ è definito come una **catena** se gli elementi di $X$ sono **confrontabili** a due a due.
$$esempio:\quad 0<1<2<3<4<...$$
- Un sottoinsieme $X$ di un insieme [parzialmente ordinato](###Parziale) $A$ è una **anticatena** se gli elementi di $X$ sono **inconfrontabili** a due a due.
$$\text{esempio:}\quad n_1<n_2 \text{ se } n_1 \text{ è un divisore di }n_2$$
$$3\space 5\space 7\space 11$$
## Ordinamento ben fondato
- Un ordinamento [parziale](###Parziale) è detto **ben fondato** se non ammette catene discendenti infinite del tipo: $a_0>a_1>a_2>...>a_n>...$ 
---
## Relazione di equivalenza
Una relazione $\mathcal{R}$ è una **relazione di equivalenza** se verifica le seguenti proprietà:
- RIFLESSIVA
- SIMMETRICA
- TRANSITIVA

### Classi di equivalenza
Indico la classe di equivalenza tramite:
$$[a]_{\mathcal{R}}=\{x\in A | a\mathcal{R}x\}$$
Possiamo dire che l'insieme delle classi di equivalenza di $A$ rispetto a $\mathcal{R}$ forma una **partizione** di $A$, infatti:
- Ogni classe <u>non è vuota</u>;
- L'<u>unione</u> di tutte le classi<u> mi fa ottenere</u> $A$;
- Le classi sono <u>distinte e disgiunte</u>;
- <u>Ogni elemento</u> di $A$ è <u>contenuto in una ed una sola classe</u>.

