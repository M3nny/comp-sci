Con questo tipo di CPU è possibile **eseguire qualsiasi tipo di istruzione ISA** (nel nostro caso MIPS) in un **singolo ciclo di clock**.
Vedremo tutti gli elementi che dovranno fare parte del **Datapath** il quale deve fornire i cammini per permettere tutti gli accessi in memoria.

Le istruzioni che useremo sono:
- **memory-reference**: lw, sw
- **arithmetic-logic**: add, sub, and, or, slt
- **control-flow**: beq, j

Prima di proseguire bisogna tenere a mente i vari [[Linguaggio macchina MIPS#Istruzioni e linguaggio macchina|formati delle istruzioni]].

D'ora in avanti con **M[x]** indicheremo la word all'indirizzo x, mentre con
R[y] il registro identificato dall'id numerico y.

### Implementazione generica a singolo ciclo
Vediamo l'implementazione di una generica istruzione:
1. Uso il **PC** (Program Counter) all'interno della CPU per fornire alla memoria l'indirizzo di istruzione;
2. Leggo l'istruzione dalla memoria (**fetch**);
3. Interpreto i campi dell'istruzione (**decode**);
4. Uso l'_ALU_ per l'esecuzione dell'istruzione (**execute**);
	- _add, sub, and, or, slt_ usano l'ALU per le operazioni corrispondenti;
	- _lw, sw_ usano l'ALU per calcolare gli indirizzi di memoria;
	- _beq_ usa l'ALU per controllare l'uguaglianza dei registri;
5. Modifico il **PC** e reitero il ciclo.

> ALU, register file e PC faranno parte del Datapath.

### RTL delle varie istruzioni
Utilizziamo RTL (Register-Transfer Language) per esprimere i trasferimenti tra registri.

1. Per prima cosa dobbiamo effettuare il _fetch_ per ogni istruzione, lo riassumiamo così:

| **Formato** | **Campi**                    |
| ----------- | ---------------------------- |
| R-type      | op/rs/rt/shamt/funct = M[PC] |
| I-type      | op/rs/rt/Imm16 = M[PC]       |
| J-type      | op/26bit address             |

2. Vediamo la sintassi delle istruzioni e quello che fanno nei registri, da ricordare che il PC si sposta di _4 byte_ dopo ogni istruzione perchè ogni istruzione opera su registri di _32 bit_ ovvero _1 word_ per MIPS.
Inoltre  la _BEQ_ adotta un indirizzamento in base al Program Counter, ovvero calcola l'indirizzo a cui saltare in base all'indirizzo attuale della istruzione di beq.

| **Istruzione** | **Trasferimenti tra registri**  | **PC**                                |
| -------------- | ------------------------------- | ------------------------------------- |
| ADD            | R[rd]<-R[rs]+R[rt]              | PC<-PC+4                              |
| SUB            | R[rd]<-R[rs]-R[rt]              | PC<-PC+4                              |
| LOAD           | R[rt]<-M[rs]+sign_ext(Imm16)    | PC<-PC+4                              |
| STORE          | M[R[rs]+sign_ext(Imm16)]<-R[rt] | PC<-PC+4                              |
| BEQ            | if(R[rs] == R[rt]) then         | PC<-PC+4+(sign_ext(Imm16)<<2) (salto) |
|                | else                            | PC<-PC+4 (non salto)                  |

Un esempio con LOAD (_lw_): $$$8\leftarrow M[$2 + 100]$$
Memorizzo quello che trovo andando avanti di 100 dal registro $2, inoltre la somma per spostarsi in avanti nel registro è eseguita dall'_ALU_.

**Funzionamento di beq (branch TRUE)**:
1. PC<-PC+4 per andare all'istruzione successiva;
2. Sommo (sign_ext(Imm16)<<2) ovvero per prima cosa estendo la costante immediata e poi la shifto di 2, ovvero è come moltiplicare per $2^2$, questo perchè in questo modo punterò all'inizio di un'altra istruzione (dato che vanno di 4byte in 4byte)

>**LOAD e STORE usano Imm16** (costante immediata), **ma la _ALU_ usa 32bit**, quindi **devo prima estendere la costante immediata allungando il bit di segno** (complemento a 2), questa operazione è indicata come _sign_ext(Imm16)_.

- _**Nota per esame**: chiede la logica del circuito non la struttura, le domande di teoria sono 3 e valgono 9 punti, mentre gli esercizi sono 3_

## Visione astratta di una possibile implementazione
Vediamo qua una versione molto grezza che non potrebbe funzionare al meglio senza alcune aggiunte, che verrano elencate di sotto.

![[Visione astratta di implementazione.png]]
Tutte le istruzioni eseguono prima il fetch, ma qualche istruzione potrebbe anche scrivere in memoria, dato che in un ciclo di clock posso interagire una volta con la memoria abbiamo una **replicazione di memoria** per consentire sia il fetch ed eventualmente scrivere (STORE) in un singolo ciclo di clock.

### Incremento del PC
Se la ALU è impegnata ad eseguire le istruzioni, non può sommare il program counter, per questo dobbiamo aggiungere un **sommatore** che faccia solo quello.
### Estensione del segno di operandi immediati
Il sign extend sarà usato dalle istruzioni _load/store/beq_ e come output fornirà il il bit di segno esteso per arrivare a 32bit.
### Calcolo dell'indirizzo di branch
Anche qui serve un'altro sommatore a 32bit per calcolare l'indirizzo di salto del branch, in quanto quando usiamo _beq_, la ALU sarà già impegnata ad eseguire l'operazione di confronto (sottrazione).

## Integrazione componenti tramite multiplexer

![[Integrazione con multiplexer.png]]
>I segnali in blu/arancione sono di controllo.

Mettendo tutto assieme vediamo che ci sono **molte risorse replicate** inoltre mettiamo dei **multiplexer per evitare conflitti** (gli ingressi dei multiplexer sono da 32bit).

- Mux **sopra**: controlla se bisogna saltare oppure incrementare di una word il PC;
- Mux **sinistra**: controlla se l'istruzione è R-type oppure I-type;
- Mux **destra**: controlla se l'istruzione è di _load_ oppure R-type.
- Esiste un'altro mux in un'implementazione più avanzata che controlla se l'istruzione è di _load_ oppure una istruzione aritmetica.

### Controllo ALU
Consiste nel determinare i 4bit _operation_.
Il circuito sarà a 2 livelli:
1. Il primo livello calcola ALUOp in base all'**op** code
2. Il secondo livello calcola la **operation** effettiva in base al campo funct e a ALUOp
![[Controllo ALU.png]]

## Datapath completo con memoria e controllo

![[Datapath con memoria e controllo.png|600]]

Sulla tabella sono identificati tutti i tipi di controlli:
- **RegDst**: registro di destinazione, devo capire se si tratta di R-type oppure load word;
- **ALUsrc**: mi dice quale è il secondo operando dell'istruzione;
- **MemtoReg**: dalla memoria al register file, mi dice chi scrive in memoria;
- **RegWrite**: mi dice quando il register file deve scrivere;
- **MemRead**: mi dice quando devo leggere dalla memoria dei dati;
- **MemWrite**: mi dice quando devo scrivere nella memoria dei dati;
- **Branch**: mi va a comandare che se l'istruzione è _beq_ e _zero_ è 1 allora devo saltare;
- **ALUOp1**: comanda istruzioni R-type.
