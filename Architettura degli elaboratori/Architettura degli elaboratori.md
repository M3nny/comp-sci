- Quando vado a trasformare in binario la parte decimale mi fermo quando la parte decimale (moltiplicata) è uguale a $0$ oppure ad un risultato che ho ottenuto precedentemente (periodicità).
- Sommando 2 numeri positivi, il risultato è positivo, ragionamento analogo per quelli negativi.
- Somma tra numeri unsigned, non c'è overflow se l'ultimo riporto è 0
- Se devo fare le conversioni ed il numero è in comp 2 che inizia con 1, lo devo trasformare in positivo
- Non posso fare le tabelle next state e output assieme, altrimenti vengono fuori sbagliate
- Nel calcolo del CPI medio: 50% = 0.5 mentre 5% = 0.05
- Dopo aver fatto la somma tra 2 FP, se il numero inizia con 1, devo fare il complemento a 2 (passare a modulo e segno)
- Nella somma FP se prima di farla ho introdotto il segno (fatto il valore assoluto) se alla fine della somma ho un riporto di 1 (quindi una nuova cifra) non lo devo mettere, come regola possiamo dire che posso avere al massimo 2 cifre a sinistra della virgola.
- mettere sempre l'ultimo riporto se no sbaglio a valutare l'overflow
- Dopo aver fatto la somma di numeri unsigned mi chiedono se avrebbe dato overflow nel caso fossero stati CO2 gli addendi, non devo considerare solo i riporti ma anche guardare il loro segno, perchè in CO2 la somma potrebbe non essere stata la stessa dato che forse  avrei potuto invertire i segni prima di farla

## Somma FP
1. Uso i valori assoluti per sommare
2. Se gli addendi erano discordi o negativi entrambi:
	- Se il risultato comincia con 1 passo a modulo e segno facendo il complemento a 2, se erano entrambi negativi il risultato per forza è negativo
altrimenti se erano positivi di sicuro è positivo il risultato e lo lascio così com'è
3. Allineo l'esponente se necessario


## Conversioni 
- da base x a CO2 se il numero in base x è negativo, trovo il suo valore in binario e poi faccio il CO2 per prendere il suo valore assoluto 
- Se il numero comincia con 1 in binario (considerandolo come complemento a 2) e lo devo convertire in decimale, devo fare il CO2 e mettere il meno davanti
- Se dal IEEE754 trovo che il binario è negativo, poi per convertirlo a decimale **non** devo fargli il complemento a 2


## Valutazione delle prestazioni
Per calcolare la velocità di picco del calcolatore espressa in MIPS, devo tenere conto solo del CPI più basso e calcolare Texe con quello (senza moltiplicarlo per la sua percentuale di utilizzo dato che verrà usato solo quello e quindi sarà 100%)







## Domande
> Scrivere sintassi e semantica dell’istruzione BEQ e spiegare come viene realizzata ed eseguita nella CPU multiciclo. Nel caso taken, come viene calcolato il valore del PC a cui saltare?
- La sintassi è: *beq $4, $5, label* e significa che se $4 è uguale a $5 allora la prossima istruzione da caricare è all'indirizzo label. Nella CPU multiciclo, dopo aver eseguito il fetch ed aver incrementato il PC al secondo ciclo viene anche anticipato del lavoro per il branch così nel caso l'istruzione sia una beq, essa è in grado di terminare al terzo ciclo sapendo già a che indirizzo saltare

> Disegnare il circuito e spiegare il funzionamento del S-R latch

![[SR Latch.png|400]]
- Il Set Reset latch è composto da 2 porte NOR, con la combinazione SR = 00 il latch è a riposo e mantiene in memoria il valore memorizzato in precedenza, SR = 10 set del latch, SR = 01 reset del latch, la combinazione SR = 11 non deve mai essere presentata in quanto il valore memorizzato può essere arbitrario.

> Disegnare il circuito e spiegare il funzionamento del D-latch

![[D Latch.png|300]]
- Il latch clockato quando è deasserted (0) mantiene in memoria il valore precedentemente valorizzato, mentre quando è asserted memorizza il valore. A differenza del SR-latch con il clock siamo in grado di determinare quando è possibile memorizzare cercando di garantire la stabilità del segnale.

> Descrivere i passi di esecuzione dell’istruzione MIPS lw nella CPU multiciclo
- Al primo passo viene eseguito il fetch dell'istruzione e viene incrementato il PC, al secondo passo viene decodificata l'istruzione poi viene calcolato l'indirizzo di memoria da cui leggere, al passo successivo si legge dalla memoria nell'indirizzo calcolato precedentemente ed infine si scrive il valore letto in memoria in un registro (write-back)

