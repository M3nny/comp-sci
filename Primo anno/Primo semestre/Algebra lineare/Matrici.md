Un elemento all'interno di una matrice $A$ si indica come $a_{ij}$ dove $i$ è la riga e $j$ è la colonna.
$$

A = \begin{bmatrix}

a_{11} & a_{12} & ... & a_{1j} \\

a_{21} & a_{22} & ... & a_{2j} \\

\vdots & \vdots & \ddots & \vdots \\

a_{i1} & a_{i2} & ... & a_{ij} \\

\end{bmatrix}

$$
- **vettore riga** di $A$: $A_i=\begin{bmatrix} a_{i1}, a_{i2}, ..., a_{ij}\end{bmatrix}$ è definito come una matrice $1 \times n$
- **vettore colonna** di $A: A_j=\begin{bmatrix} a_{1j}\\ a_{2j}\\ \vdots \\ a_{ij}\end{bmatrix}$  è definito come una matrice $n\times 1$
Chiamiamo poi un elemento $a_{ij}$ **termine o componente**.
>[!Example]
>$$\begin{bmatrix} 1 & 1 & -2\\ -1 & 4 & -5\end{bmatrix}$$
>Ha dimensione $2\times 3$ 
>Otteniamo inoltre 2 vettori riga e 3 vettori colonna.

Indichiamo con $O$ la **matrice zero**, ovvero con tutti gli elementi pari a $0$, dove: $O + A = A + O = A$ 

## Operazioni tra matrici

### Addizione
L'addizione tra matrici avviene solo se hanno la stessa dimensione, nel caso contrario si potrebbe procedere aggiungendo zeri a quella più piccola (padding).
>[!Example]
>$$A=\begin{bmatrix} 1 & -1 & 0\\ 2 & 3 & 4\end{bmatrix} \quad B=\begin{bmatrix} 5 & 1 & -1\\ 2 & 1 & -1\end{bmatrix}$$
>$$A+B=\begin{bmatrix} 6 & 0 & -1\\ 4 & 4 & 3\end{bmatrix}$$

### Trasposizione
Considerando la matrice $A=(a_{ij})\space m\times n$, la **matrice trasposta** sarà $n\times m \space B=(b_{ji})$, praticamente le righe diventano colonne e viceversa.
>[!Example]
>$$A=\begin{bmatrix}2 & 1 & 0\\1& 3 & 5\end{bmatrix} \quad A^t=\begin{bmatrix} 2 & 1\\1 & 3\\ 0&5\end{bmatrix}$$

Da notare che $(A^t)^t=A$ 

## Matrice quadrata
Una matrice è quadrata quando è di dimensioni $n\times n$ e il determinante è $\neq 0$.
Vediamo ora le operazioni che possiamo eseguire e i tipi di matrice quadrata:

### Simmetrica
Se $a_{ij} = a_{ji}$
$$\begin{bmatrix} 3&-2&4\\-2&6&2\\4&2&3 \end{bmatrix}$$
### Diagonale
Se $a_{ij}=0$ per $i\neq j$:
$$\begin{bmatrix} x&0&0\\0&x&0\\0&0&x\end{bmatrix}$$
### Identica
Se $a_{ii} = 1$ ed il resto è a $0$:
$$\begin{bmatrix} 1&0&0\\0&1&0\\0&0&1\end{bmatrix}$$
### Triangolare (sup/inf):
$$\begin{bmatrix} x&0&0\\x&x&0\\x&x&x\end{bmatrix} \quad \text{oppure}\quad \begin{bmatrix} x&x&x\\0&x&x\\0&0&x\end{bmatrix}$$
### Traccia
La traccia della matrice è la somma dei valori nella sua diagonale principale, può essere scritta come:
$$\sum_{i=1}^na_{ii}$$
### Prodotto
Se voglio fare il prodotto tra due matrici devo assicurarmi che le **colonne della prima siano uguali alle righe della seconda**.
Ad esempio si potrebbe fare il prodotto tra $A (m\times n)$ e $B(n\times s$).
Andremo poi ad ottenere dal prodotto, una matrice $m\times s$

Possiamo scrivere il prodotto tra due matrici come:

