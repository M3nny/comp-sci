Una EDO del secondo ordine si presenta come segue:
$$a_2(t)y'' + a_1(t)y' + a_0(t)y = g(t)$$
Nota che $a(t), b(t)$ nel nostro corso saranno a coefficienti costanti.

Per cui otteniamo la **forma normale**:
$$y'' + ay' + by = f(t)$$
Da cui otteniamo l'**equazione omogenea a coefficienti costanti** associata:
$$y'' + ay' + by = 0$$
- Se $z_1$ e $z_2$ sono soluzione dell'equazione omogenea associata allora qualsiasi combinazione lineare $\alpha z_1 + \beta z_2$ è soluzione, con $\alpha , \beta \in\mathbb{R}$.

#### Problema di Cauchy
$$\begin{cases}y''+ay'+by=f(t)\\y(t_0)=y_0\\y'(t_0)=v_0\end{cases}$$
#### Problema di bordo
$$\begin{cases}y''+ay'+by=f(t)\\y(t_1)=y_1\\y(t_2)=y_2\end{cases}$$
Le soluzioni sono date da:
$$y(t)=c_1z_1(t)+c_2z_2(t)+\overline{y}(t)$$
dove $\overline{y}(t)$ è la _soluzione particolare_ mentre $c_1z_1(t)+c_2z_2(t)$ è la soluzione dell'equazione omogenea.

1. Scriviamo **l'equazione caratteristica** dell'EDO di secondo ordine:
$$\lambda^2+a\lambda+b=0$$
2. Ora bisogna calcolare il discriminante ($\Delta$) tramite $a^2-4b$

3. Con il risultato di $\Delta$ andiamo a determinare come calcolare la/le soluzioni.

- $\Delta > 0:$ Si hanno due soluzioni reali distinte:
$$r_{1,2}=\frac{-a\pm\sqrt{\Delta}}{2}$$
per trovare l'integrale generale sostituiamo $r_{1,2}$ dentro a:
$$z(t)=c_1e^{r_1t}+c_2e^{r_2t}$$
  
  >[!Example]
  >$$z''(t)+2z'(t)-3z(t)=0 \quad \Rightarrow \quad  r^2 +2r  -3=0$$
  >$$\Delta = 16 \quad \Rightarrow \quad r_{1,2}=\frac{-2\pm 4}{2}=(1,-3)$$
  >L'integrale generale è dato da:
  >$$z(t)=c_1e^t+c_2e^{-3t}$$

- $\Delta = 0:$ Esiste un'unica soluzione reale ed una linearmente indipendente da $z_1$.
$$r=-\frac{a}{2}$$

l'integrale generale è dato da:
$$z(t)=c_1e^{r_1t}+c_2te^{r_1t}$$
>[!Example]
>$$z''(t)+2\sqrt{3}z'(t)+3t(t)=0 \quad \Rightarrow \quad r^2 +2\sqrt{3}r+3=0$$
>$$\Delta=0 \quad \Rightarrow \quad r_1=r_2=-\sqrt{3}$$
>L'integrale generale è dato da:
>$$z(t)=c_1e^{-\sqrt{3}t}+c_2te^{-\sqrt{3}t}$$

- $\Delta < 0:$ Esistono due soluzioni complesse coniugate, l'integrale generale trattato di seguito userà dei valori per cui le soluzioni appartengono ai numeri reali.
$$r_{1,2}=\frac{-a\pm i\sqrt{|\Delta|}}{2}$$
l'integrale generale è dato da:
$$z(t)=c_1e^{\alpha t}\cos(\beta t)+c_2e^{\alpha t} \sin(\beta t)$$
>[!Example]
>$$z''(t)+2z'(t)+3z(t)=0 \quad \Rightarrow \quad r^2 +2r + 3 = 0$$
>$$\Delta = -8 \quad \Rightarrow \quad r_{1,2}=\frac{-2\pm i\sqrt{8}}{2}=-1\pm i\sqrt{2}$$
>Da cui otteniamo $\alpha = -1$ e $\beta = \sqrt{2}$
>L'integrale generale è dato da:
>$$z(t)=c_1e^{-t}\cos(\sqrt{2}t)+c_2e^{-t}\sin(\sqrt{2}t)$$