> Scrivere le definizioni di circuito combinatorio e circuito sequenziale. Nell’ambito dei circuiti sequenziali, definire i circuiti di Mealy e di Moore e specificare in cosa si differenziano
- Un circuito combinatorio è formato da porte logiche e l'output è condizionato solo dai valori correnti delle porte, mentre in un circuito sequenziale vengono anche introdotti elementi di memoria, in questo modo l'output dipende anche dallo stato della memoria. Nel circuito di Moore l'output dipende solo dallo stato della memoria in determinato momento, mentre nel circuito di Mealy oltre che allo stato dipende anche dagli input.

> Descrivere caratteristiche e funzionamento del Register File. Specificare quali sono i segnali di input che riceve e quali output produce. Specificare inoltre come vengono realizzate le operazioni di lettura e scrittura
- Gli operandi delle istruzioni aritmetico-logiche sono memorizzati in dei registri, più registri organizzati assieme formano il register file, in input riceve l'indirizzo del registro su cui si vuole operare e un segnale che indica se vogliamo leggere o scrivere sul quel registro. Per la lettura abbiamo bisogno di 2 multiplexer poi ci ritornerà una coppia di registri, se vogliamo scrivere dovremmo usare un decoder inoltre il segnale write dovrà essere affermato.

> Nell’ambito della valutazione delle prestazioni, spiegare cosa si intente per tempo di esecuzione e come si calcola. Descrivere ogni termine che compone la formula di calcolo ed eventuali altre versioni della formula stessa. Spiegare inoltre che relazione c'è tra il tempo di esecuzione e la performance o throughput. Infine descrivere cosa calcola quest’ultima misura delle prestazioni
- Per tempo di esecuzione intendiamo la latenza, ovvero il tempo trascorso tra l'avvio di un job e la sua terminazione, si può calcolare tramite: $n°cicli \cdot T$ (numero di cicli per l'esecuzione del programma per il periodo del ciclo di clock) oppure tramite $CPI\cdot IC \cdot T$ (cicli per istruzione per le istruzioni totali eseguite dal programma per il periodo del ciclo di clock). Performance e throughput sono sinonimi indicano una misura generica della velocità del computer, è possibile trovare la performance tramite $\frac{1}{Texe}$ 

> Descrivere i principi di progetto delle CPU singolo ciclo e multiciclo viste a lezione, evidenziando i loro vantaggi e svantaggi.
- Nella CPU a singolo ciclo l'obiettivo è quello di eseguire qualsiasi tipo di istruzione (facente parte al nostro ISA ridotto) in un singolo ciclo di clock, perchè questo sia possibile però dobbiamo replicare alcune risorse come i sommatori che ad esempio se nel caso in cui la ALU fosse già impegnata ad eseguire istruzioni, il PC non potrebbe essere incrementato usandone solo 1 di sommatore, un altro grande svantaggio è quello di avere un ciclo di clock tarato sull'istruzione che ci mette più passi per essere completata, rallentando così anche le istruzione che ci metterebbero meno tempo e generando di conseguenza tempi morti. Nella CPU multiciclo andiamo a risolvere il problema della replicazione delle risorse in quanto ora le istruzioni non vengono più eseguite su un singolo ciclo di clock, bensì usiamo un registro di stato per tener traccia dei risultati parziali di ogni istruzione così da poterla fare continuare nel prossimo ciclo. Con la nostra CPU didattica potrebbe sembrare inoltre di non aver ottenuto particolari vantaggi con quest'ultimo tipo di CPU, questo perchè non teniamo in considerazioni istruzioni più complesse come quelle FP.

> Scrivere la formula della legge di Amdhal, specificando tutte le sue componenti. Descrivere a cosa serve, quando si usa e qual ed il corollario che ne deriva
- La formula è la seguente: $Texe_{after} = \frac{1}{s}\cdot Texe + \frac{(1-\frac{1}{s})\cdot Texe}{n}$, con Texe intendiamo il tempo di esecuzione totale del programma prima delle ottimizzazioni, con $\frac{1}{s} Texe$ intendiamo la frazione del tempo non modificata dalle ottimizzazioni, con $(1-\frac{1}{s}) Texe$ intendiamo la frazione del tempo ridotta tramite le ottimizzazioni, mentre con $n$ indichiamo il miglioramento ottenuto tramite le ottimizzazioni. Serve a fissare il massimo speedup ottenibile e viene usata appunto quando apportiamo delle migliorie al programma, ne deriva dal corollario che è meglio rendere più veloci i casi più comuni (istruzioni che impiegano la maggior parte di $Texe$).

> Cosa si intende per SRAM e DRAM? Descrivere brevemente le loro caratteristiche
- Per SRAM (static RAM) intendiamo un tipo di RAM molto veloce la quale viene utilizzata per realizzare le cache ed è composta da una matrice di latch è però più costosa e richiede più spazio della DRAM (dynamic RAM) la quale è più capiente ma più lenta, inoltre utilizza dei condensatori per mantenere i dati in memoria, i quali devono essere costantemente rinfrescati per continuare a mantenere i dati in memoria (il refresh avviene leggendo e riscrivendo i valori appena letti)

