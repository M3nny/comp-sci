## Funzioni a più variabili reali
Le funzioni a più variabili reali le troviamo sotto la forma di:
$$\begin{split} f:A\subseteq&\mathbb{R}^n\to\mathbb{R}\newline &\overline{x} \mapsto z=f(\overline{x}) \end{split}$$
Dove $\overline{x}$ è un vettore del tipo $(x_1,...,x_m)$, nel caso di $n=2$ otterremo:
$$\begin{split} f:A\subseteq&\mathbb{R}^2\to\mathbb{R}\newline &(x,y) \mapsto z=f(x,y) \end{split}$$
da cui otteniamo il grafico:
$$\Gamma(f)=\{(x,y,z)\in\mathbb{R}^2\times\mathbb{R}:(x,y)\in A \land z = f(x,y)\}$$
Con due variabili esprimiamo una superficie a cui associamo ad ogni punto la sua altezza.

![[Curva di livello.png|500]]

Ogni piano non verticale inoltre è definito da $z=ax+by+c$ 
- Il piano orizzontale è definito da $z=c$ dove $c$ è l'altezza del piano.
- I piani verticali si possono rappresentare tramite $ax+by+c=0$ 

### Piani particolari
- $x=0$ rappresenta il piano verticale $yz$
- $y=0$ rappresenta il piano verticale $xz$
- $z=0$ rappresenta il piano orizzontale $xy$

### Curve di livello
Le **curve di livello** sono date da:
$$\Lambda_k=\{\overline{x}\in\mathbb{R}^n|\overline{x}\in A \land f(\overline{x})=k\}$$
$$(n=2)\space\Lambda_k = \{(x,y)\in\mathbb{R}^2|(x,y)\in A \land f(x,y)=k\}$$
ed equivale a tagliare la superficie con un piano orizzontale.
Nell'esempio riportato di sopra le curve di livello sono rappresentate sotto al grafico.

### Sezioni verticali
Chiamiamo sezione verticale l'intersezione tra il grafico di $f$ ed un piano verticale.
Possiamo avere piani ortogonali all'asse $x$ o $y$, e otteniamo la sezione sostituendo a $x/y$ una costante $c$.
- **Ortogonale alle ascisse**: $z=f(c,y)$ con $c\in\mathbb{R}$
- **Ortogonale alle ordinate**: $z=f(x,c)$ con $c\in\mathbb{R}$

---
### Funzioni note

##### Paraboloide ellittico
Descritto come:
$$f(x,y) = a(x - x_0)^2 + b(y-y_0)^2+c$$
Dove $a,b$ sono _concordi_ e se sono _positivi_ generano il paraboloide rivolto verso l'alto, altrimenti se sono _negativi_, verso il basso.
![[Paraboloide elittico.png|200]]
- **Vertice**: $(x_0, y_0)$ 
- **Curve di livello**: circonferenze ($a=b$) oppure ellissi ($a\neq b$)
- **Sezioni verticali**: parabole

##### Cono
Descritto generalmente come:
$$f(x,y)=\sqrt{a(x - x_0)^2 + b(y-y_0)^2}+c$$
![[Cono.png|200]]
Anche in questo $a,b$ sono _concordi_ ma devono essere positivi.
- **Vertice**: $(x_0, y_0)$
- **Curve di livello**: circonferenze con raggio $k$, dove $k$ è l'altezza della sezione orizzontale.
- **Sezioni verticali**: hanno la stessa forma di $y=|x|$, ovvero una V

##### Paraboloide iperbolico
Descritto generalmente come:
$$f(x,y)=a(x - x_0)^2 - b(y-y_0)^2+c$$
![[Paraboloide iperbolico.png|200]]
In questo caso $a,b$ sono _discordi_
- **Sella**: $(x_0,y_0)$
- **Curve di livello**: iperboli o rette
- **Sezioni verticali**: parabole

---
### Dominio naturale
Si trova come nelle funzioni ad una variabile viste finora, con delle piccole accortezze in più.
1. Disegnare la frontiera del dominio
2. Vedere se il dominio è la parte esterna o interna della frontiera

>[!Example]
>$$f(x,y)=\sqrt{4-x^2-y^2}$$
>Il dominio è dato da $x^2+y^2\leq 4$, ora dobbiamo trovare la frontiera, per cui sostituiamo $\leq$ con $=$
>$$x^2+y^2=4$$
>Notiamo che in questo caso viene rappresentata una circonferenza di raggio $2$ con centro nell'origine.
>
>Vediamo se il dominio è quello racchiuso dalla frontiera oppure è esterno sostituendo $(x,y)=(0,0)$, per cui $0+0\leq 4$, dato che la disuguaglianza è vera ed il punto si trova dentro alla circonferenza, il dominio è quello interno alla frontiera.
