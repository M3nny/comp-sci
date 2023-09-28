## Classe $O$
$$O(g(n))=\{f(n)|\exists c>0,\quad \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad f(n)\leq c\cdot g(n)\}$$
**Notazione**: $f(n)=O(g(n))$ 

>Il simbolo $=$ presente nelle notazioni significa "appartiene a"

Per $n$ sufficientemente grande $f(n)$ sarà sempre _sotto_ ad una funzione $g(n)$ moltiplicata per una costante positiva $c$.

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

Per $n$ sufficientemente grande $f(n)$ sarà sempre _sopra_ ad una funzione $g(n)$ moltiplicata per una costante positiva $c$.

>[!Example]
>$\frac{1}{2}n^2-3n=\Omega(n^2)$
>$$\exists c>0, \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad c\cdot n^2\leq\frac{1}{2}n^2-3n\iff$$
>$$c\cdot n\leq\frac{1}{2}n-3\quad\iff\quad n(\frac{1}{2}-c)\geq 3$$
>$(\frac{1}{2}-c)$ deve essere $>0$ e anche essere positivo, quindi $0<c<\frac{1}{2}$ si ha quindi:
>$$n\geq\frac{3}{\frac{1}{2}-c}=\frac{6}{1-2c}$$
>Scelgo $c=\frac{1}{14}$ e sostituendo ottengo $n\geq\frac{6}{1-\frac{1}{7}}=7$
>Quindi avrò come soluzioni: $c=\frac{1}{14}$ e $n_0=7$

## Classe $\Theta$ ($O\cap \Omega$)
$$\Theta(g(n))=\{f(n)|\exists c_1>0,\exists c_2>0\quad \exists n_0\in\mathbb{N}|\forall n \geq n_0:\quad c_1\cdot g(n)\leq f(n)\leq c_2\cdot g(n)\}$$
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

---