>[!Example]
>$$A=\begin{bmatrix} 2&1&5\\1&3&2 \end{bmatrix} \quad B=\begin{bmatrix} 3&4\\-1&2\\2&1 \end{bmatrix}$$
>Il prodotto $A\cdot B$ sarà di dimensioni $2\times 2$
>Procedo moltiplicando:
>- $1^a$ riga $1^a$ colonna;
>- $1^a$ riga $2^a$ colonna;
>- $2^a$ riga $1^a$ colonna;
>- $2^a$ riga $2^a$ colonna;
>
>Ottengo:
>$$A\cdot B=\begin{bmatrix} 15&15\\4&12 \end{bmatrix}$$

#### Proprietà del prodotto
- Il prodotto tra matrici è associativo: $A(BC)=(AB)C$;
- Ammette l'elemento neutro, ovvero la matrice identica $I$, quindi: $IA=AI=A$;
- Distributiva rispetto la somma: $A(B+C)=(AB)+(AC)$;
- Se $A$ e $B$ si possono moltiplicare, allora $(AB)^t=B^tA^t$.
>[!Attention]
>Il prodotto **non è** commutativo: $AB \neq BA$

## Vettori come matrici
I vettori posso essere suddivisi in:
- Matrici riga;
- Matrici colonna;

Il prodotto tra vettori deve sempre essere del tipo m.riga x m.colonna, dato che solo in questo caso si potrà avere il prodotto in quanto le colonne del primo sono uguali alle righe del secondo.

Nel caso dovessi avere due vettori colonna, per moltiplicarli dovrò prima fare la matrice trasposta.
>[!Example]
>a=v.colonna $nx1$
>b=v.colonna $nx1$
>Per moltiplicarli dovrò fare:
>$$a^t\cdot b$$
>Il quale risultato sarà **1 singolo valore**.

---
## Matrici elementari
Sono definite per interpretare le mosse di Gauss e sono di tre tipi:
1. **Scambio di righe**;
2. **Moltiplicazione di una riga per uno scalare**;
3. **Combinazione lineare**, ovvero aggiungere ad una riga un'altra riga moltiplicata per uno scalare.

---
## Determinante
Può essere calcolato se la matrice è quadrata, esso è un numero reale.
#### Matrice 2x2:
$$det(A)=(a_{11}\cdot a_{22})- (a_{12}\cdot a_{21})$$
- Se 2 colonne sono uguali, allora $det = 0$.
- Il determinante di una matrice Identica è $det = 1$.
- Due matrici sono linearmente indipendenti _se e solo se_ $det = 0$.

#### Matrice 3x3
Il determinante in questo caso va calcolato con la **regola di Sarrus**:
![[Sarrus.png]]
>[!Example]
>$$A = \begin{bmatrix}1&2&3\\1&1&-1\\2&0&5\end{bmatrix}$$
>$|A| = (1\cdot 1\cdot 5) + (2\cdot -1\cdot 2)+(3\cdot 1\cdot 0) - (2\cdot 1\cdot 3) - (0\cdot -1\cdot 1) - (5\cdot 1\cdot 2)$

## Minore di una matrice
Il **minore** di una matrice è dato dal determinante della sottomatrice ricavata togliendo l'intera riga e colonna appartenenti ad un elemento

>[!Example]
>$$A = \begin{bmatrix}1&3&2\\4&1&3\\2&5&2\end{bmatrix}$$
>Se voglio trovare il minore dell'elemento $a_{21}$ dovrò per prima cosa togliere la riga 2 e colonna 1, ottenendo la sottomatrice:
>$$\begin{bmatrix}3&2\\5&2\end{bmatrix}$$
>ora calcolo il determinante: $3\cdot 2 - 2\cdot 5 = -4$
>
>Per ottenere la **matrice dei minori**, dovrò fare questo passaggio per ogni elemento della matrice, ottenendo quindi:
>$$\text{matrice dei minori} = \begin{bmatrix}-13&2&18\\-4&-2&-1\\7&-5&-11 \end{bmatrix}$$

## Matrice dei cofattori
La **matrice dei cofattori**(o matrice dei complementi algebrici) si ricava procedendo per ogni elemento nel seguente modo: $\text{minore}(a)\cdot (-1)^{i+j}$ 
>[!Example]
>Continuando con la matrice dell'esempio precedente, il cofattore dell'elemento $a_{1,1}$ sarà: $-13\cdot (-1)^{1+1} = -13$.
>
>Procedendo in questo modo per ogni elemento otterremo:
>$$\begin{bmatrix}-13&-2&18\\4&-2&1\\7&5&-11 \end{bmatrix}$$

