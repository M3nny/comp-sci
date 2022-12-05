Una **trasformazione lineare**(o applicazione lineare) è una **funzione tra due spazi vettoriali** che conserva le **combinazioni lineari** (operazioni di somma di vettori e di moltiplicazione per uno scalare).

Siano $V$ e $W$ due spazi vettoriali (sullo stesso campo).
Una funzione $f:V\to W$ è una _trasformazione lineare_ se soddisfa le seguenti proprietà per ogni vettore $x,y \in V$ e $r$ scalare
- $f(x+y) = f(x)+f(y)$;
- $f(rx)=rf(x)$.

## Omomorfismo
Una trasformazione lineare $F:V\to W$ è un **omomorfismo** se oltre alle proprietà precedenti,
soddisfa anche:
- Presi due elementi $v_1, v_2$, l'immagine della somma è uguale alla somma delle immagini;
- L'immagine del prodotto tra un qualsiasi elemento $v \in V$ e un qualsiasi scalare $a \in \mathbb{K}$ è uguale al prodotto tra lo scalare e l'immagine di $v$.

### Isomorfismo
L'isomorfismo è una trasformazione lineare dove spazi vettoriali $V$ e $W$ hanno la stessa dimensione, per cui si corrispondono in una trasformazione lineare invertibile (quindi iniettiva e suriettiva):
$$f:V\to W$$
$$f^{-1}: W\to V$$
>Qualsiasi applicazione lineare invertibile è un isomorfismo.

### Endomorfismo
Un endomorfismo è caratterizzato dal dominio e codominio che coincidono.
$$f:V\to V$$
### Automorfismo (o endomorfismo biiettivo)
Prende questo nome qualsiasi operatore lineare che sia iniettivo e suriettivo, quindi:
$$f:V\to V$$
$$f^{-1}:V\to V$$
---
## Capisaldi delle trasformazioni lineari

### Nucleo
$$\ker(G)=\{v\in V: f(v)=0\}$$
Il nucleo ($\ker$) in una trasformazione lineare viene definito così un particolare **sottoinsieme del dominio** dell'applicazione lineare, **formato dai vettori del dominio che hanno come immagine lo zero del codominio**.
Inoltre studiandolo è possibile ricavare l'iniettività della funzione.

### Immagine delle matrici
$$Im(f)=\{w\in W: \exists v\in V \text{ per cui }f(v)=w\}$$
L'immagine ci permette di trovare la controimmagine e di studiare la suriettività dell'applicazione lineare.

>Il rango è anche definito come la dimensione dell'immagine.

>[!Teorema delle dimensioni (o della nullità più rango)]
>Mette in relazione le dimensioni di nucleo e immagine di una applicazione lineare con la dimensione dello spazio vettoriale in cui essa è definita.
>Dice quindi che la somma delle dimensioni di $\ker(f)$ e di $Im(f)$ sia uguale a quella dello spazio in cui è finita $f$:
>$$\dim(V)=\dim(\ker(f)) + \dim(Im(f))$$

In base all'immagine ed il nucleo l'applicazione lineare $f: V\to W$ può essere:
- **iniettiva** se $\dim(\ker(f)) = \{0\}$
- **suriettiva** se $\dim(Im(f)) = \dim(W)$
- **biettiva** se è sia _iniettiva_ sia _suriettiva_, inoltre se è biettiva è anche invertibile

### Applicazioni lineari e matrici
Ad ogni applicazione lineare è associata una matrice:
$T: \mathbb{R}^2\to \mathbb{R}^3$ 
$T((x,y)) = (x+y,\space 2x,\space x-y)$
$$\begin{bmatrix} 1 &1\\2 &0\\1 &-1\end{bmatrix} \cdot \begin{bmatrix}x\\ y \end{bmatrix} = \begin{bmatrix}x+y\\2x\\x-y \end{bmatrix}$$
