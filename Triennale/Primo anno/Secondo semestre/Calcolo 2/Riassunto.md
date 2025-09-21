## Equazioni differenziali

### Primo ordine
- $y'=f(x)$:   $y=\int f(x)\space dx$
- $y'=g(x)\cdot h(y)$:
	1. Si separano le variabili e si integra rispettivamente per $y$ e per $x$
	2. Si esaminano a parte i casi derivanti da $h(y)=0$
- $y'=a(x)\cdot y+b(x)$, con $b(x)=0$:
	1. Si risolve come nel caso a variabili separabili, oppure si usa la formula: $y=ke^{\int a(x)\space dx}$
- $y'=a(x)\cdot y+b(x)$, con $b(x)\neq 0$:
	1. $y=e^{\int a(x)\space dx}\left[\int b(x)\cdot e^{-\int a(x)\space dx}\space dx + c\right]$

1. Si trova la soluzione costante dell'equazione ($h(y)=0$)
2. Si trova il dominio di $h(y)$
3. Si guarda per quali valori $x$ è uguale a $h(y)=0$ (ovvero i valori di $x$ che rendono $y = 0$, di solito c'è la $x$ a sinistra dell'= che elimina $y'$)
4. Prima di integrare bisogna scrivere: "si considera $y\neq ...$ e $x\neq...$"
5. Se la sol. costante non è compresa dopo aver fatto gli integrali, allora bisogna aggiungerla tramite una somma della sol. costante

- **Cauchy**: trovare la sol. che soddisfi la condizione iniziale $y(a)=b$
	1. Bisogna prendere il tratto di funzione che comprende $b$ e sostituire a $x\rightarrow a$ ed a $y\rightarrow b$  
	2. La soluzione è data sostituendo al tratto usato precedentemente $c$ appena trovato, bisogna anche specificare l'intervallo del dominio a cui appartengono le $x$, facendo attenzione a quali $x$ avevamo negato all'inizio dell'equazione differenziale.

>Con cauchy, fare attenzione se viene chiesto di calcolarlo in $y(a)=b$ dove $b$ è la sol. costante trovata all'inizio, in questo caso bisogna scrivere "bisogna considerare la sol. costante $y(x)=b$" la quale poi avrà anche dominio $\mathbb{R}$.
>Se invece si ha $a$ che è uguale ad una $x$ scartata all'inizio allora bisognerà scrivere che non ci sono soluzioni per $x=a$
>


### Secondo ordine
$$y''+ay'+by=r(x)$$
1. Trovare le radici reali tramite $\Delta$ ($b^2-4ac$)
2. Determinare l'equazione omogenea $z(x)$ in base al risultato di $\Delta$:
| **Risultato $\Delta$** |                           **Radici**                           |                     **Equazione omogenea**                     |
|:----------------------:|:--------------------------------------------------------------:|:--------------------------------------------------------------:|
|      $\Delta > 0$      |             $r_{1,2}=\frac{-b\pm\sqrt{\Delta}}{2a}$             |                  $z(x)=c_1e^{r_1x}+c_2e^{r_2x}$                   |
|      $\Delta = 0$      |                        $r=-\frac{b}{2a}$                        |                    $z(x)=c_1e^{rt}+c_2te^{rt}$                    |
|      $\Delta < 0$      | $r_{1,2}=\frac{-b\pm i\sqrt{\|\Delta\|}}{2a}$ (valore assoluto) | $z(x)=c_1e^{\alpha t}\cos(\beta t)+c_2e^{\alpha t} \sin(\beta t)$ |

3. Trovare la soluzione particolare $y_0$:
	- $r(x)$ è un polinomio:
		- se $c\neq 0 \implies$ $y_0$ è un polinomio di grado $n$ ([[EDO del secondo ordine#Stesso grado|esempio]])
		- se $c=0$ e $b\neq 0\implies$ $y_0$ è un polinomio di grado $n+1$ ([[EDO del secondo ordine#Grado diverso|esempio]])
	- $r(x)=s(x)e^{\alpha x}$:
		- se $\alpha\neq r_{1,2}\implies y_0=p(x)e^{\alpha x}$ ([[EDO del secondo ordine#$e {ax}$ non compare nell'omogenea|esempio]])
		- se $\alpha = r_1 \lor \alpha = r_2\implies y_0=p(x)te^{\alpha x}$ ([[EDO del secondo ordine#$e {ax}$ compare nella omogenea|esempio]])
		- se $\alpha = r_1 = r_2\implies y_0=p(x)t^2e^{\alpha x}$ ([[EDO del secondo ordine#$e {ax}$ è uguale alle sol. coincidenti dell'omogenea|esempio]])
	- $r(x)=k_1t\sin(\omega t)+k_2t\cos(\omega t)$:
		- ([[EDO del secondo ordine#Trigonometrica|esempio]])
4. Sostituire le derivate della sol particolare nella funzione iniziale
5. L'integrale generale $y(x)$ sarà dato da  $y_0+z(x)$

**Cauchy**: si ha $y(a)=b$ e $y'(a)=b$
	1. Trovare la derivata dell'integrale generale
	2. Sostituire a $x\rightarrow a$ rispettivamente a $y$ e $y'$ e porre la funzione di base e quella derivata in uguaglianza con il corrispettivo $b$
	3. Mettere a sistema le due uguaglianze e trovare $c_{1,2}$
	4. Sostituire $c_{1,2}$ all'interno dell'integrale generale

---
## Curve parametriche
$$r(t)=\begin{cases}r_1(t)=(t_1,t_2)&\text{se }t\in[a,b];\\r_2(t)=(t_3,t_4)&\text{se }t\in[c,d];\end{cases}$$
Come verificare le proprietà di una curva:
- **Continua**: composta da funzioni continue, se è definita a tratti allora deve anche valere $r_1(b)=r_2(c)$
- **Chiusa**: $r_1(a)=r_2(d)$
- **Semplice**: deve essere continua e non deve intersecarsi (tranne nell'inizio e fine al massimo), non basta che $r_1$ e $r_2$ siano se stesse semplici, ma poi deve anche valere che $r_1$ non si interseca con $r_2$, (occhio agli esponenti pari ed ai valori assoluti).
	Se è in forma polare è semplice perchè il raggio cresce
![[Verifica curva semplice.png]]
- **Regolare**: la derivata deve esistere, essere continua e non deve annullarsi
	1. trovare i due vettori tangenti ai due tratti di curva facendo la derivata delle quattro funzioni che determinano i due punti di ciascun tratto di curva, spezzando adeguatamente se l'intervallo del tratto comprende lo $0$ in quanto lo $0$ non è definito nel vettore tangente. (nota: se compare il $|t|$ bisogna divedere a tratti il punto considerando la derivata con $+t$ e $-t$ ).
	2. Controllare che i due tratti derivati siano continui
	3. Scrivere infine gli intervalli in cui è regolare (evitando lo $0$ quindi)

>Se una delle due componenti che determinano il punto di un tratto non si annulla (valore costante) allora quel tratto è regolare (tranne se comprende lo 0).

- **Equazione cartesiana della curva (supporto)**:
	1. Porre a sistema $\begin{cases}x=t_1\\y=t_2\end{cases}$ (equazione parametrica) , isolare $t$ e sostituire
	2. L'insieme in cui è definito ($[...,...]$) cambia, bisogna vedere il dominio della funzione a destra della $t$ isolata e combinarlo con quello originale (prendere gli estremi più piccoli)
		- nota: si ha un segmento rettilineo se $x$ o $y$ sono $=0$ 

> Guardare spostamenti/traslazioni di funzioni per disegnare il supporto.
> Se fatto bene risolve tutto l'esercizio

- **Retta tangente a $\gamma$ in $x_0$:
	1. Individuo quale tratto contiene $x_0$ 
	2. Trovo la derivata del tratto di curva parametrica $r'(t)$ 
	3. Sostituisco $x_0$ in $r(t)$ e $r'(t)$ ottenendo così due punti
	4. L'equazione cartesiana della retta tangente è data da $\begin{cases}x=r(t_0)+r'(t_0)(t-t_0)\\y=r(t_0)+r'(t_0)(t-t_0)\end{cases}$ dove nella prima equazione si usa la coordinata $x$ del punto trovato, mentre nella seconda la coordinata $y$.

- **Calcolare l'integrale curvilineo**:
	1. Calcolo il dominio della funzione e vedo se al suo interno è compreso il sostegno specificato (guardando il grafico)
	2. Applico la formula: $\int^b_a f(r(t))\cdot||r'(t)||dt$ dove $a,b$ sono gli estremi del tratto di curva di cui si vuole calcolare l'integrale.
- **Calcolare la lunghezza della curva**: $\int^b_a||r'(t)||$ 

---
## Funzioni a più variabili
>Lo studio del segno per la sezione $x=...$ è invertito, negli intervalli in cui è indicato che è positivo il grafico, in realtà è negativo (usando come asse verticale $z$ e orizzontale $y$.


- **Trovare il dominio**: considerare il polinomio elevato al quadrato:
$$4x^2+y^2+12y>0\quad \Rightarrow\quad(y+1)^2+4x^2>1$$
- **Piano tangente**: $$T(x,y)=f(x_0,y_0)+[f_x(x_0,y_0)](x-x_0)+[f_y(x_0,y_0)](y-y_0)$$
- **Derivata direzionale**: $$f_x(x_0,y_0)\cdot v_{x_0}+f_y(x_0,y_0)\cdot v_{y_0}$$
- **Versore di massima crescita**: 
> Prima di fare il calcolo controllare che il punto in questione non sia un punto critico, perchè se lo fosse, il gradiente sarebbe nullo e non esisterebbe il versore di massima crescita (evitando così di fare conti)

$$v=\frac{\nabla f(x_0,y_0)}{||\nabla f(x_0,y_0)||} = \frac{1}{\sqrt{[f_x(x_0,y_0)]^2+[f_y(x_0,y_0)]^2}}\cdot\begin{pmatrix}f_x(x_0,y_0)\\f_y(x_0,y_0)\end{pmatrix}$$ il risultato sarà in forma di $(P_1, P_2)$

- **Sviluppo di taylor 1° ordine(piano tangente)+2° ordine**:
$$f(x_0,y_0)+[f_x(x_0,y_0)](x-x_0)+[f_y(x_0,y_0)](y-y_0)+$$
$$+\frac{1}{2}([f_{xx}(x_0,y_0)](x-x_0)^2+2[f_{xy}(x_0,y_0)](x-x_0)(y-y_0)+[f_{yy}(x_0,y_0)](y-y_0)^2)$$
- **Caratterizzazione punti critici**:
	1. $\begin{cases}f_x=0\\f_y=0\end{cases}$ trovo gli zeri per una della due funzioni e poi vado a sostituire nell'altra (controllare che il punto completo appartenga al dominio)
	2. $H_f=\begin{pmatrix}f_{xx}&f_{xy}\\f_{xy}&f_{yy}\end{pmatrix}$ 
	3. Sostituisco nell'Hessiana i punti critici e trovo il determinante: $det\begin{pmatrix}a&b\\c&d\end{pmatrix}=(a\cdot d)-(b\cdot c)$ 
	4. Eseguo il test:
		- $det(H)<0$: punto di sella
		- $det(H)>0$:
			- $a>0$ minimo
			- $a<0$ massimo
			- $a=0$ punto di sella
		- $det(H)=0$ non definibile con questo metodo

---
## Integrali doppi
Se viene fuori $0$ all'interno di un integrale doppio, l'integrale esterno sarà uguale a $0$.

- **Dominio**: quando scrivo gli estremi per $x$ devo scrivere funzioni in funzione di $x$, lo stesso per $y$
- **Baricentro**:$$(x_c,y_c)=\left(\frac{\int\int_Dx\space dxdy}{\text{Area}},\frac{\int\int_Dy\space dxdy}{\text{Area}}\right)$$
- **Forma polare** (usata per circonferenze):$$\begin{cases}x=\rho\cos(\theta)\\y=\rho\sin(\theta)\end{cases}$$
	- $\rho$: lunghezza raggio (prendere positiva, relativa al centro)
	- $\theta$ dove è compresa la circonferenza (indicando con radianti)
>Quando si calcola l'integrale con la forma polare ricordarsi di moltiplicare per $\rho$ (risultato dalla Jacobiana)
![[Grad Rad.png|500]]


---
## Info generali
- **Retta tra due punti**: $$\frac{x-x_1}{x_2-x_1}=\frac{y-y_1}{y_2-y_1}$$
- **Distanza tra due punti**:$$\sqrt{(x_2-x_1)^2+(y_2-y_1)^2}$$
- **Formule trigonometriche**:
	- $\cos(\theta)\sin(\theta)=\frac{1}{2}\sin(2\theta)\quad(\int =-\frac{\cos(2\theta)}{4})$ 

>[!Tip]
>$$\text{Circonferenza}$$
>Si presenta come $(x-x_0)^2+(y-y_0)^2=r^2$
>- Centro: $(x_0,y_0)$
>- Raggio: $r$
>$$\text{Elisse}$$
>Si presenta come: $\frac{(x-x_0)^2}{a^2}+\frac{(y-y_0)^2}{b^2}=1$
>- Centro: $(x_0,y_0)$
>- Semiasse orizzontale: $a$
>- Semiasse verticale: $b$
	 
- **Integrali difficili**:
	- $\int\sqrt{1-x^2}dx=\int\sqrt{1-\cos^2(\theta)}\cdot -\sin(\theta)d\theta = \int\sin^2(\theta)d\theta=\frac{\theta}{2}-\frac{\sin(2\theta)}{4}$ 
	- $\int\sqrt{1-y^2}dy=-\frac{\theta}{2}-\frac{\sin(2\theta)}{4}$ 
	- $\int y\sqrt{1-y^2}=\frac{\cos^3(\theta)}{3}$
		(dove gli estremi dell'integrale vanno cambiati in modo che quando messi dentro al $\sin(x)$ risultino uguali a prima, quindi gli estremi saranno dei radianti)
