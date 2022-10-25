Questo capitolo sorvolerà o darà una definizione più banale di alcuni temi dato che la maggior di essi sono già stati trattati nella [[Cos'è una funzione|definizione di funzione]] in calcolo.

Una funzione associa ogni elemento di A ad **uno ed un solo** elemento di B, dove A sarà il **dominio** e B il **codominio** ($f: A\to B$).
Possiamo quindi scrivere l'insieme delle funzioni da A a B come $B^A$.

- L'**insieme immagine** di una funzione è dato dai valori del suo dominio messi dentro alla funzione, possiamo definire l'immagine di A tramite:
$$f(A)=\{f(x)|x\in A\}$$
- Inoltre se una funzione ha cardinalità pari a $1$ ($|f(A)|=1$) allora $f$ viene detta **costante**.

## Proprietà delle funzioni
- **Iniettiva**: quando per ogni elemento $y$ del codominio esiste **al massimo** un elemento $x$ del dominio;
$$f(x)=f(x')\implies x=x',\space \forall x,x' \in A \text{ con } x\neq x$$
- **Suriettiva**: quando per ogni elemento $y$ del codominio esiste **almeno** un elemento $x$ del dominio;
$$\text{ esiste almeno un x tale che } y=f(x)$$
- **Biettiva**: quando è sia iniettiva che suriettiva, quindi per ogni elemento $y$ del codominio esiste **uno ed un solo** elemento $x$ del dominio, in questo caso $A$ e $B$ avranno la stessa cardinalità $|A|=|B|$.

---
### Funzione identica (o identità)
Sia $A$ un insieme
$$i_A:A\to A$$
$$i_A(x)=x,\forall x\in A$$
- È **biettiva**.

---
### Funzione inclusione
Sia $A\subseteq B$
$$j:A\to B$$
$$j(x)=x,\forall x\in A$$
- È **iniettiva**.

---
### Funzione pavimento (o floor)
Indica il massimo intero non maggiore di $x$:
$$\lfloor x\rfloor: \mathbb{R}\to \mathbb{Z}$$
$$\lfloor x\rfloor=max\{v\in \mathbb{Z}|v\leq x\}$$
### Funzione soffitto (o ceiling)
Indica il minimo intero non minore di $x$:
$$\lceil x\rceil: \mathbb{R}\to \mathbb{Z}$$
$$\lceil x\rceil=min\{v\in \mathbb{Z}|v\geq x\}$$

>[!Example]
>- $\lfloor 1.5\rfloor =1 \quad \lfloor -1.5\rfloor =-2$
>- $\lceil 1.5\rceil=2 \quad \lceil -1.5\rceil =-1$

---
### Funzioni composte
Date due funzioni
$$f:A\to B \quad \text { e } \quad g:B\to C$$
il quale **codominio della prima coincide con il dominio della seconda** possiamo definire una terza funzione:
$$h:A\to C$$
La [[Operazioni tra funzioni#Funzione composta|funzione composta]] sarà indicata come $g\circ f$ (oppure gf) e definita dalla regola:
$$h(x)=(gf)(x)=g(f(x))$$
- Non soddisfano la proprietà commutativa;
- Soddisfano invece la proprietà associativa.
- La funzione composta ($ff$) si indica anche con $f^2$ più in generale $f^n$

---
### Funzione idempotente
$$f:A\to A$$
$$f=f^2$$
Troviamo in questo tipo di funzioni quelle:
- costanti;
- identità;
- valore assoluto;
- floor e ceiling.

---
### Funzione inversa
Una funzione per essere [[Operazioni tra funzioni#Funzione inversa|inversa]] deve essere biunivoca e si indica con $f^-1$, inoltre se $f$ possiede una funzione inversa allora essa è unica.
>[!Example]
>**Data la funzione** $f(x)=ax+b$ **trovare la sua inversa**:
>$$y=ax+b$$
>$$x=\frac{y-b}{a}$$
>
>Possiamo quindi scrivere che $f^{-1}(x)=\frac{y-b}{a}$

