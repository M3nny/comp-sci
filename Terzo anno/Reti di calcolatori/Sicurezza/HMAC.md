Le  [[Terzo anno/Reti di calcolatori/Sicurezza/Introduzione#Funzioni hash|funzioni hash]] in certi casi sono limitanti, se il digest viene allegato al plaintext, un attaccante (Eve) potrebbe modificare sia il plaintext e sia il digest, chi lo riceverà non noterà alcun problema, per questo è importante <u>inoltrare gli hash su due canali diversi</u>.

Per evitare di utilizzare due canali diversi viene introdotto l'**HMAC (Hashed Message Authentication Code)**.

Alice e Bob si mettono d'accordo su una chiave condivisa $K$ ed una funzione di hash $H$ la quale utilizzerà anche la chiave per creare il digest:
$$D=HMAC(M,K)=H((K\oplus \text{opad})|H((K\oplus \text{ipad})|M))$$
- **ipad/opad**: sequenza di padding per allineare $K$ con la lunghezza del digest di $H$
- $|$: concatenazione

In questo modo se Eve intercettasse sia il messaggio e sia l'HMAC non saprebbe comunque la chiave $K$ usata nell'hashing, quindi non potrebbe rompere l'integrità.
Alice e Bob <u>hanno bisogno di un canale sicuro</u> in cui accordarsi sulla chiave.
>L'HMAC fornisce integrità e autenticazione, ma non confidenzialità, il messaggio è ancora in plaintext con l'hash allegato.

### CRAM-MD5
Il protocollo **CRAM-MD5** viene usato per autenticare due utenti basandosi sulla conoscenza di una password e su un accordo di una funzione hash.
![[Challenge HMAC.png|400]]

Viene indicata con $C$ la **challenge**, solitamente viene composta come: $$C=\text{<timestamp@domain>}$$
è importante che sia sempre diversa, altrimenti Eve potrebbe replicare la _challenge_ ed usare il digest precedente.

Questo protocollo è stato **dismesso** in quanto:
1. La crittografia MD5 non è più considerata sicura, inoltre utilizzare una sola funzione crittografica non è saggio
2. L'autenticazione non è bi-direzionale, ovvero Alice non sa se il server è veramente Bob, si potrebbe replicare il protocollo anche dalla parte del server, tuttavia questo non è ufficialmente supportato
3. Eve può ancora osservare la challenge $C$ ed il digest $D$, ciò vuol dire che può tentare un attacco brute force offline

## Crittografia a chiave simmetrica
Gli elementi fondamentali della crittografia sono i **cipher** (algoritmi), le **chiavi** (informazione), e secondo il **principio di Kerchoffs** il segreto risiede nella chiave, non nell'algoritmo, gli algoritmi infatti devono essere visibili a tutti altrimenti potrebbero essere sospetti, tali algoritmi (nascosti) vengono definiti come [snake oil](https://en.wikipedia.org/wiki/Snake_oil).

Per quanto riguarda l'HMAC, Alice e Bob utilizzano un canale sicuro per accordarsi sulla **chiave simmetrica**, ad oggi la funzione crittografica [AES](https://it.wikipedia.org/wiki/Advanced_Encryption_Standard) è ritenuta sicura, quindi procederanno come segue:
1. Alice crea $C=AES(K, M)$
2. Bob utilizzerà lo stesso cipher per decrittare $C$, ovvero $M=AES(K ,C)$

Come le funzioni hash utilizzano operazioni di shift e xor, le funzioni crittografiche utilizzano **sostituzioni** per rimpiazzare simboli e **trasposizioni** (o permutazioni) per scambiare l'ordine dei simboli.

#### Cifrario di Cesare (ROT-13)
La chiave $K$ viene scelta tra $[1,25]\in\mathbb{N}$, e l'algoritmo incrementa ogni carattere di $K \mod_{25}$, mentre nella fase di decrittazione al posto di aggiungere $K$ si sottrae.

È un semplice algoritmo basato sulla **sostituzione** in quanto rimpiazza un simbolo con un altro in modo costante.
Questo meccanismo può essere reso più complesso utilizzando una mappatura tra simboli, tuttavia con una semplice **analisi statistica** è facilmente bypassabile.

#### Algoritmo di trasposizione
$$\begin{matrix}3&1&2&5&4\\h&e&l&l&o\end{matrix}\Longrightarrow\begin{matrix}1&2&3&4&5\\e&l&h&o&l\end{matrix}$$

L'ordine in cui le colonne sono scambiate è la chiave $K$.
La trasposizione mantiene la frequenza delle lettere, quindi è ancora semplice indovinare il messaggio originale.

Un cipher funziona se non c'è (o c'è in minima parte) correlazione tra $C$ ed $M$, nel caso ci fosse correlazione Eve potrebbe recuperare $M$ da $C$ senza conoscere $K$.

#### One-Time-Pad
Il **one-time-pad** è un cipher perfetto con $0$ correlazione, funziona come segue:
1. Alice genera una stringa di $n$ bit e la trasmette a Bob tramite un canale sicuro
2. Per criptare un messaggio $M$ di $m<n$ bit Alice prende una porzione $K'$ da $K$ di lunghezza $m$ e calcola $C=M\oplus K'$
3. La porzione $K'$ della chiave originale $K$ non deve essere più riusata

Prendiamo come esempio $K=1100100111010110$ e $M=00101101$:
- $C=11001001\oplus 00101101=11100101$
il prossimo messaggio utilizzerà la parte successiva di $K$.

Immaginando che Eve abbia il cipher text $101$, questo vuol dire che la chiave deve essere lunga tre bit, quindi può eseguire il brute force:

| $k$ | $c$ | $m'=k\oplus c$ |
| --- | --- | -------------- |
| 000 | 101 | 101            |
| 001 | 101 | 100            |
| ... | ... | ...            |
| 111 | 101 | 010            |

Tuttavia ogni possibile candidato appare una singola volta nella tabella, ovvero hanno tutti la stessa probabilità di apparire, e quindi usare il <u>brute force non darà alcuna informazione</u>.

Il problema di questo algoritmo è che per mandare un messaggio di lunghezza $N$, serve una chiave di lunghezza $N$, infatti se si dovesse usare la stessa chiave per più parti del messaggio la frequenza dei simboli aumenterebbe e quindi si avrebbe lo stesso problema del cifrario di cesare.
$$K=01110001\quad01110001\quad01110001$$
$$\oplus$$
$$M=01001110\quad10101010\quad01001110$$
$$=$$
$$C=\underbrace{00111111}_*\quad11011010\quad\underbrace{00111111}_*$$

>Se si riduce la dimensione della chiave di un OTP si introduce correlazione tra $M$ e $C$.

**Cipher moderni**
Questo algoritmo non è conveniente nella realtà, infatti di solito gli algoritmi moderni combinano trasposizioni e sostituzioni con le seguenti caratteristiche:
- La chiave ha lunghezza fissa
- La correlazione tra $M$ e $C$ è così piccola che è impossibile recuperare $M$ da $C$

Per ottenere l'ultimo punto i cipher moderni hanno un elevato numero di **round** di sostituzioni e trasposizioni su $M$, ogni _round_ rimuove correlazione, per cui alla fine si assume che sia talmente piccola da non poter essere sfruttata da attaccanti.

### Crittografia e autenticazione
Una volta che Alice e Bob si sono scambiati una chiave comune $K$, la possono usare sia per l'HMAC e sia per la crittografia.
![[Comunicazione con chiave simmetrica.png]]

Questo schema garantisce una comunicazione sicura purchè:
- Le funzioni di criptazione e HMAC sono robuste
- Si siano scambiati una chiave prima di cominciare la comunicazione, e che questa sia lunga abbastanza, ai giorni nostri chiavi da $256$ bit sono considerate sicure

>Nella realtà useranno due chiavi diverse per HMAC e crittografia, ne viene usata una per semplicità nell'esempio.

>[!Attention] Offline brute-force
>Il problema degli attacchi brute force offline persiste, anche con due chiavi diverse per HMAC e crittografia.

