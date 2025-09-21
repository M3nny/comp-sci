Le etichette all'interno dei vari nodi che indicavano l'output nel circuito di Moore, devono essere eliminate, dato che qui l'output di pende anche dall'input oltre che dallo stato.

- Vogliamo realizzare un circuito di Mealy che riceve in ingresso una sequenza di bit, all’interno della quale deve riconoscere se le varie sotto-sequenze di 3 bit hanno un numero pari o dispari di bit uguali ad 1.
- Le sotto-sequenze considerate non si sovrappongono.
- Ogni qualvolta il circuito arriva a leggere il terzo bit di ogni sotto-sequenza deve restituire il valore P o D ( P per pari, D per dispari).
- L’output in corrispondenza di tutte le altre posizioni (prima e seconda di ogni terzetto) della sequenza deve essere N.

1. Nel nostro automa abbiamo uno stato $I$ di partenza al quale ritorneremo ogni volta che abbiamo completato un terzetto. $P_1$, $D_1$ per la lettura del primo bit e $P_2$, $D_2$ per la lettura del secondo bit, al terzo bit ritorniamo a $I$.

![[Automa Mealy.png]]
2. Realizziamo le tabelle di verità degli stati e degli output
| **Stato** | $s_2$ | $s_1$ | $s_0$ |
| --------- | ----- | ----- | ----- |
| I         | 0     | 0     | 0     |
| P1        | 0     | 0     | 1     |
| P2        | 0     | 1     | 0     |
| D1        | 0     | 1     | 1     |
| D2        | 1     | 0     | 0     |
| -         | 1     | 0     | 1     |
| -         | 1     | 1     | 0     |
| -        | 1     | 1     | 1      |

| **Output** | $O_1$ | $O_2$ |
| ---------- | ----- | ----- |
| N          | 0     | 0     |
| D          | 0     | 1     |
| P          | 1     | 0     |
| -          | 1     | 1     |

3. Faccio le tabelle di verità per NEXT_STATE

| $s_2\space s_1\space s_0\space I$ | $O_1\space O_2$ | $s_2'\space s_1'\space s_0'$ |
| --------------------------------- | --------------- | ---------------------------- |
| 0000                              | 00              | 001                          |
| 0001                              | 00              | 011                          |
| 0010                              | 00              | 010                          |
| 0011                              | 00              | 100                          |
| 0100                              | 10              | 000                          |
| 0101                              | 01              | 000                          |
| 0110                              | 00              | 100                          |
| 0111                              | 00              | 010                          |
| 1000                              | 01              | 000                          |
| 1001                              | 10              | 000                          |
| 101X                              | XX              | XXX                          |
| 110X                              | XX              | XXX                          |
| 111X                              | XX              | XXX                             |

![[Tabelle Mealy Karn..svg]]
