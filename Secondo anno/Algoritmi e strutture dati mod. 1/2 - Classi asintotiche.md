## Classe $O$
$$O(g(n))=\{f(n)|\exists c>0,\quad \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad f(n)\leq c\cdot g(n)\}$$
**Notazione**: $f(n)=O(g(n))$ 

>Il simbolo $=$ presente nelle notazioni significa "appartiene a"

Per $n$ sufficientemente grande $f(n)$ sarà sempre _sotto o uguale_ ad una funzione $g(n)$ moltiplicata per una costante positiva $c$.

>[!Example]
>$\frac{1}{2}n^2-3n=O(n^2)$
>$$\exists c>0, \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad \frac{1}{2}n^2-3n\leq c\cdot n^2\iff$$
>$$\frac{1}{2}n-3\leq c\cdot n\quad\iff\quad\frac{1}{2}n-cn\leq 3\quad\iff\quad (\frac{1}{2}-c)n\leq 3$$
>Se $(\frac{1}{2}-c)$ fosse $\leq 0$ allora sarebbe sempre $\leq 3$ da cui:
>$$c\geq \frac{1}{2}>0\space\forall n\geq 1$$
>Usiamo $\geq 1$ in quanto consideriamo in numeri naturali che partono da 1.
>Ci sono infinite scelte delle costanti $c$ ed $n_0$, in questo caso sceglieremo $c=\frac{1}{2}$ e $n_0=1$

## Classe $\Omega$
$$\Omega(g(n))=\{f(n)|\exists c>0,\quad \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad c\cdot g(n)\leq f(n)\}$$
**Notazione**: $f(n)=\Omega(g(n))$

Per $n$ sufficientemente grande $f(n)$ sarà sempre _sopra o uguale_ ad una funzione $g(n)$ moltiplicata per una costante positiva $c$.

>[!Example]
>$\frac{1}{2}n^2-3n=\Omega(n^2)$
>$$\exists c>0, \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad c\cdot n^2\leq\frac{1}{2}n^2-3n\iff$$
>$$c\cdot n\leq\frac{1}{2}n-3\quad\iff\quad n(\frac{1}{2}-c)\geq 3$$
>$(\frac{1}{2}-c)$ deve essere $>0$ e anche essere positivo, quindi $0<c<\frac{1}{2}$ si ha quindi:
>$$n\geq\frac{3}{\frac{1}{2}-c}=\frac{6}{1-2c}$$
>Scelgo $c=\frac{1}{14}$ e sostituendo ottengo $n\geq\frac{6}{1-\frac{1}{7}}=7$
>Quindi avrò come soluzioni: $c=\frac{1}{14}$ e $n_0=7$

## Classe $\Theta$ ($O\cap \Omega$)
$$\Theta(g(n))=\{f(n)|\exists c_1>0,\exists c_2>0,\quad \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad c_1\cdot g(n)\leq f(n)\leq c_2\cdot g(n)\}$$
**Notazione**: $f(n)=\Theta(g(n))$

Per $n$ sufficientemente grande $f(n)$ sarà sempre _sotto_ ad una funzione $g(n)$ moltiplicata per una costante positiva $c_2$ ed allo stesso tempo _sopra_ ad una funzione $g(n)$ moltiplicata anch'essa per un'altra costante positiva $c_1$.

>[!Example]
>$\sqrt{n+10}=\Theta(\sqrt{n})$
>$$\exists c_1,c_2>0, \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad c_1\sqrt{n}\leq\sqrt{n+10}\leq c_2\sqrt{n}\iff$$
>$$c_1^2n\leq n+10\leq c_2^2n$$
>1. $$c_1^2n\leq n+10\quad\iff\quad (c_1^2-1)n\leq 10$$
>	Se $c_1^2-1\leq 0$ allora $c_1\leq 1$ che è vero $\forall n \geq 1$, scelgo $c_1=1$
>
>2. $$c_2^2n\geq n+10\quad\iff\quad n(c_2^2-1)\geq 10$$
>	Se $c_2>1:\quad n\geq\frac{10}{c_2^2-1}$, scelgo $c_2=\sqrt{2}$
>Ho $n\geq 10$ quindi con le due costanti scelte ottengo $n_0=10$