---
## Complete
Con il **metodo di somiglianza** ricerchiamo $\overline{y}(t)$ tra le funzioni che 'assomigliano' a $f(t)$.

#### $f(t) =$ Polinomio
>[!Example]
>$$y''+3y'-y=2t^2-1$$
>Cerco $\overline{y}(t)$ tra i polinomi di grado 2.
>- $\overline{y}(t) = At^2+Bt+C$
>- $\overline{y}'(t)=2At+B$
>- $\overline{y}''(t)=2A$
>**Sostituisco**:
>$$2A+3(2At+B)-(At^2+Bt+C)=2t^2-1$$
>$$-At^2+t(6A-B)+2A+3B-C=2t^2-1$$
>Ora metto a sistema il confronto tra i coefficienti $t^x$, ad esempio qua abbiamo che i coefficienti di -$At^2$ che saranno messi a confronto con $2t^2$, dato che non esiste un $t^1$ i coefficienti di $t(6A-B)$ saranno confrontati con $0$.
>$$\begin{cases}-A=2\\6A-B=0\\2A+3B-C=-1\end{cases}\quad\Rightarrow\quad\begin{cases}A=-2\\B=-12\\C=-39\end{cases}$$
>Abbiamo che la soluzione particolare è:
>$$\overline{y}(t)=-2t^2-12t-39$$
>mentre la soluzione dell'equazione omogenea si troverà con il metodo del discriminante ($\Delta$).
>L'integrale generale sarai poi dato da:
>$$y(t)=c_1z_1(t)+c_2z_2(t)-2t^2-12t-39$$

#### I polinomi hanno grado diverso
>[!Example]
>$$y''+3y'=2t^2-1$$
>In questo caso manca $y$ per cui i polinomi non potranno mai essere uguali.
>Vediamolo meglio sostituendo.
>- $\overline{y}(t) = At^2+Bt+C$
>- $\overline{y}'(t)=2At+B$
>- $\overline{y}''(t)=2A$
>$$2A+3(2At+B)=2t^2-1$$
>In questo caso mi manca un $t^2$ a sinistra quindi procedo sostituendo un polinomio di grado 3.
>- $\overline{y}(t) = At^3+Bt^2+Ct+D$
>- $\overline{y}'(t)=3At^2+2Bt+C$
>- $\overline{y}''(t)=6At+2B$
>**Sostituisco**:
>$$6At+2B+3(3At^2+2Bt+C)=2t^2-1$$
>$$9At^2+t(6A+6B)+2B+3C=2t^2-1$$
>Ora confronto i coefficienti:
>$$\begin{cases}9A=2\\6A+6B=0\\2B+3C=-1\end{cases}$$
>Ora procedo analogamente al caso precedente.

#### $f(t)$ è esponenziale
>[!Example]
>$$y''+3y'-y=2e^{-t}$$
>- $\overline{y}(t) = Ae^{-t}$
>- $\overline{y}'(t)=-Ae^{-t}$
>- $\overline{y}''(t)=Ae^{-t}$
>**Sostituisco**:
>$$Ae^{-t}-3(-Ae^{-t})+2Ae^{-t}=2e^{-t}$$
>$$A+3A+2A=2\quad\Rightarrow\quad A=\frac{1}{3}$$
>La soluzione particolare è quindi data da:
>$$\overline{y}(t)=\frac{1}{3}e^{-t}$$

#### $f(t)$ compare nella sol. omogenea
Se $f(t)$ compare nella sol. omogenea, avremo sostituendo che $0=f(t)$  che è assurdo.
>[!Example]
>$$y''-3y'+2y=2e^t$$
>- $\overline{y}(t)=\overline{y}'(t)=\overline{y}''(t)=Ae^t$
>Vediamo ora che sostituendo otteniamo $0=f(t)$ (Assurdo).
>$$Ae^t-3Ae^t+2Ae^t=0\neq2e^t$$
>Questo succede per colpa della sol. dell'equazione omogenea:
>$$\lambda ^2-3\lambda +2=0\quad\Rightarrow\quad\Delta=1\quad\Rightarrow\quad\lambda_{1,2}=2,1$$
>Da cui ottengo $z_1(t)=e^t$ e $z_2(t)=e^{2t}$  vediamo difatti di che $e^t$ compare in $f(t)$.
>In questo caso si moltiplica davanti per $t$:
>- $\overline{y}(t)=Ate^t$
>- $\overline{y}'(t)=Ae^t+Ate^t$
>- $\overline{y}''(t)=Ae^t+Ae^t+Ate^t=2Ae^t+Ate^t$
>**Sostituisco** (se è andato tutto bene, i termini con $t$ si annullano):
>$$2Ae^t+Ate^t-3Ae^t-3Ate^t+2Ate^t=2e^t$$
>$$-Ae^t=2e^t\quad\Rightarrow\quad A=-2$$
>La sol. particolare è data da:
>$$\overline{y}(t)=-2te^t$$

