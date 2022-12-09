### Span
Per **span** intendiamo il sottospazio generato dai vettori $v_1, v_2...,v_n$, l'insieme di questi vettori  è ottenuto tramite tutte le possibili combinazioni lineari:
$$Span(v_1,...,v_n)$$
>[!Example]
>- $V=\mathbb{R}^2$
>- $v_1 = \begin{pmatrix}1\\1\end{pmatrix}$ $v_2 = \begin{pmatrix}2\\2\end{pmatrix}$
>$$Span(v_1, v_2) = a_1v_1+a_2v_2 = a_1(\begin{pmatrix}1\\1\end{pmatrix} + a_2 \begin{pmatrix}2\\2\end{pmatrix} =$$
>$$=a_1(1,1)+a_2(2,2)=(a_1,a_1)+(2a_2,2a_2) = \begin{pmatrix}a_1\\a_1\end{pmatrix} + \begin{pmatrix}a_2\\a_2\end{pmatrix} =$$
>$$(a_1+2a_2, a_1+2a_2)$$

## Sistema di generatori
Dato $V$ spazio vettoriale definito sul campo $\mathbb{K}$, l'insieme di vettori $v_1,..., v_n \in V$ è un sistema di generatori di $V$ se ogni elemento di $V$ si può esprimere mediante combinazione lineare di tali vettori, ovvero se per ogni $w\in V$ esistono $n$ scalari $a_1, ..., a_n$ tali che:
$$\sum^n_{i=1}a_iv_i=w$$
- Se $\{v_1, ..., v_n\}$ è un sistema di generatori di $V$, allora $V$ coincide con il sottospazio generato da questi vettori.
