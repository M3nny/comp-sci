Dati $G_1=(V_1,E_1)$, $G_2=(V_2,E_2)$ e la funzione $\phi:V_1\to V_2$, essi rappresentano un **isomorfismo** (ovvero hanno la stessa forma) se:
1. $\phi$ è biunivoca
2. Deve preservare l'adiacenza: $(u,v)\in E_1\iff(\phi(u),\phi(v))\in E_2$

Seguono due grafi isomorfi:
![[Grafi isomorfi.svg]]
essi sono isomorfi perchè rappresentano la stessa relazione indipendentemente dal nome dei nodi, infatti esiste un vertice adiacente ad altri due, i quali non sono adiacenti tra loro, scriviamo quindi $G\simeq G'$.

La **degree-sequence** ($\text{deg-seq}(G)$) di un grafo è un vettore di $n$ elementi contenente i gradi dei vertici secondo un certo ordine (solitamente è crescente).

#### Clique
Per elencare una condizione necessaria per l'isomorfismo, dobbiamo introdurre il concetto di **clique**, ovvero un [[Tipologie#Sottografo|sottografo]] [[Tipologie#Grafo completo|completo]], in particolare:
- **Clique massima**: sottografo completo più grande in $G$
- **Clique massimale**: clique che non è contenuta in una clique più grande
![[Clique.svg|500]]
Indichiamo con $\omega(G)$ il **clique number**, ovvero la cardinalità della clique massima.


**Condizioni necessarie per l'isomorfismo**:
1. $G_1\simeq G_2\implies |V_1|=|V_2|$
2. $G_1\simeq G_2\implies |E_1| = |E_2|$, infatti deve valere anche $\deg(u)=\deg(\phi(u))\space\forall u\in V_1$
3. $G_1\simeq G_2\implies\text{deg-seq}(G_1)=\text{deg-seq}(G_2)$
4. $G_1\simeq G_2\implies$ $G_1$ e $G_2$ hanno lo stesso numero di _componenti connesse_
5. $G_1\simeq G_2\implies\omega(G_1)=\omega(G_2)$

>È facile dimostrare se non è un isomorfismo, ma è più difficile il contrario.

Di seguito sono rappresentati due grafi _non_ isomorfi, in quanto rispettano le prime tre condizioni, ma non l'ultima (4.):
![[Grafi non isomorfi.svg]]

**Dimostrazione isomorfismo tra due grafi**:
Siano $G_1$ e $G_2$ i seguenti grafi:
![[Grafi isomorfi pentagono.svg]]
e sia $\phi$ definita come segue:
$$\phi(1)=2\quad \phi(2)=4\quad \phi(3)=1\quad \phi(4)=3\quad \phi(5)=5$$
verifichiamo se $\phi$ rispetta le due condizioni:
1. $\phi$ mappa un solo vertice di $V_1$ ad uno solo di $G_2$ quindi è biunivoca
2. Le adiacenze sono rispettate:
	- $(1,2)\in E_1\to(\phi(1),\phi(2))=(2,4)\in E_2$
	- $(2,3)\in E_1\to(\phi(2),\phi(3))=(4,1)\in E_2$
	- $(3,4)\in E_1\to(\phi(3),\phi(4))=(1,3)\in E_2$
	- $(4,5)\in E_1\to(\phi(4),\phi(5))=(3,5)\in E_2$
	- $(5,1)\in E_1\to(\phi(5),\phi(1))=(5,2)\in E_2$

Verifichiamo se i due grafi rispettano le cinque condizioni:
1. $V_1=V_2=\{1,2,3,4,5\}$, quindi $|V_1|=|V_2|$
2. $|E_1|=|E_2|$
3. $\text{deg-seq}(G_1)[2,2,2,2,2]=\text{deg-seq}(G_2)[2,2,2,2,2]$
4. Entrambi hanno solo $1$ componente connessa

>Inoltre è possibile notare che $G_2$ è il grafo _complemento_ di $G_1$, quindi si può dire che $G_1$ è isomorfo al suo complemento $G_1\simeq \overline{G_1}$.