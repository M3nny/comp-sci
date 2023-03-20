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