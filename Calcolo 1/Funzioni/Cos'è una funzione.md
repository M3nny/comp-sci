# Funzioni
Siano $A$ e $B$ insiemi, $f$ è funzione da $A$ a $B$ se per ogni $x$ appartenente ad $A$ esiste <u>un solo</u> $y$ che appartiene a $B$.
![[Rappresentazione funzione.svg]]
- Indichiamo con $x$ la variabile **indipendente** e con $y$ la variabile **dipendente**.

## Il grafico
Il grafico di una funzione $f$ si indica con:
$$G(f)\subseteq D \times \mathbb{R}$$
Dove il grafico è un sottoinsieme del prodotto cartesiano tra il dominio $D$ e l'insieme dei numeri reali $\mathbb{R}$ messi in relazione da $f$:
$$G(f)=\{(x,y)\in \mathbb{R}^2:x\in D \land y=f(x)\}$$
![[Grafico.svg]]
## Immagine
- L'immagine della funzione è un sottoinsieme del <u>codominio</u> costituito dai valori assunti dalla funzione e si può scrivere come $Im(f)$ oppure $f(D)$.

Più formalmente la possiamo descrivere come:
$$Im(f)=\{y\in \mathbb{R}:\exists x\in D \space \text{per cui}\space y=f(x)\}$$
## Controimmagine
La controimmagine di un punto o intervallo di una funzione è non è altro che che la corrispettiva $x$ di $y$ e si indica con $f^{\leftarrow}(B)$.

Più formalmente possiamo definire la controimmagine come:
$$f^{\leftarrow}(B) = \{x \in D|f(x) \in B\}$$

>[!Example]
>### Esempio 1
>![[Controimmagine_es1.png]]
>### Esempio 2
>![[Controimmagine_es2.png]]

## Iniettiva, suriettiva, biettiva
- $f$ è **iniettiva** se $\forall  x_0\in B$ esiste _al massimo_ 1 elemento di $x_0 \in D$ tale che $f(x_0) = y_0$.
- $f$ è **suriettiva** se $\forall y_0 \in B$ esiste _almeno_ un $x_0\in D$ tale che $f(x_0)=y_0$.
- $f$ è **biettiva** se $\forall y_0\in B$ esiste _un solo_ $x_0 \in D$ tale che $f(x_0) = y_0$, (in altre parole è biettiva quando è sia iniettiva e suriettiva).

>[!Example]
>$$y=x^2 \quad f: \mathbb{R} \rightarrow \mathbb{R}$$
>![[Iniettiva.svg]]
>- Non è iniettiva perchè per le $y>0$ si ha più di un punto $y$ con lo stesso valore per 2 $x$ diversi.
>- Non è suriettiva perchè essendo il codominio $\mathbb{R}$ non esistono punti della funzione per le $y<0$

## Restrizioni 
Per ottenere una funzione biettiva è possibile restringere il dominio e codominio di una funzione, per esempio nella funzione precedente $y=x^2$, potremmo limitare il dominio e codominio ad $A=\mathbb{R}^+ \cup \{0\}$.
- Possiamo quindi scrivere una funzione ristretta in questo modo: $f_{|A}=g$
$$g: A \rightarrow A$$$$x \mapsto g(x)=x^2$$
- In questo modo otterremo solo il ramo destro superiore della parabola rendendo la funzione sia iniettiva che suriettiva e quindi biettiva.

## Funzioni monotone
- $f$ è **crescente** se $\forall x_1,x_2 \in D$ con $x_1 < x_2$ si ha che $f(x_1) \leq f(x_2)$.
![[Crescente.svg]]
- $f$ è **decrescente** se $\forall x_1,x_2 \in D$ con $x_1$ e $x_2$ si ha $f(x_1) \geq f(x_2)$.
![[Decrescente.svg]]
- $f$ è **strettamente crescente** se $f(x_1)<f(x_2)$.
- $f$ è **strettamente decrescente** se $f(x_1)> f(x_2)$.
- $f$ si dice **costante** se $f(D)$ ha un solo elemento.

Da notare che:
- $f$ <u>strettamente monotona è iniettiva</u> ma non sempre il contrario.





