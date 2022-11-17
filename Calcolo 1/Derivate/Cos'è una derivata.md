##### Preambolo
Se vogliamo scrivere una retta, la scriveremo come $y=mx+q$ se essa non è verticale, dove:
- $m$ è il coefficiente angolare (pendenza della retta);
- $q$ è l'intercetta.
Possiamo misurare $m$ come il rapporto tra la differenza delle ascisse e ordinate di due punti:
$$m=\frac{y_2-y_1}{x_2-x_1}=\tan \alpha$$
Indichiamo con $y=m(x-x_0)+y_0$ l'equazione del fascio di rette che passa per $y_0$.
Mentre se vogliamo trovare la retta che passa per due punti $p_0, p_1$ dovremmo usare la seguente formula: $$y=\frac{y_1-y_0}{x_1-x_0}(x-x_0)+y_0$$
Andiamo ad indicare il coefficiente angolare della retta secante tra due punti di una funzione con:
$$r(x)=\frac{f(x)-f(x_0)}{x-x_0}$$
Possiamo anche chiamare $r(x)$ **rapporto incrementale** di $f$ in $x_0$ con incremento $x-x_0$.

## Derivata
Con $f: A \subseteq \mathbb{R} \to \mathbb{R}; x_0 \in A$ ($x_0$ interno ad $A$)
$$\text{Se }\lim\limits_{x\to x_0}r(x)=\lim\limits_{x\to x_0}\frac{f(x)-f(x_0)}{x-x_0} \text{ esiste ed è finito}$$
Allora $f$ si dice derivabile in $x_0$ e la sua derivata è $f'(x_0) = \lim\limits_{x\to x_0}\frac{f(x)-f(x_0)}{x-x_0}$

Eseguendo la sostituzione $h=x-x_0$ avremmo che:
$$\lim\limits_{x\to x_0}\frac{f(x)-f(x_0)}{x-x_0} = \lim\limits_{h\to 0}\frac{f(x_0+h)-f(x_0)}{x-x_0}$$
- **Notazioni**: $f'(x_0); \quad \frac{df}{dx}; \quad D(f)$

![[Derivazione.svg||700]]
Al limite di $x \to x_0$ <u>la retta secante diventa la retta tangente al grafico</u> di $f$ in $x_0$.
l'**equazione della retta tangente** la possiamo calcolare ora tramite:
$$y=f'(x)(x-x_0)+f(x_0)$$
>[!Teorema (Derivabillità)]
>Con $f:A\subseteq \mathbb{R} \to \mathbb{R};$ $x_0$ interno ad $A$
>Supponiamo che:
>$$\lim\limits_{h\to 0^+}\frac{f(x_0+h) - f(x_0)}{h} = d\in \mathbb{R} \quad \text{ derivata dx}$$
>$$\lim\limits_{h\to 0^-}\frac{f(x_0+h) - f(x_0)}{h} = s\in \mathbb{R} \quad \text{ derivata sx}$$
>Allora $f$ è derivabile in $x_0$ se e solo se $d=s$.
>In tal caso $f'(x_0)=d=s$

>[!Example]
>**Trovare la derivata di $f(x)=x \quad D:\mathbb{R}; \quad x_0\in \mathbb{R}$**:
>$$\lim\limits_{x\to x_0}\frac{f(x)-f(x_0)}{x-x_0}=\lim\limits_{x\to x_0}\frac{x-x_0}{x-x_0} = 1$$

>[!Teorema (Continuità delle funzioni derivabili)]
>Se $f$ è derivabile in $x_0 \in A$ allora $f$ è continua in $x_0$ 
>>[!Attention]
>>Dal teorema possiamo dire che $f$ **non continua** in $x_0$ implica $f$ **non derivabile** in $x_0$.
>>- **ATTENZIONE**: $f$ continua in $x_0$ non implica $f$ derivabile in $x_0$, ad esempio $f=\sqrt{x}$ è continua ma non è derivabile (nel punto $0$ in questo caso), lo stesso per $f=|x|$


### Teorema di Lagrange
Avendo una funzione definita in un intervallo $[a,b]$ e derivabile in $]a,b[$ allora esiste un punto nell'intervallo $[a,b]$ la cui tangente è parallela alla retta che passa per $(a,f(a))$ e $(b,(fb))$.
$$f'(c)=\frac{f(b)-f(a)}{b-a}$$
![[Lagrange.png|300]]
### Teorema di Rolle
Il teorema di Rolle è una conseguenza del teorema di Lagrange.
Sia $f:[a,b] \to \mathbb{R}$ una funzione continua in $[a,b]$ e derivabile in $]a,b[$ tale che $f(a)=f(b)$, allora esiste un punto tale che $f'(c)=0$.

---
- Se due derivate sono uguali, allora le loro funzioni di partenza differiscono di una costante;
- Se $f'(x)>0$ allora $f(x)$ è strettamente crescente;
- Se $f'(x)<0$ allora $f(x)$ è strettamente decrescente.
---