### Matrice AxB (Laplace)
Posso inoltre calcolare qualsiasi determinante matrice sfruttando la matrice dei cofattori fissando una riga o una colonna (in genere quella con più zeri).
- Fissando una riga:
$$det(A) = \sum_{j=1}^n a_{ij}\cdot C_{ij}$$
- Fissando una colonna:
$$det(A) = \sum_{i=1}^n a_{ij}\cdot C_{ij}$$
>[!Example]
>$$A=\begin{bmatrix}3&2&0&1\\4&0&1&2\\3&0&2&1\\9&2&3&1\end{bmatrix}$$
>Osserviamo che tra le righe/colonne, quella che ha più zeri è la colonna 2, quindi **applicheremo Laplace fissando la seconda colonna**:
>$$det(A) = \sum_{i=1}^n a_{i2}\cdot C_{i2}$$
>Trovo il cofattore di dell'elemento $a_{1,2} (2)$ e di $a_{4,2} (2)$ che sono gli unici elementi diversi da zero nella colonna.
>Procedo quindi a trovare il minore di $a_{1,2}$
>$$det\left(\begin{bmatrix}4&1&2\\3&2&1\\9&3&1\end{bmatrix}\right) = -16$$
>$$Cof(a_{1,2}) = 16$$ 
>Posso quindi mettere dentro alla coda di somme da fare: $2\cdot 16 = 32$
>Gli elementi $a_{2,1}$ e $a_{3,1}$ sono uguali a 0 quindi non serve fare altro, al momento abbiamo: $32+0+0$, manca l'ultimo elemento della colonna da elaborare, ovvero $a_{4,2}$
>$$det\left(\begin{bmatrix}3&0&1\\4&1&2\\3&2&1\end{bmatrix}\right) = -4$$
>$$Cof(a_{4,2}) = -4$$
>Possiamo quindi fare la somma di tutti i risultati trovati:
>$$32+0+0-4\cdot 2=24$$

---
## Matrici inverse
Una matrice quadrata $A$ di ordine $n$ è detta invertibile se il prodotto $A\cdot A^{-1}$ restituisce una matrice identità di ordine $n$.

La posso calcolare solo se il $det(A) \neq 0$ tramite:
$$A^{-1} = \frac{1}{det(A)}\cdot C^T$$
>[!Example]
>Calcolo la matrice inversa (ipotizzando di avere già determinante e matrice dei cofattori trasposta)
>- $det(A) = -16$
>- matrice dei cofattori trasposta:
>$$\begin{bmatrix}-3&-4&5\\-4&0&-4\\5&-4&-3\end{bmatrix}$$
>
>L'inversa è uguale a:
>$$\begin{bmatrix}\frac{3}{16}&\frac{1}{4}&-\frac{5}{16}\\\frac{1}{4}&0&\frac{1}{4}\\-\frac{5}{16}&\frac{1}{3}&\frac{3}{16}\end{bmatrix}$$

### Metodo dell'inversa
Posso capire se un sistema ammette soluzione se il determinante della matrice ricavata dal sistema è $\neq 0$, possiamo rappresentare il sistema come:
$$Ax=b$$
Dove $A$ è la matrice dei coefficienti, $x$ sono tutte le incognite che vogliamo trovare e $b$ i valori noti.
Ricaviamo quindi le soluzioni con:
$$x=A^{-1}\cdot b$$
>[!Example]
>$$\begin{cases}3x+7y=27\\ 5x-2y=4\end{cases}$$
>Vediamo se ammette soluzione calcolando $\left| \begin{bmatrix}3&7\\5&-2\end{bmatrix}\right| = -41 \neq 0$ quindi ammette soluzione, calcoliamo quindi l'inversa:
>
>La formula per l'inversa è $A^{-1} = \frac{1}{det(A)}\cdot C^T$, il determinante già ce l'abbiamo, andiamo a trovare la matrice dei cofattori trasposta:
>- Matrice dei minori: $\begin{bmatrix}-2&5\\7&3\end{bmatrix}$
>- Matrice dei cofattori: $\begin{bmatrix}-2&-5\\-7&3\end{bmatrix}$ -> trasposta: $\begin{bmatrix}-2&-7\\-5&3\end{bmatrix}$
>- Matrice inversa: $\begin{bmatrix}\frac{2}{41}&\frac{7}{41}\\\frac{5}{41}&-\frac{3}{41}\end{bmatrix}$
>
>Andiamo ora a trovare le soluzioni con $x=A^{-1}\cdot b$:
>$$\begin{bmatrix}\frac{2}{41}&\frac{7}{41}\\\frac{5}{41}&-\frac{3}{41}\end{bmatrix} \begin{bmatrix}27\\4\end{bmatrix} = \begin{bmatrix}2\\3\end{bmatrix}$$
>Le soluzioni sono quindi $x = 2$ e $y = 3$.
>

