Vedremo come un numero elevato di _task_ possono **competere** e **cooperare**.
## Competizione
Dei processi competono per risorse comuni, (e.g. lettura/scrittura della stessa area di memoria, condivisione della CPU) e questo crea **interferenze** tra processi:
- **Starvation**: un processo bloccato per tempo indefinito a causa di altro/i processo/i che monopolizzano una o più risorse
- **I/O**: l'accesso ad una periferica varia in base a quanti processi la stanno utilizzando

Il SO deve **gestire la competizione** e garantire la correttezza (e.g. [[Scheduling|scheduling di processi]], [[Dischi#Scheduling del disco|scheduling del disco]]).
## Cooperazione
Ci sono tanti altri casi in cui l'**interazione** è voluta:
- **Condivisione**
- **Possibilità di parallelismo**: incrementa le prestazioni usando più core fisici
- **Modularità**: un'applicazione complessa è divisa in attività distinte più semplici
- **Multitasking**: lanciare un'attività mentre si continua con un'altra
- **Replicazione**: per quando è necessario l'esecuzione simultanea della stessa attività (e.g. [[Triennale/Secondo anno/Sistemi operativi/Mod. 1/Thread#Thread nei sistemi distribuiti|pop-up thread]])
---
## Modelli di comunicazione
Per cooperare usiamo principalmente due modelli di **comunicazione**:
- **Message passing**: i task si scambiano informazioni tramite messaggi (principalmente processi)
- **Shared memory**: i task condividono dati in memoria (principalmente thread)

## Message passing
I processi dispongono di due primitive:
- `send(m)`: invia il messaggio `m`
- `receive(&m)`: riceve un messaggio e lo salva in `m`
Mittente e destinatario possono essere **nominati** direttamente o indirettamente.

### Nominazione diretta
- `send(P, m)`: invia il messaggio `m` a `P`
- `receive(Q, &m)`: riceve un messaggio da `Q` e lo salva in `m`

In questo **canale riservato** basta conoscere la reciproca identità, esiste una variante in cui si riceve da chiunque:
- `receive(&Q, &m)`: riceve un messaggio `m` da un mittente qualsiasi `Q`

| **Vantaggio** |                    **Svantaggio**                     |
|:------------:|:----------------------------------------------------:|
|   Semplice   | È necessario conoscere il PID di mittente e destinatario |
### Nominazione indiretta
Il messaggio non viene letto/scritto dal destinatario/mittente, bensì si usano delle **porte (pipe in UNIX)** gestite dal SO, il quale ne consente la creazione e distruzione.
- `send(A, m)`: invia il messaggio `m` sulla porta `A`
- `receive(A, &m)`: riceve un messaggio dalla porta `A` e lo salva in `m`

In questo caso è necessario conoscere solo il nome delle porte.

Per gestire la **competizione** spesso si associa la porta ad un processo (il creatore la possiede), il quale sarà l'unico in grado di leggere da tale porta, in questo modo si evitano problemi di competizione in ricezione.

I messaggi possono essere **accodati** sulla porta, quindi l'invio è meno problematico.

## Comunicazione sincrona e asincrona

|             |                                                **Sincrona**                                                |                                                                    **Asincrona**                                                                    |
|:-----------:|:----------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------------------:|
|  **Send**   | La _send_ è bloccante, viene completata quando la corrispettiva _receive_ viene eseguita (e.g. telefonata) |              La _send_ viene completata subito, sarà necessario un buffer in cui memorizzare temporaneamente il messaggio (e.g. email)              |
| **Receive** |      La _receive_ è bloccante, viene completata quando c'è un messaggio da leggere (e.g. server web)       | La _receive_ ritorna il messaggio se presente, `NULL` altrimenti, utilizza il polling per controllare se ci sono nuovi messaggi (e.g. client email) |

### Produttore-consumatore
La comunicazione a scambio di messaggi è adatta nelle situazioni in cui un processo **produce** un dato e un altro lo **consuma**.

```shell
~ ls
hello.c  sistemi.md

~ ls | grep sistemi
sistemi.md
```

In questo esempio abbiamo: comunicazione a _nominazione indiretta_ con _send asincrona_ e _receive sincrona_.

>La ricezione dalla pipe è di default sincrona.
