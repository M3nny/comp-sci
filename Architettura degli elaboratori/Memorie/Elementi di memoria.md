### Differenza tra circuiti combinatori e sequenziali
- I **circuiti combinatori** calcolano funzioni che dipendono solo dai dati in input.
- I **circuiti sequenziali** calcolano anche funzioni che dipendono da informazioni memorizzate.

## S-R Latch
Il **Set Reset** latch è un circuito basilare composto da due porte NOR, dove l'output è il valore memorizzato nel latch stesso.
![[SR Latch.png]]
- ==_Set_== del **latch a sinistra**: (S,R)=(1,0)
- ==_Reset_== del **latch a destra**: (S,R)=(0,1)
Con la combinazione (S,R)=(0,0) il latch è a riposo e mantiene il valore memorizzato in precedenza.
La combinazione (S,R)=(1,1) non deve mai essere presentata al latch in quanto il valore memorizzato può essere arbitrario.

## Clock
I segnali devono quindi essere chiari e devono valere (0,1) oppure (1,0) per poter memorizzare il valore corretto.
Essendo (S,R) calcolati da un circuito combinatorio:
- l'output diventa stabile dopo un certo **intervallo di tempo**, esso può essere calcolato in base al numero di porte attraversate.
Bisogna quindi evitare che vengano presentati al latch valori non stabili (altrimenti potrebbero essere memorizzati valori errati)

Per questo usiamo il **clock** che è un segnale il cui periodo è grande abbastanza da assicurare la stabilità dell'output.
Lo usiamo per **abilitare la scrittura** nei latch, esso appunto determina il ritmo dei calcoli e le relative operazioni di memorizzazione.
Possiamo definire ora il circuito **sincrono** rispetto al segnale di clock.

>[!Example]
>Se un clock ha un periodo **T=10 nsec**, la sua frequenza sarà:
>
>**Freq** = $\frac{1}{T} = \frac{1}{10\cdot 10^{-9}}$ = $10^8$Hz = $10^2\cdot 10^6$Hz = 100 MHz

## Latch clockato D-latch
- _==Set==_ D=1
- _==Reset==_ D=0

A causa delle due porte AND, quando il clock è **deasserted** (0), viene mantenuto il valore precedentemente memorizzato.
Viene memorizzato un valore solo quando il clock è **asserted**.

Se il segnale C fosse invertito (con una porta NOT), il latch memorizzerebbe quando il clock è **deasserted**
![[D Latch.png]]