---
## Matrici a scala
Sono matrici dove il primo valore non nullo di una riga si trova dopo il valore non nullo della riga precedente:
$$\begin{bmatrix} 0 & 1 & 5 & 0 & 3 & 1\\ 0 & 0 & 9 & 2 & 5 & 2\\ 0 & 0 & 0 & 0 & 5 & 6\\ 0 & 0 & 0 & 0 & 0 & 1 \end{bmatrix}$$

### Forma ridotta
In questo tipo particolare di matrice a scala:
- Il primo elemento non nullo di ogni riga deve essere $1$;
- Ci deve essere al massimo un $1$ per colonna e se presente non devono esserci altri numeri;
- Le colonne senza $1$ possono avere i valori che vogliono.
$$\begin{bmatrix} 1 & 0 & 0 & 0 & 0 & 7\\ 0 & 1 & 0 & 0 & 0 & 2\\ 0 & 0 & 0 & 1 & 0 & 6\\ 0 & 0 & 0 & 0 & 1 & 0\\ 0 & 0 & 0 & 0 & 0 & 0\ \end{bmatrix}$$

Per trasformare una matrice a scala in una matrice ridotta:
- Si prende la prima riga non nulla;
- Si divide la riga per il suo primo elemento a sinistra;
- Si procede per ogni riga.

---
## Rango della matrice
Il **rango** è un numero compreso tra $0$ e il $\min(i,j)$ e rappresenta il massimo numero di vettori colonna/riga linearmente indipendenti in una matrice.

Per trovarlo devo andare a tentativi, ovvero devo trovare la grandezza più grande della sottomatrice con determinante $\neq 0$.

>[!Example]
>$$A = \begin{bmatrix}1&2&3\\4&5&6\\7&8&9\end{bmatrix}$$
>Comincio con il calcolare il determinante della sottomatrice quadrata più grande, ed essendo la matrice in sè quadrata, sarà proprio $det(A)$, il quale però è uguale a $0$, per cui devo andare a trovare una sottomatrice più piccola (grandezza 2) che abbia $det \neq 0$ , provo con $\begin{bmatrix}1&2\\4&5\end{bmatrix}$, ne calcolo il determinante e vedo che è uguale a $-3$.
>
>Essendo che la sottomatrice più grande con $det \neq 0$ è una matrice 2x2, posso affermare che il rango è pari a $2$.

### Teorema di Rouchè-capelli
Questo teorema ci permette di capire se un sistema lineare ammette o meno soluzioni, indicheremo con $A$ la matrice dei coefficienti del sistema, e con $(A|B)$ la matrice che comprende anche i termini noti, e con $n$ il numero di incognite che compaiono nel sistema.
- **Ha un'unica soluzione** _se e solo se_ $\text{rango }(A) = \text{rango }(A|B) = n$
- **Ha infinite soluzioni** _se e solo se_ $\text{rango }(A) = \text{rango }(A|B) = r<n$
	Le soluzioni dipendono da $n-r$ parametri (con $r$ che è più piccolo di $n$)
- **Non ammette soluzioni** _se e solo se_ $\text{rango }(A) \neq \text{rango }(A|B)$ 

---
## Cramer
Usiamo questo metodo per risolvere sistemi che hanno lo stesso numero di equazioni/incognite.

1. Trovare il determinante della matrice dei coefficienti
2. Creare tante matrici quante sono le incognite, dove andiamo a sostituire la colonna con i valori dell'incognita che vogliamo trovare con i termini noti
3. Calcolare il determinante di ognuna di queste nuove matrici
4. Per trovare il valore dell'incognita $x$ si procede così:
$$x=\frac{D_x}{D}$$
>[!Example]
>$$\begin{cases}2x+3y\\4x-3y\end{cases}$$
>1. $\left| \begin{bmatrix}2&3\\4&-3\end{bmatrix} \right| =-18$
>2.  $D_x = \left| \begin{bmatrix}8&3\\-2&-3\end{bmatrix} \right| =-18$  
$D_y = \left| \begin{bmatrix}2&8\\4&-2\end{bmatrix} \right| =-36$
>3. $x=\frac{D_x}{D} = \frac{-18}{-18} = 1$        $y=\frac{D_y}{D} = \frac{-36}{-18} = 2$
>
>Abbiamo quindi ottenuto che $x=1$ e $y=2$

