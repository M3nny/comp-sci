Classifichiamo tre tipi di complessità in un algoritmo, il caso **migliore**, **medio**, e **peggiore**.
Considerando la **ricerca sequenziale** di un elemento in un array otteniamo le seguenti complessità:
- $T_{\text{best}}(n)=1$ (il primo elemento è quello cercato)
- $T_{\text{avg}}(n)=\frac{n}{2}$ (l'elemento cercato si trova circa in mezzo all'array)
- $T_{\text{worst}}(n)=n$ (l'ultimo elemento è quello cercato)

Nello studio della complessità andremo sempre a valutare il caso **peggiore**.

## Costrutti base

#### If-else
```
if <cond>:
	// ramo then
else:
	// ramo else
```
La `<cond>`, il ramo `then` ed `else` avranno ciascuno complessità pari a $O(f(n))$
per valutare il caso peggiore la complessità del costrutto sarà:
$$O(f(n)+\max\{g(n),h(n)\}$$
dove $f(n)$ è `cond`
#### For
```
for i = 1 to k:
	// block
```
Considerando la complessità del `block` pari a $O(f(n))$, la complessità del costrutto sarà data dalla complessità di `block` moltiplicato `k` volte:
$$O(k\cdot f(n))$$
considerando due cicli for annidati
```
for i = 1 to k:
	for j = 1 to m:
		// block
```
$$O(k\cdot m\cdot f(n))$$
#### While
```
while <cond>:
	// block
```
Considerando la complessità di `<cond>` pari a $O(f(n))$ e quella di `block` pari a $O(g(n))$, definiamo $N(n)$ come il massimo numero di iterazioni del ciclo, otteniamo che la complessità del costrutto è:
$$O(N(n)\cdot(f(n)+g(n)))$$

>[!Example]
>```c
>int MyAlgorithm(int n) {
>	int a, i, j;
>	if (n > 1) {
>		a = 0
>		for (int i = 1; i < n; i++) {
>			for (int j = 1; j < n; j++) {
>				a = (a+1) * j + (a/2);
>			}
>		}
>		for (int i = 1; i < 16; i++) {
>			a = a + MyAlgorithm(n/4);
>		}
>		return a;
>	}
>	else {
>		return false;
>	}
>}
>```
>Consideriamo gli assegnamenti e valori di ritorno come complessità $O(1)$, i primi due cicli for annidati avranno complessità totale pari a $O(n^2)$, dovremo poi introdurre una complessità ricorsiva per quanto riguarda il terzo ciclo for, ovvero: $16T(\frac{n}{4})$.
>Complessità dell'algoritmo: $T(n)=n^2+16T(\frac{n}{4})$.


## Ricorrenze
Nell'esempio appena visto otteniamo una complessità ricorsiva, vediamo ora come esprimere quella complessità con una notazione non ricorsiva.
#### Metodo dell'iterazione
Consiste nello "**srotolare**" le chiamate ricorsive fino al caso base.
>[!Example]
>Considerando l'algoritmo di ricerca binaria:
>$$T(n)=\begin{cases}c+T(\frac{n}{2})&\text{se }n\geq 2\\1&\text{se }n=1\end{cases}$$
>srotoliamo le ricorrenze:
>$$\begin{flalign}
>T(n)&=c+T(\frac{n}{2})\\
>&=c+[c+T(\frac{n}{2^2})]=2c+T(\frac{n}{2^2})\\
>&=2c+[c+T(\frac{n}{2^3})]=3c+T(\frac{n}{2^3})\\
>&=\space...\\
>&=kc+T(\frac{n}{2^k})
>\end{flalign}$$
>Al k-esimo passo la funzione sarà come riportato sopra, ora ci riconduciamo al caso base ponendo:
>$$\frac{n}{2^k}=1\iff n=2^k\iff k=\log_2n$$
>$k$ ora assume il valore per cui $\frac{n}{2^k}=1$ (caso base).
>Otteniamo quindi:
>$$T(n)=c\log_2n+T(1)=c\log_2n+1$$
>$$T(n)=\Theta(\log_2n)$$
>---
>Consideriamo quest'altro esempio:
>$$T(n)=\begin{cases}9T(\frac{n}{3})+n&\text{se }n\geq 2\\1&\text{se }n=1\end{cases}$$
>$$\begin{flalign}
>T(n)&=9[9T(\frac{n}{3^2})+\frac{n}{3}]+n=9^2T(\frac{n}{3^2})+3n+n\\
>&=9^2[9T(\frac{n}{3^3})+\frac{n}{3^2}]+3n+n=9^3T(\frac{n}{3^3})+9n+3n+n\\
>&=9^3T(\frac{n}{3^3})+n(3^2+3^1+3^0)\\
>&=\space...\\
>&=9^kT(\frac{n}{3^k})+n(\sum_{i=0}^{k-1}3^i))
>\end{flalign}$$
>[[Le sommatorie#Scambio degli indici|Risolvendo la sommatoria]] si ottiene:
>$$T(n)=9^kT(\frac{n}{3^k})+n\frac{3^k-1}{2}$$
>Trovo quando $k=1$ per riportarmi al caso base:
>$$\frac{n}{3^k}=1\iff n=3^k\iff k=\log_3n$$
>sostituisco e semplifico:
>$$\begin{flalign}
>T(n)&=9^{\log_3n}T(1)+n\frac{3^{\log_3n}-1}{2}\\
>&=3^{\log_3n^2}+n\frac{n-1}{2}\\
>&=n^2+\frac{n(n-1)}{2}=\Theta(n^2)
>\end{flalign}$$

#### Metodo della sostituzione
Consiste nell'**indovinare** la complessità dell'algoritmo e poi dimostrarla per induzione.
>[!Example]
>$$T(n)=\begin{cases}1&\text{se }n=1\\T\lfloor\frac{n}{2}\rfloor+n&\text{se }n\geq 2\end{cases}$$
>Ipotizzo $T(n)=O(n)$, quindi usando la definizione di $O$:
>$$\exists c>0,\exists n_0\in\mathbb{N}|\forall n\geq n_0:\quad T(n)\leq c\cdot n$$
>Dimostrazione per inuduzione:
>**Caso base**: $n=1$
>$$T(1)\leq c\cdot 1\implies 1\leq c\quad \text{vero}\forall c\geq 1$$
>**Passo induttivo**
>Suppongo che la proprietà valga fino a $n-1$:
>$$\begin{flalign}
>T(n)&=T\left(\Big\lfloor\frac{n}{2}\Big\rfloor\right)+n\\
>&\leq c\cdot\Big\lfloor\frac{n}{2}\Big\rfloor+n\\
>&\leq c\cdot\frac{n}{2}+n\\
>&=\left(\frac{c}{2}+1\right)\cdot n
>\end{flalign}$$
>Sotto quali condizioni $\frac{c}{2}+1\leq c$ ?
>$$1\leq\frac{c}{2}\iff c\geq 2$$
>La proprietà risulta quindi verificata per $c\geq 2$ 
