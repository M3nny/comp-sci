Finora abbiamo visto **indirizzi fisici** ($R$) i quali rappresentano indirizzi nella RAM, ci riferiremo a **indirizzi virtuali** ($V$) (i quali sono più numerosi rispetto a quelli _fisici_), come indirizzi riferiti a processi.

La [[Mapping|memoria virtuale]] crea l'<u>illusione di avere più memoria a disposizione</u>, grazie alla **MMU (Memory Management Unit)**, la quale è una componente hardware dedicata alla **traduzione** di $R$ in $V$ scambiando porzioni di $V$ tra memoria principale, cache e memoria secondaria.

Il **mapping dei blocchi** indica quali regioni dello spazio di indirizzamento virtuale di un processo sono attualmente in RAM e dove si trovano.
>Gli indirizzi virtuali contigui visti dal programmatore potrebbero non corrispondere a indirizzi reali contigui.
## Mapping dei blocchi
Sistema che rappresenta gli indirizzi virtuali come coppie ordinate.
#### Segmentazione
In particole un indirizzo virtuale sarà dato da $v=(b,d)$ dove $b$ è il numero del blocco e $d$ lo spostamento.
Considerando che ogni processo ha la sua **tabella della mappa dei blocchi** (memorizzata in RAM) che comincia dall'indirizzo reale $a$, la **traduzione** da un indirizzo virtuale a reale avviene nei seguenti passaggi:
![[Mapping dei blocchi.png|600]]
1. Si aggiunge ad $a$ il numero del blocco $b$ per individuare la riga nella tabella di mappa dei blocchi del processo
2. Ora abbiamo $b'$ il quale indica l'inizio del blocco $b$ in memoria principale
3. Si aggiunge lo spostamento (offset) $d$ a $b'$ per formare l'indirizzo reale $r$
#### Paginazione
Viene usato il mapping di blocchi a **dimensione fissa**.
In questo caso l'indirizzo virtuale è $v=(p,d)$ dove $p$ è il numero di pagina in memoria virtuale.
Un **page frame** è un blocco di RAM destinato a contenere pagine, inizia ad un indirizzo di memoria che è un multiplo della dimensione fissa della pagina ($p_s$).

La traduzione avviene nei seguenti passaggi:
![[Paginazione.png|500]]
1. Da $p$ ricavo attraverso una **tabella delle pagine** $p'$ (page frame)
2. Faccio $p'\cdot p_s + d$ per ottenere l'indirizzo reale di interesse

La **tabella delle pagine** quindi data una **pagina virtuale** restituisce un **page frame**.
>Ha tante righe quante sono le pagine virtuali del processo.

Ogni riga (**PTE: Page Table Entry**) contiene:
- **Bit di residenza** $r$: indica se l'indirizzo è presente in RAM o no
- **Page frame** e **indirizzo di memoria secondaria**
![[Page table entry.svg]]
Se $r=0$ il SO dovrà caricare in RAM l'indirizzo da $s$ (nel mentre blocca il processo e fa altro).