---
## Autovalori e autovettori
> Si parla di autovalori e autovettori quando ci riferiamo alle matrici quadrate

Un **autovalore** ($\lambda$) è un numero tale che esiste un vettore $v$ per cui:
$$Av = \lambda v$$
$\lambda$ è chiamato l'autovalore di $A$ associato all'autovettore $v$, in questo modo siamo in grado di comprimere l'informazione che la matrice ci da.

Gli autovalori che possiamo trovare saranno **al massimo** dell'ordine della matrice quadrata, quindi se una matrice è $2\times 2$, potremmo trovare al massimo 2 autovalori.
Gli autovalori li possiamo trovare tramite la seguente equazione:
$$\text{Polinomio caratteristico:}\quad det(A-\lambda I) = 0$$
Dove $\lambda I(A)$ che sarebbe la matrice identità, vuol dire sottrarre  un $-\lambda$ a tutti gli elementi della diagonale principale.
>[!Example]
>$$A=\begin{bmatrix}2&0\\1&-1\end{bmatrix}$$
>Risolvo $det(A-\lambda I(A)) = 0$
>$$det\begin{bmatrix}2-\lambda&0\\1&-1-\lambda\end{bmatrix} = 0$$
>Devo risolvere quindi: $(2-\lambda)(-1-\lambda) - (0\cdot 1) = 0$, da cui ne derivo:
>$$(2-\lambda)(-1-\lambda) = 0$$
>Non serve fare ulteriori moltiplicazioni, vedo già che gli autovalori sono:
>$$\lambda_1 = 2 \quad \lambda_2=-1$$

Per determinare gli autovettori associati agli autovalori, risolvo i sistemi che mi escono fuori sostituendo $\lambda$ con gli autovalori trovati:
$$(A-\bar{\lambda} I)\bar{x} = 0$$
Gli autovettori sono:
- **Non nulli**.
- **Infiniti**

>[!Example]
>Trovo l'autovettore associato a $\lambda_1$
>$$\begin{bmatrix}2-2&0\\1&-1-2\end{bmatrix}\begin{bmatrix}x\\y\end{bmatrix}=\begin{bmatrix}0\\0\end{bmatrix} \quad\Rightarrow \quad\begin{cases}0x+0y=0\\x-3y=0\end{cases}$$
>La prima equazione non esiste praticamente, quindi vado a dare un valore $k$ a $y$, andando quindi a risolvere $x-3k = 0 \implies x=3k$, per cui abbiamo trovato:
>$$\begin{cases}x=3k\\y=k\end{cases} \quad k\neq 0$$ 
>Abbiamo infiniti autovettori, basta che $k$ sia diverso da $0$ perchè non rientra nella definizione di autovettore, ad esempio con $k = 1$, ottengo l'autovettore $\begin{bmatrix}3\\1\end{bmatrix}$
>---
>Trovo l'autovetttore associato a $\lambda_2$
>$$\begin{bmatrix}2+1&0\\1&-1+1\end{bmatrix}\begin{bmatrix}x\\y\end{bmatrix}=\begin{bmatrix}0\\0\end{bmatrix} \quad\Rightarrow \quad\begin{cases}3x+0y=0\\x+0y=0\end{cases}$$
>In questo caso ho $x=0$ e $y$ libero, per cui pongo $y = k$:
>$$\begin{cases}x=0\\y=k\end{cases} \quad k\neq 0$$ posso trovare un autovettore con $k=1$ ad esempio, per cui otterrei: $\begin{bmatrix}0\\1\end{bmatrix}$
>---
>>Da notare che il determinante del sistema quando lo si ha trovato è uguale a $0$ 
>
>>Verifico il primo autovettore trovato nell'esempio, moltiplicando la matrice originale per l'autovettore:
>>$$\begin{bmatrix}2&0\\1&-1\end{bmatrix}\begin{bmatrix}3\\1\end{bmatrix}=\begin{bmatrix}6\\2\end{bmatrix} = 2\begin{bmatrix}3\\1\end{bmatrix}$$
>>$2$ era appunto l'autovalore associato all'autovettore