#### Il discriminante della sol. omogenea è $\Delta = 0$
>[!Example]
>$$y''-2y'+y=3e^{-t}$$
>Osserviamo che l'eq. caratteristica $\lambda^2-2\lambda+1=(\lambda-1)^2$ per cui $\Delta=0$ e $\lambda_{1,2}=1$
>$$z_1(t)=e^t;\space z_2(t)=te^t$$
>Ora valuto le esponenziali aumentando la $t$ davanti di un grado.
>- $\overline{y}(t)=At^2e^t$
>- $\overline{y}'(t)=2Ate^t+At^2e^t$
>- $\overline{y}''(t)=2Ae^t+2Ate^t+2Ate^t+At^2e^t$
>**Sostituisco** (se è andato tutto bene, i termini con la $t$ si annullano):
>$$2Ae^t+4Ate^t+At^2e^t-4Ate^t-2At^2e^t+At^2e^t=3e^t$$
>$$2Ae^t=3e^t\quad\Rightarrow\quad A=\frac{3}{2}$$
>La sol. particolare è data da:
>$$\overline{y}(t)=\frac{3}{2}t^2e^t$$
>L'integrale generale è dato da:
>$$y(t)=c_1e^t+c_2te^t+\frac{3}{2}t^2e^t$$

#### $f(t)$ è trigonometrica
Si presenta come segue:
$$f(t)=k_1\sin(\omega t)+k_2\cos(\omega t)$$
>[!Example]
>$$y''-4y'-12y=\sin(2t)+3\cos(2t)$$
>- $\overline{y}(t)=A\sin(2t)+B\cos(2t)$
>- $\overline{y}'(t)=A2\cos(2t)+B(-2\sin(2t))$
>- $\overline{y}''(t)=-4A\sin(2t)-4B\cos(2t)$
>**Sostituisco**:
>$$-4A\sin(2t)-4B\cos(2t)-4(2A\cos(2t)-2B\sin(2t))-12(A\sin(2t)+B\cos(2t))$$
>$$\sin(2t)(-4A+8B-12A)+\cos(2t)(-4B-8A-12B)=\sin(2t)+3\cos(2t)$$
>$$\sin(2t)(-16A+8B)+\cos(2t)(-8A-16B)=\sin(2t)+3\cos(2t)$$
>Anche in questo caso si ottiene un sistema confrontando i coefficienti di $\cos(\omega t)$ e $\sin(\omega t)$
>$$\begin{cases}8-16A+8B=1\\-8A-16B=3\end{cases}\quad\Rightarrow\quad\begin{cases}A=-\frac{1}{8}\\B=-\frac{1}{8}\end{cases}$$
>La sol. particolare è data da:
>$$\overline{y}(t)=-\frac{1}{8}\sin(2t)-\frac{1}{8}\cos(2t)$$

Con questo tipo di $f(t)$ se $\cos(\omega t)$ e $\sin(\omega t)$ sono soluzioni dell'equazione omogenea associata, allora la soluzione particolare è del tipo:
$$f(t)=k_1t\sin(\omega t)+k_2t\cos(\omega t)$$
## Sovrapposizione degli effetti
Questo modo di risolvere le differenziali funziona anche con quelle di primo ordine e consiste nel trovare 2 o più soluzioni particolari nel caso di EDO del tipo:
$$y''+ay'+by=f_1(t)+f_2(t)$$
1. Trovo $\overline{y}_1(t)$ di $y''+ay'+by=f_1(t)$
2. Trovo $\overline{y}_2(t)$ di $y''+ay'+by=f_2(t)$
3. $\overline{y}(t)$ è dato da:
$$\overline{y}(t)=\overline{y}_1(t)+\overline{y}_2(t)$$
