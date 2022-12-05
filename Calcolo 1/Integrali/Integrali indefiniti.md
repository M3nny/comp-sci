Chiamiamo **primitiva** ogni funzione derivabile tale che
$$F'(x)=f(x)$$
L'insieme di tutte le primitive di una funzione sono denotate con
$$\int f(x) dx = F(x)+c$$
- $c$ è costante e se $c = 0$ allora si chiama funzione primitiva fondamentale.

>[!Example]
>$$\int x\space dx= \frac{x^2}{2}+c, \quad c\in \mathbb{R}$$


## Algebra degli integrali

$$\int f(x) + g(x)\space dx = \int f(x)\space dx + \int g(x)\space dx$$
$$\int kf(x) \space dx = k\int f(x)\space dx$$
## Integrali elementari

|       **Funzione**       |      **Primitiva**      |
|:------------------------:|:-----------------------:|
|           $k$            |         $kx+c$          |
|          $x^a$           | $\frac{x^{a+1}}{a+1}+c$ |
|      $\frac{1}{x}$       |       $ln (x) +c$       |
|          $e^x$           |         $e^x+c$         |
|         $\sin x$         |       $-\cos x+c$       |
|         $\cos x$         |       $\sin x+c$        |
|   $\frac{1}{\cos^2x}$    |        $\tan x$         |
|   $\frac{1}{\sin^2 x}$   |      $-\cot x +c$       |
| $\frac{1}{\sqrt{1-x^2}}$ |      $\arcsin x+c$      |
|    $-\frac{1}{1-x^2}$    |     $\arccos x +c$      |
|    $\frac{1}{1+x^2}$     |      $\arctan x+c$      |


### Integrazione funzioni composte
$$\int f'(x) \cdot g'(f(x)) = g(f(x)) + c$$
>[!Example]
>$$\int (\sin x)^4 \cdot \cos x\space dx = \frac{\sin^5 x}{5}+c$$

### Integrazione per parti
La derivata $D(fg) = f'g +g'f$ da cui otteniamo
$$\int f'(x)g(x)\space dx = f(x)g(x) - \int g'(x)f(x)\space dx$$
>[!Example]
>$$\int x^2 ln(x) \space dx = \frac{x^3}{3}ln(x)-\int\frac{x^3}{3}\cdot \frac{1}{x} \space dx +c =$$
>$$=\frac{x^3}{3}ln(x)-\int \frac{x^2}{3}\space dx +c = \frac{x^3}{3}ln(x)- \frac{1}{3}\int x^2 \space dx = $$
>$$= \frac{x^3}{3}ln(x)- \frac{x^3}{9}$$

### Integrazione per sostituzione
In alcuni casi è meglio sostituire la radice (o altro) per facilitare i conti

>[!Example]
>$$\int \frac{x}{\sqrt{x-1}}\space dx$$
>- $t=\sqrt{x-1}$ 
>- $x=1+t^2$
>- $dx = dD(x) = 2tdt$
>$$\int \frac{t^2}{t}\space 2tdt = \int 2(1+t^2) \space dt =$$
>$$ = 2t+\frac{2}{3}t^3+c$$
>Sostituisco $x$ a $t$
>$$2\sqrt{x-1}+\frac{2}{3}\sqrt{(x-1)^3}+c$$

### Integrali di funzioni razionali
1. **Caso 1**: Il numeratore ha il grado maggiore o uguale a quello del denominatore
	- Si risolve facendo la divisione polinomiale prima di integrare.
2. **Caso 2**: Il numeratore ha grado minore del denominatore
	- Si risolve con il metodo $AB$.
