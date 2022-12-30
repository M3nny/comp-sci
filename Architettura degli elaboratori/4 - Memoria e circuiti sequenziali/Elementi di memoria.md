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

## Ritardi nella propagazione dei segnali nei circuiti
Nella realtà i circuiti hanno dei ritardi che _dipendono da quante porte logiche ha attraversato un segnale_, per questo gli output possono cambiare valore prima di diventare stabili, questo fenomeno è noto come **glitch**.

Per questo il periodo **T** deve essere scelto in modo tale da permettere ai segnali di stabilizzarsi.

### Trasparenza del latch clockato
- Durante l'intervallo alto del clock il segnale di ingresso D viene memorizzato nel latch;
- Il valore D si propaga all'uscita Q e con esso anche le eventuali variazioni, col risultato che Q può variare più volte nell'intervallo alto del clock;
- Quando il clock torna a zero, Q si stabilizza
Dunque nell'intervallo alto del clock, il latch non memorizza.

Nel caso in cui l'**elemento di memoria deve essere usato sia come input che come output** durante lo stesso ciclo di clock, **il d-latch non andrebbe bene**, in quanto:
- Se il clock dovesse rimanere alto per troppo tempo, allora potrebbe essere memorizzato un valore scorretto all'interno del latch.

## Metodologia di timing
Vediamo vari istanti in cui può avvenire la **memorizzazione**:
1. **level-triggered methodology**:
	- Avviene sul livello alto (o basso) del clock (come nella situazione brutta di sopra).
2. **edge-triggered methodology**:
	- Avviene sul fronte di salita (o discesa) del clock;
	- La memorizzazione avviene _istantaneamente_ per cui il segnale di ritorno sporco non fa tempo ad arrivare per essere memorizzato;
	- Questo tipo di elementi di memoria si chiamano **flip-flop**.
![[Timing.png|500]]

### Generatore di impulsi
Permette di generare impulsi in corrispondenza del fronte di salita di un segnale a gradino (funge da clock).

## Flip-flop semplice
![[Flip-flop.png|400]]
Il flip-flop semplice (in figura il generatore di impulsi è a sinistra) memorizza _istantaneamente_ il valore di D sul fronte di salita del clock (in corrispondenza dell'impulso), questo tipo di metodologia edge-triggered, è definita **rising triggered**.

>[!Attention]
>Il segnale memorizzato fluisce subito fuori dal flip-flop e a causa della brevità dell'impulso, non permette di percorrere la logica combinatoria e di modificare il contenuto del flip-flop in un solo periodo di clock.

### D flip-flop
![[D flip flop.png|400]]
Questo tipo di flip-flop può essere utilizzato sia in input che in output nello stesso ciclo di clock.
- È composto da 2 latch in serie, il primo è **master** mentre il secondo è **slave**;
- Viene utilizzata sempre la metodologia edge-triggered, ma questa volta è di tipo **falling triggered**.