---
## Funzioni comuni
- $\log(n)=O(n)\quad\forall n\in\mathbb{N}:\log(n)\leq n-1\leq n$

- $n\log(n)=O(n^2)\quad\forall n \geq 1:\log(n)\leq n\iff n\log(n)\leq n^2$

- $n!=O(n^n)$, infatti:
	$n!=1\cdot 2\cdot 3\cdot ... \cdot n\quad\leq\quad n\cdot n\cdot n\cdot n\cdot ...\cdot n\quad=\quad n^n$
	quindi $n!\leq n^n$

- $n!=\Omega(2^n)$, infatti:
	$n!=1\cdot 2\cdot 3\cdot ... \cdot n\quad\geq\quad1\cdot 2\cdot 2\cdot ... \cdot 2\quad=\quad 2^{n-1}$
	quindi: $2^{n-1}\leq n!\quad\forall n\geq 1$
	da cui: $\frac{1}{2}2^n\leq n!\quad\forall n\geq 1$

- $\log(n!)=O(n\log(n))$, infatti:
	$\log(n!)=\log\left(\prod\limits_{i=1}^ni\right)\quad=\quad\sum\limits_{i=1}^n\left(\log(i)\right)\quad\leq\quad n\log(n)$

- $\sqrt{n}=O(n)$, banalmente:
	$n\leq n^2\space\forall n\geq 1\quad\implies\quad\sqrt{n}\leq n$

![[Plot complessità.png|600]]

---

## Proprietà
**Prima proprietà**:
$$f(n)=O(g(n))\iff g(n)=\Omega(f(n))$$
Ovvero $f(n)$ sta sotto a $g(n)$ solo se quest'ultima sta sopra a $f(n)$
- **Dimostrazione**:
	- **Ipotesi**: $\exists c > 0,\exists n_0\in\mathbb{N}|\forall n\geq n_0:\quad f(n)\leq c\cdot g(n)$ da cui $\frac{1}{c}f(n)\leq g(n)$
	- **Tesi**: $\exists c'>0,\exists n_0'\in\mathbb{N}|\forall n\geq n_0':\quad c'\cdot f(n)\leq g(n)$
	 Metto in uguaglianza ipotesi e tesi e pongo $c'=\frac{1}{c}>0,\space n_0'=n_0$ verificando così la proprietà.

**Proprietà transitiva**:
$$\text{Se }f(n)=O(g(n))\text{ e }g(n)=O(h(n))\text{ allora: }f(n)=O(h(n))$$
Ovvero se $f(n)$ sta sotto a $g(n)$ e quest'ultima sta sotto a sua volta a $h(n)$ allora anche $f(n)$ starà sotto ad $h(n)$, <u>vale anche per le classi:</u> $\Omega$ e $\Theta$ 
- **Dimostrazione**:
	 **Ip.1**: $\exists c_1>0,\exists n_1\in\mathbb{N}|\forall n\geq n_1:\quad f(n)\leq c_1\cdot g(n)$
	 **Ip.2**: $\exists c_2>0,\exists n_2\in\mathbb{N}|\forall n\geq n_2:\quad g(n)\leq c_2\cdot h(n)$
	 **Tesi**: voglio dimostrare che: $\exists c_3>0,\exists n_3\in\mathbb{N}|\forall n\geq n_3:\quad f(n)\leq c_3\cdot h(n)$
	 
	 $f(n)\leq c_1\cdot g(n)\land g(n)\leq c_2\cdot h(n)$
	 Sostituisco $c_2\cdot h(n)$ a $g(n)$ e noto che $f(n)\leq c_1\cdot c_2\cdot h(n)$ quindi ponendo $c_3 = c_1\cdot c_2$ e $n_3=\max\{n_1,n_2\}\space \forall n\geq n_3$ (considerando quindi il punto in cui le funzioni non si incrociano più) la proprietà è verificata.
---

## Classe $o$ 
$$o(g(n))=\{f(n)|\forall c>0,\quad\exists n_0\in\mathbb{N}|\forall n\geq n_0:\quad f(n)<c\cdot g(n)\}$$
Per $n$ sufficientemente grande $f(n)$ sarà sempre _sotto_ ad una funzione $g(n)$ moltiplicata per ogni costante positiva $c$.

