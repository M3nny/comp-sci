Il **B&B** è una tecnica iterativa utilizzata per la risoluzione di problemi di programmazione matematica con **variabili intere e non**.
L'idea è quella di utilizzare un approccio [[Teorema master#Divide et impera|divide et impera]] per trovare una stima della soluzione di ogni sottoproblema.

Consideriamo il seguente problema di PLI:
$$\begin{aligned}
\min&\space c^Tx\\
&x\in Q_0\\
&x\in \mathbb{Z}^n
\end{aligned}
\quad\equiv\quad
\begin{aligned}
\min&\space c^Tx\\
&x\in S_0
\end{aligned}$$

Indichiamo con $Q_0$ un generico poliedro, mentre con $S_0=Q_0\cap\mathbb{Z}^n$ i **punti ammissibili con coordinate intere**.
![[Poliedro con coordinate intere.svg|400]]

Sia $x_0$ la soluzione di $\min\limits_{x\in Q_0}c^Tx$ e $\hat x_0$ la sol di $\min\limits_{x\in S_0}c^Tx$, si naturalmente:
$$f(\hat x_0)\geq f(x_0)$$
poichè $S_0\subseteq Q_0$, ovvero si avranno più punti a disposizione per minimizzare $f$, per la soluzione $\hat x_0$ avrà sempre un valore maggiore o uguale alla soluzione definita dal punto $x_0$.

Il metodo del B&B consiste nel **partizionare** (da cui branch) la regione ammissibile $S_0$ nei sottoproblemi $S_i,i\in\{1\dots,k\}$ in modo tale che:
$$S_0=\bigcup_{i=1}^kS_i\qquad S_i\cap S_j=\emptyset,\space\forall i\neq j$$
cercando (se necessario) una **stima per difetto** di una soluzione del sottoproblema $\min\limits_{x\in S_i}c^Tx$.

Il sottoproblema $(P_i)$ generato viene detto **aperto** e viene inserito in una lista.
