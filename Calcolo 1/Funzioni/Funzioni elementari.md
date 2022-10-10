# Funzioni elementari
Sono funzioni di cui il grafico è noto.

## Funzioni potenza

### Potenza con esponente intero

$$\begin{split} f\colon &D \to \mathbb{R}\newline &x \mapsto f(x)=x^n \end{split}$$
 $$
	D=\mathbb{R};\quad Im(f)=
	\begin{cases}
	      [0, +\infty[ \space &\text{ se n pari} \neq 0;\\
	      \mathbb{R} &\text{ se n dispari.}
	\end{cases}
$$
![[Potenza naturale.png]]
Con esponente:
- **Pari**: la funzione è strettamente crescente in $[0, +\infty[$ 
- **Dispari**: la funzione è strettamente crescente in $\mathbb{R}$

### Potenza con esponente intero negativo
$$f(x)=x^{-n}=\frac{1}{x^n}$$
$$D=\mathbb{R^*};\quad Im(f)=
	\begin{cases}
	      ]0, +\infty[ \space &\text{ se n pari} \neq 0;\\
	      \mathbb{R^*} &\text{ se n dispari.}
	\end{cases}$$
![[Potenza negativa.png]]

### Potenza con esponente $\frac{1}{n}$
$$f(x)=x^{\frac{1}{n}}=\sqrt[n]{x}$$
Con esponente:
- **Pari**: $D=[0, +\infty[;\quad Im(f)=[0, +\infty[$ 
- **Dispari**: $D=\mathbb{R};\quad Im(f)=\mathbb{R}$ 
![[Potenza naturale 1suN.png]]

### Potenza con esponente razionale
$$f(x)=x^{\frac{m}{n}}=\sqrt[n]{x^m}$$
Con esponente:
- $\frac{m}{n}>0$:   $D=[0, +\infty[;\quad Im(f)=[0,+\infty[$
- $\frac{m}{n}<0$:   $D=]0, +\infty[;\quad Im(f)=]0,+\infty[$
![[Potenza razionale.png]]

>[!Info]
>I domini e le immagini precedenti valgono anche per le **potenze con esponente reale**.

---

## Funzioni esponenziali
Definiamo esponenziale una funzione con $a\in \mathbb{R}^+$ con $a>0$:
$$\begin{split} f\colon &\mathbb{R} \to \mathbb{R}\newline &x \mapsto f(x)=a^x \end{split}$$
![[Esponenziale.png]]
>[!Important]
>Per le funzioni esponenziali valgono le seguenti **proprietà**:
>- assumono solo valori positivi
>- se la base è > 1 allora è <u>strettamente crescente</u>.
>- se 0 < base < 1 allora è <u>strettamente decrescente</u>.
>- se la base = 1, allora è <u>costante</u>.
>- se non è costante e possiede codominio $]0,+\infty[$ è **biettiva** e quindi invertibile.
>
>Valgono le seguenti proprietà delle potenze:
>$$a^0=1;\quad a^1=a;\quad a^{-x}=\frac{1}{a^x};\quad a^{x_1+x_2}=a^{x_1}\cdot a^{x_2};\quad (a^{x_1})^{x_2}=a^{x_1\cdot x_2}$$

## Funzioni logaritmiche
$$\begin{split} f\colon &]0,+\infty[ \to \mathbb{R}\newline &x \mapsto f(x)=log_ax \end{split}$$
Il logaritmo è la funzione inversa dell'esponenziale: 
- $y=log_a(x) \iff x=a^y$.
- $a^{log_a(x)}=x$.
- $log_a(a^x)=x$.

Definiamo **naturale** il logaritmo quando ha la base $e$ di Nepero (2.71...).
![[Logaritmica.png]]
>[!Important]
>Per le funzioni logaritmiche valgono le seguenti **proprietà**:
>- Se la base è > 1 allora è strettamente crescente.
>- Se 0 < base < 1 allora è strettamente decrescente
>
>Valgono le seguenti proprietà dei logaritmi:
>$$log_a(1)=0;\quad log_a(a)=1$$
>$$log_a(a\cdot b)=log_a(a)+log_a(b);\quad log_a(\frac{a}{b})=log_a(a)-log_a{b}$$
>$$log_aa^b=b\cdot log_aa$$
>
>Per **cambiare base** si usa la seguente formula:
>$$log_a(b)=\frac{log_c(b)}{log_c(a)}$$

## Valore assoluto
$$\begin{split} f\colon &\mathbb{R} \to \mathbb{R}\newline &x \mapsto f(x)=|x|=
	\begin{cases}
	      x & \text{ se } x\geq 0;\\
	      -x & \text{ se } x<0.
	\end{cases} \end{split}$$
Per le funzioni con valore assoluto valgono le seguenti proprietà:
- $|x|\geq 0$ e $x\leq |x|$ per ogni $x\in \mathbb{R}$
- dato $a>0$ allora $|x|<a \iff -a<x<a$;
- dato $a>0, |x|>a \iff (x<-a\lor x>a)$.
![[Assoluto.svg]]

**Disuguaglianze triangolari**:
- |$a+b|\leq |a|+|b|$ (molto usata)
- $||a|-|b||\leq |a-b|$

## Funzione segno
$$\begin{split} f\colon &\mathbb{R} \to \mathbb{R}\newline &x \mapsto f(x)=sgn(x)=
	\begin{cases}
	      1 & \text{ se } x>0;\\
	      0 & \text{ se } x=0;\\
	      -1 & \text{ se } x<0.
	\end{cases} \end{split}
$$
![[Segno.png]]

## Funzioni trigonometriche
Un punto nella circonferenza di raggio 1 ha coordinate:
$$(x,y) | x=cos(a)\land y=sin(a)$$
Dato che l'angolo è rappresentato in **radianti**, possiamo eseguire la conversione in gradi grazie alla seguente formula:
$$g°=\frac{rad\cdot 180°}{\pi}$$
>[!Important]
>Le funzioni trigonometriche rispettano le seguenti **proprietà**:
>- Valori di $sin$ e $cos$ compresi tra -1 e 1;
>- $cos^2a+sin^2a=1$;
>- $cos(-a)=cos(a);\quad sin(-a)=-sin(a)$;
>- $sin(a+b)=sin(a)cos(b)+sin(b)cos(a)$;
>- $cosa(a+b)=cos(a)cos(b)-sin(a)sin(b)$.