**Osservazione**: $o(g(n))\subset O(g(n))$ infatti $f(n)=o(g(n))\implies f(n)=O(g(n))$ 

**Proprietà**:
$$f(n)=o(g(n))\iff\lim\limits_{n\to\infty}\frac{f(n)}{g(n)}=0$$
$$\text{quindi}$$
$$\lim\limits_{n\to\infty}\frac{f(n)}{g(n)}=0\implies f(n)=O(g(n))$$
- $\log(n)=O(\sqrt{n})$, infatti applicando de l'Hopital:
	$\lim\limits_{n\to\infty}\frac{log(n)}{\sqrt{n}}=\space\lim\limits_{n\to\infty}\frac{\frac{1}{n}}{\frac{1}{2}n^{-\frac{1}{2}}}=\space\lim\limits_{n\to\infty}\frac{2}{n}\sqrt{n}=\space\lim\limits_{n\to\infty}\frac{2}{\sqrt{n}}=0$ 
	quindi, $\log(n)=o(\sqrt{n})\implies\log(n)=O(\sqrt{n})$

## Classe $\omega$
$$\omega(g(n))=\{f(n)|\forall c>0,\quad\exists n_0\in\mathbb{N}|\forall n\geq n_0:\quad c\cdot g(n)<f(n)\}$$
Per $n$ sufficientemente grande $f(n)$ sarà sempre _sopra_ ad una funzione $g(n)$ moltiplicata per ogni costante positiva $c$.

**Osservazione**: $\omega(g(n))\subset \Omega(g(n))$ infatti $f(n)=\omega(g(n))\implies f(n)=\Omega(g(n)$

**Proprietà**:
$$f(n)=\omega(g(n))\iff\lim\limits_{n\to\infty}\frac{f(n)}{g(n)}=+\infty$$
$$\text{quindi}$$
$$\lim\limits_{n\to\infty}\frac{f(n)}{g(n)}=+\infty\implies f(n)=\Omega(g(n))$$
### Osservazioni generali sulle classi asintotiche
- Se $f(n)=o(g(n))$ potrebbe accadere che $f(n)=\Omega(g(n))$?
	**No**, perchè:
	1. $o(g(n))\cap\Omega(g(n))=\emptyset$
	2. $\omega(g(n))\cap O(g(n))=\emptyset$

	- **Dimostrazione di 1.** per assurdo:
		Supponiamo che $\exists f(n)|\space o(g(n))\cap\Omega(g(n))$
		quindi:
		$\forall c>0,\space\exists n_0\in\mathbb{N}|\forall n\geq n_0:\space f(n)<c\cdot g(n)$
		e
		$\exists c'>0,\space \exists n_0'\in\mathbb{N}|\forall n \geq n_0':\space c'\cdot g(n)\leq f(n)$

		se $n\geq \max\{n_0, n_0'\}$ si avrebbe $f(n)<c'\cdot g(n)\leq f(n)$ <u>Assurdo!</u>

- Se $\lim\limits_{n\to\infty}\frac{f(n)}{g(n)}=\ell\space\text{con}\space 0<\ell<\infty$ allora $f(n)=\Theta(g(n))$
	versione generalizzata:
	$$\lim_{n\to\infty}\frac{f(n)}{g(n)}=\begin{cases}0\space (\iff f(n)=o(g(n))&\implies f(n)=O(g(n))\\\ell,\space \ell\in]0,\infty[&\implies f(n)=\Theta(g(n))\\\infty\space(\iff f(n)=\omega(g(n))&\implies f(n)=\Omega(g(n))\end{cases}$$
	Tuttavia questa osservazione non vale per funzioni il cui limite non è definito come $\sin,\cos...$ (questi casi non si verificheranno nel corso)	

### Polinomi
>[!Regola dei polinomi]
>Se $P(n)$ è un polinomio di grado $k$ allora $P(n)=\Theta(n^k)$

Esempi:
- $3n^3+2n^2+6n+5=\Theta(n^3)$
- $27n^2+n^2\log(n)+\sqrt{n}+\log(n^2) = \Theta(n^2\log(n))$