> Descrivere le due forme canoniche Somma di Prodotti e Prodotti di Somme utilizzate per rappresentare le funzioni logiche. Quali sono i vantaggi di scrivere una funzione in forma canonica?
- Nella forma SP: per ogni output uguale a 1 genera un prodotto (mintermine) degli input, dove gli input a 0 appaiono negati, nella forma PS: ogni output uguale a 0 genera una somma (maxtermine) degli input, dove gli input a 1 appaiono negati. Come risultato otterremo un circuito efficiente con la 2-level logic ovvero un livello di porte AND e un livello di porte OR (la disposizione cambia in base al tipo di forma canonica scelta)

> Che differenza c’è tra un D-latch clockato e un flip-flop? Che problema si può verificare quando un D-latch clockato deve fornire l’input ad un circuito combinatorio e deve poi memorizzarne l’output nello stesso periodo di clock?
- Un D-latch clockato memorizza il segnale di ingresso nell'intervallo alto del clock, questo può portare a problemi in quanto il valore memorizzato si propaga all'uscita con delle possibili variazioni dato che quando il clock è alto non è ancora stabile (si stabilizza quando torna a zero) quindi nel caso in cui dovesse essere usato sia come input che come output durante lo stesso ciclo di clock il d-latch non andrebbe bene in quanto se il clock dovesse rimanere alto per troppo tempo allora potrebbe essere memorizzato un valore scorretto (trasparenza del d-latch). Il flip-flop a sua differenza sfrutta un generatore di impulsi che gli permette di usare una tipologia di timing edge-triggered, dove in questo caso la memorizzazione viene effettuata (immediatamente) sul fronte di salita o discesa del clock. 

> Si consideri l’operazione A+B (con A e B numeri binari) nei seguenti casi: (a) A, B sono numeri naturali senza segno rappresentati su 8 bit; (b) A, B sono numeri interi espressi in complemento a due su 8 bit. Si discutano le condizioni che possono causare overflow e come esse possono essere rilevate nei due casi elencati
- Nel primo caso da overflow se l'ultimo riporto è 1, nel secondo caso da overflow se gli ultimi due riporti sono discordi oppure sommando due positivi otteniamo un negativo oppure sommando due negativi otteniamo un positivo.

> Considerare l’input Less dell’ALU vista a lezione e dire (a) quali valori può assumere e in quali casi; (b) scrivere sintassi e semantica dell’operazione svolta dalla ALU che coinvolge questo input
- L'input less può assumere il valore 0 o 1 in base al risultato dell'istruzione slt (set less than), 0 se il primo operando è maggiore del secondo, 1 se è minore. La sintassi è la seguente: *slt $a, $b, $c* mette ad 1 $a se $b è minore di $c altrimenti mette il valore 0 ad $a.

> Cos’è il clock e per quale motivo viene introdotto nei circuiti? Scrivere quali sono e cosa indicano le due misure legate al clock
- Essendo che gli output diventano stabili dopo un intervallo di tempo, bisogna evitare che vengano presentati agli elementi di memoria valori non stabili, per questo usiamo il clock che è un segnale il cui periodo è abbastanza grande da assicurare la stabilità dell'output, le sue misure sono frequenza la quale misura quante volte il segnale del clock cambia stato in un secondo e si misura in Hz ed il periodo che si riferisce alla durata di un ciclo di clock e si misura in secondi 

> Si assuma di utilizzare la CPU multiciclo vista a lezione. Si considerino quindi le seguenti linee di codice: 
```r
	lw $t2, 0($t3) 
	lw $t4, 4($t3) 
	beq $t2, $t4, Label #assumere che il salto non venga eseguito 
	add $t4, $t2, $t4 
	addi $t2, $t2, 1 
	sw $t4, 8($t3) 
	sw $t2, 0($t3) 
	Label: ...
 ```
(a) Quanti cicli di clock sono necessari per eseguire questo codice? **29**
(b) Cosa accade durante il decimo ciclo di clock? E durante il tredicesimo? **finisce lw, finisce beq**
(c) In quale ciclo inizia l’istruzione sw finale? **26**
(d) Scrivere in dettaglio i passi d’esecuzione dell’istruzione lw.
>Esercizio simile 13 giugno 2018

> Scrivere il circuito e spiegare il funzionamento del flip-flop semplice ed il principale vantaggio nella realizzazione dei circuiti sequenziali

![[Flip-flop.png|300]]
- Il flip flop semplice memorizza istantaneamente il valore del segnale in ingresso sul fronte di salita del clock utilizzando la metodologia di timing rising triggered grazie ad un generatore di impulsi, ed a causa della brevità dell'impulso non si verificano errori simili a quelli dovuti alla trasparenza del d-latch

