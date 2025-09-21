Si dice **equazione differenziale ordinaria** di ordine $n$:
$$F(t,y,y',y'',...,y^{(n)})=0$$
dove $t$ è la variabile indipendente, $y(t)$ è la funzione incognita e $F$ la funzione assegnata.
- L'**ordine** della EDO è dato dal massimo ordine di derivazione.
- La **soluzione** è data da $\phi :I \to \mathbb{R}$ derivabile almeno $n$ volte.
- Si dice **integrale generale** l'insieme di tutte le soluzioni
$$y(t)=ke^{\delta t},\space k\in \mathbb{R}$$

## EDO del primo ordine
La soluzione di questo tipo di EDO dipende da un parametro, possono avere le seguenti forme:
$$F(t,y,y')=0$$
$$y'(t)=f(t,y)\quad (\text{forma normale})$$
Si cerca una soluzione dell'EDO che soddisfi la condizione $y(t_0)=y_0$ (ovvero si impone il passaggio per il punto $(t_0,y_0)$ ).
Otteniamo così il **problema di Cauchy**:
$$\begin{cases}y'(t)=f(t,y)\\y(t_0)=y_0\quad (\text{valore iniziale assegnato})\end{cases}$$

>[!Teorema (esistenza e unicità)]
>Sotto opportune ipotesi su $f$ (per es. $f$ derivabile in $I$) allora esiste un'unica soluzione del problema di Cauchy.

>[!Example]
>$$\begin{cases}y'(t)=3y(t)\\y(0)=7\end{cases}$$
>Ricavo l'integrale generale, si vede che $y(t)=0$ non è una soluzione, per cui divido per $y(t)$ e integro:
>$$\int\frac{y'(t)}{y(t)}dt=\int 3 dt$$
>$$ln|y(t)|=3t+c \Rightarrow |y(t)|=e^{3t+c}=ke^{3t}$$
>$$y(t)=Ce^{3t},\space C\in\mathbb{R} \backslash \{0\}$$
>Ora per determinare $C$ impongo la condizione del problema di Cauchy:
>$$y(0)=7\Rightarrow \quad Ce^0=7\Rightarrow \quad C=7$$


## Equazioni a variabili separabili
Si dicono tali le EDO del primo ordine del tipo:
$$y'=a(t)b(y)$$
con $a, b$ funzioni continue.

1. **Soluzioni costanti**: trovo i valori per cui $b(y)=0$

2. Valuto poi le soluzioni **non costanti**, dove $b(y)\neq 0$ 
	$$y'=a(t)b(y) \xRightarrow{\text{separo le variabili}}\int\frac{1}{b(y)}dy=\int a(t)dt$$
	Risolvo gli integrali ed esplicito $y(t)$ dopo aver cambiato le variabili ($dy$ e $dt$)

>[!Example]
>$$y'(t)=(t-1)(y-1)$$
>1. **Soluzioni costanti**: $(y-1)=0$ quando $y(t)=1$
>2. **Soluzioni non costanti**: valuto per $y\neq 1$ 
>	$$\frac{y'}{y-1}=t-1 \xRightarrow{\text{integro}} \int\frac{y'}{y-1}dt=\int t-1 dt$$
>	$$\int\frac{1}{y-1}dy = \frac{t^2}{2}-t+c\quad c\in\mathbb{R}$$
>	$$ln|y-1|=\frac{t^2}{2}-t+c \quad |y-1|=e^{\frac{t^2}{2}-t+c}$$
>	$$y(t)=1\pm e^ce^{\frac{t^2}{2}-t}=ce^{\frac{t^2}{2}-t}, \quad c\in\mathbb{R}$$

## EDO lineari del primo ordine
Sono generalmente sotto la forma di:
$$y'+a(t)y=f(t) \quad (\spadesuit)$$

#### Omogenee
Nel caso $f(t) = 0$ allora l'equazione si dice **omogenea**, indichiamo in questo caso l'incognita con $z(t)$:
$$z'(t)a(t)z(t)=0 \xRightarrow{\text{ricavo la sol.}}z(t)=ce^{-\int a(t)dt}, \quad c\in\mathbb{R}$$
>[!Example]
>Avendo la seguente EDO lineare omogenea $z'-\sin(t) z=0$ la soluzione è data da $z(t)=ce^{-\cos(t)}$

#### Complete
Si dicono complete quando $f(t) \neq 0$ e sono quindi in forma $(\spadesuit)$, si possono risolvere quindi tramite la formula:
$$y(t)=ce^{-\int a(t)dt}+e^{-\int a(t)dt}\cdot \int e^{a(t) dt}\cdot f(t)dt, \quad c\in\mathbb{R}$$
Da cui possiamo distinguere la soluzione dell'equazione omogenea associata ($ke^{-\int a(t)dt}$) e la soluzione particolare data dal resto della formula.

>[!Example]
>Risolvere la seguente EDO lineare completa del primo ordine:
>$$y'-\sin(t) y = \sin(t)$$
>1. Sol. equazione omogenea associata: $z(t)=ce^{-\cos(t)}$
>2. Sol. particolare:
>$$\overline{y}(t) = e^{-\cos(t)}\int\sin(t) e^{\cos(t)}dt =$$
>$$= e^{-\cos(t)}(-e^{\cos(t)}) = -1$$
>Unendo le due soluzioni otteniamo l'integrale completo dell'EDO completa:
>$$y(t)=z(t)+\overline{y}(t)=ce^{-\cos(t)}-1, \quad c\in\mathbb{R}$$
>
>Trovare ora la soluzione tale per cui: $y(\pi)=1$
>$y(\pi)=ce^{-\cos(\pi)}-1=ce-1 \xRightarrow{\text{da cui}} ce-1=1$
>$$c=2e^{-1}$$
>La soluzione è:
>$$y(t)=2e^{-\cos(t)-1}-1$$

>[!Tip] Dominio di definizione
>Il più grande intervallo che contiene la condizione iniziale e per cui $y(t)$ sia di classe $c^1$  e soluzione dell'equazione differenziale.

## Concavità e pendenza della retta tangente
Non possiamo dire molto delle EDO non lineari, però possiamo determinare la concavità e la pendenza (della retta tangete) in un punto.

Nell'esempio seguente, l'equazione non è lineare in quanto ha $y^2$.
>[!Example]
>Determinare la concavità di $y$ vicino a $x=0$ e la pendenza della retta tangente vicino a $x=0$
>$$\begin{cases}3e^x-y^2\\y(0)=1\end{cases}$$
>- $y'(0)=3e^0-(y(0))^2=3-1^2=2$
>	dato che $2>0$ allora la retta tangente cresce.
>- $y''(x)=D[3e^x-(y(x))^2]=3e^x-2y(x)\cdot y'(x)$
>	la calcolo in $0$, per cui: $y''(0)=3e^0-2y(0)\cdot y'(0)=3-2\cdot 1 \cdot 2 = -1$
>	Dato che $-1<0$ avrà concavità verso il basso.

