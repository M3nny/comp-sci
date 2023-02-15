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

1. **Soluzioni costanti**: trovo i valori per cui $y'=0$
	$y'=(t-1)(y-1)$ la sol. costante è $1$

2. Assumiamo $b(y)\neq 0$ 
	$$y'=a(t)b(y) \xRightarrow{\text{separo le variabili}}\frac{y'(t)}{b(y(t))}=a(t)$$
	Risolvo gli integrali ed esplicito $y(t)$ dopo aver cambiato le variabili ($dy$ e $dt$)

>[!Example]
>$$y'(t)=(t-1)(y-1)$$
>1. Sol. costante: $1$
>2. valuto per $y\neq 1$ 
>	$$\frac{y'(t)}{y(t)-1}=t-1 \xRightarrow{\text{integro}} \int\frac{y'(t)}{y(t)-1}dt=\int t-1 dt$$
>	$$\int\frac{1}{y-1}dy = \frac{t^2}{2}-t+c\quad c\in\mathbb{R}$$
>	$$ln|y-1|=\frac{t^2}{2}-t+c \quad |y-1|=e^{\frac{t^2}{2}-t+c}$$
>	$$y(t)=1\pm e^ce^{\frac{t^2}{2}-t}$$