> Dimostrare, applicando le proprietà dell’algebra di Boole, che è possibile eliminare la variabile A dalla seguente equazione logica: F = A∼BC∼D + ∼A∼BC∼D. Per ogni passaggio scrivere la proprietà applicata
1.  Passo: A∼BC∼D + ∼A∼BC∼D
2.  Passo: (A + ∼A)∼BC∼D (utilizzando la proprietà di annullamento della variabile)
3.  Passo: 1∼BC∼D (poiché A + ∼A = 1)
4.  Passo: ∼BC∼D (poiché 1∼BC∼D = ∼BC∼D)

> Gli operatori logici NAND o NOR sono sufficienti per implementare qualsiasi funzione logica. Cosa significa e perchè?
- Gli operatori NAND e NOR sono considerati operatori universali in quanto utilizzando solo uno l'altro è possibile ricreare qualsiasi porta logica e di conseguenza realizzare qualsiasi tipo di circuito.

> Spiegare a cosa serve e come viene generato il segnale di uscita Zero dell’ALU vista a lezione. Scrivere la sintassi e la semantica delle istruzioni assembler che l’ALU realizza grazie a questo segnale
- Il segnale zero prodotto dall'ALU serve a capire se i due operandi dell'istruzione *beq* sono uguali oppure no, nel caso siano uguali allora zero = 1 altrimenti 0, la sintassi della _beq_ è la seguente: *beq $4, $5, label* se $4 è uguale a $5 allora mette zero=1 e salta a label.

> Cosa si intende per CPU user time? Scrivere la formula per il calcolo del tempo di esecuzione di un programma su un calcolatore. Scrivere poi la formula per il calcolo dei MIPS e spiegare per quale motivo possono essere una misura di prestazione fuorviante
- Per cpu user time intendiamo il tempo impiegato dal computer per eseguire codice dell'utente o delle applicazioni (quindi non tempo impiegato dal SO oppure per le librerie di sistema). $\text{Texe} = n° cicli\cdot T$ mentre $MIPS = \frac{IC}{Texe \cdot 10^6}$ sono misure fuorvianti in quanto può dipendere anche dal compilatore che magari potrebbe generare anche tante istruzioni inutili per far aumentare i MIPS e far quindi sembrare che quella macchina sia più veloce

> Spiegare in quali casi si verifica overflow/underflow per i numeri di tipo: 
	(a)  unsigned rappresentati su n bit; 
	(b) in complemento a due rappresentati su n bit; 
	(c) in virgola mobile rappresentati secondo lo Standard IEEE754 in singola precisione.
> Scrivere sintassi, semantica e formato di tutte le istruzioni che la ALU vista a lezione riesce ad eseguire
- Unsigned: quando ultimo riporto è 1, CO2: ultimi 2 riporti discordi, IEEE754 quando il numero ha più di 32 bit
![[sintassi-semantica.png|400]]
| **Istruzione** | **Trasferimenti tra registri**  | **PC**                                |
| -------------- | ------------------------------- | ------------------------------------- |
| add            | R[rd]<-R[rs]+R[rt]              | PC<-PC+4                              |
| sub            | R[rd]<-R[rs]-R[rt]              | PC<-PC+4                              |
| lw           | R[rt]<-M[R[rs]+sign_ext(Imm16)]    | PC<-PC+4                              |
| sw          | M[R[rs]+sign_ext(Imm16)]<-R[rt] | PC<-PC+4                              |
| beq            | if(R[rs] == R[rt]) then         | PC<-PC+4+(sign_ext(Imm16)<<2) (salto) |
|                | else                            | PC<-PC+4 (non salto)                  |

> Descrivere come viene realizzata l’operazione sub dall’ALU vista a lezione
- Per prima cosa inverte il segno del numero da sottrarre quindi esegue il complemento a 1 e somma 1, ora esegue una normale somma

> Dire in quali casi si verifica underflow nelle operazioni con numeri FP espressi secondo lo Standard IEEE754
- Si verifica underflow quando il numero è minore di quello più piccolo esprimibile dalla cpu 

> Descrivere come viene realizzata l’operazione bne dall’ALU vista a lezione
- *bne $a, $b, label* se ZERO prodotto dalla cpu è 0 allora salta a label

>La parte di controllo è combinatoria per cpu a ciclo singolo?
- Si è combinatoria, mentre il datapath è sequenziale

>Disegnare il sommatore e spiegare come avviene la somma

![[1-bit adder.png|300]]

> Risorse usate per ogni ciclo di esecuzione
1. ALU, memoria 
2. ALU, register file
3. ALU per R-type oppure ALU per lw/sw, completo beq (senza utilizzare ulteriori risorse)
4. register file per R-type oppure memoria per lw/sw
5. register file