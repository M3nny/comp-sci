Più basso è il livello in cui stiamo operando, più sono le informazioni crittografate, ad alto livello è più facile sviluppare applicazioni, ma più informazioni possono essere trapelate.

**Possiamo criptare l'header IP?**
**No**, l'header IP è utilizzato per il routing, ed i router sono sconosciuti dagli attori nella comunicazione, tuttavia esistono delle **eccezioni**, tra cui:
- Crittografia a livello MAC, questo funziona ma solo all'interno di una LAN
- Utilizzo di una VPN (Virtual Private Network) che incapsula un pacchetto IP criptato all'interno di un altro pacchetto IP, i quali header sono in chiaro

**Possiamo criptare l'header TCP?**
**Teoricamente si**, il TCP è un protocollo end-to-end, quindi gli attori della comunicazione possono istanziare una comunicazione sicura, tuttavia **non è possibile** in quanto internet si basa su dei punti intermediari di comunicazione che devono guardare gli header TCP.

## Transport Layer Security (TLS)
I protocolli internet inizialmente non furono designati con i principi di sicurezza, per cui si sono dovuti costruire dei layer aggiuntivi al di sopra di quelli già esistenti.

Il **Secure Socket Layer (SSL)** venne introdotto come un servizio che aggiungeva sicurezza al [[TCP]], col passare degli anni venne standardizzato e rinominato a **TLS**.
>SSL e TLS sono la stessa cosa.

Il TLS garantisce i seguenti servizi ai livelli superiori:
- Autenticazione dell'origine
- Segretezza
- Integrità
![[TLS layer.png]]

### TLS record protocol
Il **TLS record protocol** viene utilizzato per applicare una trasformazione ai dati per renderli sicuri.
![[TLS record protocol.png|450]]

La pipeline funziona come segue:
1. Lo stream di  dati viene frammentato
2. Compresso (opzionale)
3. Criptato
4. Viene aggiunto un header

Provvede inoltre due proprietà basilari:
- **Connessione privata**: viene utilizzata crittografia simmetrica, le chiavi sono uniche per ogni connessione e sono negoziate dal _TLS handshake protocol_
- **Connessione affidabile**: il trasporto del messaggio include un controllo di integrità

### TLS handshake protocol
Il **TLS handshake protocol**, consente al server ed al client di autenticarsi e di negoziare quale algoritmo crittografico utilizzare per generare le chiavi per poi scambiarsele prima di scambiarsi il primo byte di dati.

Provvede inoltre tre proprietà basilari:
- Gli attori possono essere **identificati** tramite una chiave pubblica, l'autenticazione è necessaria per almeno uno dei due attori
- La **negoziazione di un segreto è sicura**
- La **negoziazione è affidabile**, un attaccante non può interferire senza essere rilevato dai due attori

![[TLS handshake protocol.png]]

1. I primi tre messaggi rappresentano il [[Livello di trasporto#Three way handshake|3-way handshake]] del TCP, ciò include quindi `ClientHello` il quale rappresenta l'ACK
2. I certificati vengono scambiati nei messaggi `Certificate`, in HTTPS tali messaggi contengono tutto l'albero dei certificati dalla root CA fino al certificato del sito
3. `ChangeCipher` indica che la negoziazione delle chiavi è finita, il prossimo messaggio sarà criptato e autenticato
4. `Finished` è il primo messaggio criptato, esso contiene un hash dei messaggi precedenti per verificare che essi non siano stati modificati da un MiTM
5. Il primo byte usabile dal client arriva dopo $4$ RTT

>[!Info] Autenticazione unidirezionale
>Solitamente l'autenticazione avviene in una singola direzione, infatti è il server ad indentificarsi, ciò non è richiesto al browser.
>Tuttavia il client ed il server possono ancora negoziare una chiave simmetrica per rendere la connessione TCP sicura.

#### Mutual TLS (mTLS)
Con la nascita del paradigma dei **microservizi** e **applicazioni cloud** la necessità della mutua autenticazione è aumentata.

In questi sistemi distribuiti che interagisco all'interno della stessa infrastruttura si utilizza la politica **zero trust**, ovvero non ci si fida di un servizio solo perchè è interno all'infrastruttura, ma perchè esso ha un certificato valido.

## TLS 1.3
La versione 1.2 del TLS possedeva molteplici bug e feature inutilizzate, molti di questi problemi vennero risolti dalla versione **1.3** la quale rimosse molteplici features inutilizzate riducendo la superfice d'attacco.

Tra i vari cambiamenti, venne resa obbligatoria la **forward secrecy**, la quale garantisce che le chiavi di sessione non vengano compromesse anche se la chiave privata del server dovesse essere compromessa.

In pratica se Eve intercetta una comunicazione e se ne salva il contenuto (senza riuscire a decriptarlo) e poi in un secondo momento riesce a rubare la chiave privata del server, non potrà comunque decriptare il contenuto che si era salvata precedentemente.

La _forward secrecy_ è implementata con **chiavi pubbliche effimere**, ovvero chiavi pubbliche che vengono cancellate dopo essere state usate.
>Questa pratica non era obbligatoria nella versione 1.2.

