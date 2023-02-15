#### Derivate di ordine superiore
$f: A\to \mathbb{R}$ si dice derivabile 2 volte se $f$ è derivabile in $A$ e $f'$ è derivabile in $A$.

#### Insiemi di funzioni derivabili
Indichiamo con $\mathcal{C}^k(I)$ la classe (o insieme) delle funzioni derivabili $k$ volte dove l'ultima derivata ($k$ esima) è continua sull'intervallo $I$ che è a sua volta contenuto in $\mathbb{R}$.
- $\mathcal{C}^0(I)=\{f: I\to \mathbb{R} | f \text{ continua}\}$
- $\mathcal{C}^1(I)=\{f: I\to \mathbb{R} | f \text{ derivabile e }f' \text{ continua}\}$
- $\mathcal{C}^k(I)=\{f: I\to \mathbb{R} | f \text{ derivabile } k \text{ volte e }f^{k} \text{ continua}\}$
- $\mathcal{C}^\infty(I)=\{f: I\to \mathbb{R} | f \text{ derivabile } k \text{ volte per ogni } k\in\mathbb{N}\}$ 
>$\cos x,\sin x,$ polinomi $P_n(x),e^x$ sono funzioni di classe $c^{\infty}$ su $\mathbb{R}$.

## Concava e convessa
![[Concava Convessa.svg]]
- Una funzione è **concava** in $I$ se per ogni coppia di punti, la retta che li congiunge si trova al di sopra del grafico di $f$ per ogni punto $x\in ]x_1,x_2[$ 
- Si dice **convessa** in $I$ se la retta è sotto al grafico di $f$.

>[!Verificare se la funzione è concava o convessa]
>$f:I\to \mathbb{R}$ derivabile due volte.
>- Se $f''(x)\leq 0 \quad \forall x \in \mathring{I}$ allora $f$ è **concava**
>- Se $f''(x)\geq 0 \quad \forall x \in \mathring{I}$ allora $f$ è **convessa**

### Concavità, convessità locale e punti di flesso
![[Localmente conc.svg]]
La retta tangente per un punto $x_0$ la ricaviamo tramite:
$$t(x)=f'(x_0)(x-x_0)+f(x_0)$$
- $f$ è **localmente concava** in $x_0$ se $\exists I_{x_0}$ tale che $f(x)\leq t(x) \quad \forall x \in I_{x_0}$
- $f$ è **localmente convessa** in $x_0$ se $\exists I_{x_0}$ tale che $f(x)\geq t(x) \quad \forall x \in I_{x_0}$
- $x_0$ si dice **punto di flesso** se alla sua sinistra la funzione è _concava_ mentre alla sua destra è _convessa_, o viceversa.

>[!Verificare se in un punto la funzione è concava, convessa oppure ha un punto di flesso]
>$f:I\to \mathbb{R}$ derivabile due volte.
>- Se $f''(x_0) < 0$ allora $f$ è **concava** in $x_0$
>- Se $f''(x_0) > 0$ allora $f$ è **convessa** in $x_0$
>- Se $f''(x_0) = 0$ allora $x_0$ è un **punto di flesso** (cambio concavità)
