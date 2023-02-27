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