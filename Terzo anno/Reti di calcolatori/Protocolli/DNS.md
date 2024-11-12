Il [[Livello applicativo|livello applicativo]] offre **protocolli** che offrono servizi agli utenti, esso tuttavia si basa sul [[Livello di trasporto|livello di trasporto]] che può essere _connection-based_ (TCP), oppure _connection-less_ (UDP).
>La versione UDP è più diffusa.

In un server identificato da (almeno) un **IP**, possono essere in esecuzione più applicazioni identificate tramite un **numero di porta** offerto dal livello di trasporto.

## Domain Name System
Il DNS si occupa della conversione da _nome di dominio_ a _indirizzo IP_.
Un **nome di dominio** ha una struttura gerarchica dal livello più basso a sinistra verso il livello più alto a destra (e.g. `www.unive.it`).
>Il livello più alto `.it` è definito **Top Level Domain (TLD)**.

L'[ICANN](https://www.icann.org/) è responsabile per assegnare i domini, i TLD possono essere delegati ad altre organizzazioni (anche nazionali) le quali li possono ulteriormente delegare ai **Domain Name Registrars**, i quali sono grandi provider.

Quando si possiede un nome di dominio lo si può delegare ad altri, ad esempio il proprietario di `example.com` può delegare a qualcun altro `my.example.com`.

#### Registrazione di un dominio
Per rendere disponibile su `example.com` una pagina web sarà necessario possedere un'indirizzo IP pubblico, poi dovrà prendere in prestito il dominio `example.com`, e configurare il **server DNS**.

Il server DNS risponderà alle richieste fornendo l'indirizzo IP configurato.
>Anche il server DNS dovrà disporre di un indirizzo IP pubblico, ma questo solitamente è offerto dal registrar.

Il registrar dirà al TLD `.com` che un nuovo sottodominio `example` è stato aggiunto, ciò rendere il registrar l'autorità competente per tale dominio.

#### Accesso ad un dominio
Il browser conosce una lista di **root servers**, ovvero una decina di server sparsi per il mondo il quale indirizzo IP è noto dai browser.

I root server forniscono al browser gli indirizzi dei server DNS che sono responsabili per ogni TLD, successivamente il browser contatterà il DNS server responsabile per `.com` e chiederà l'IP di `example.com`, il DNS non lo conosce, fornirà quindi  l'indirizzo IP del server DNS responsabile per `example.com` il quale infine fornirà l'indirizzo IP di `example.com`.

#### Query ricorsive e iterative
L'host che vuole accedere ad un dominio contatterà per primo un **DNS locale**, sarà esso a comunicare con gli altri server DNS finchè non otterrà l'indirizzo IP effettivo, questa tecnica è chiamata query **ricorsiva**.
Nel caso in cui il DNS locale dovesse ritornare una **risposta parziale** all'host in questione si parlerebbe di query **iterativa**.

I root server ed i server di autorità per `.com` non accettano query ricorsive, mentre il DNS locale accetta query ricorsive se interrogato dalla rete locale, ma non al di fuori di essa.

#### DNS caching
Se si volesse interrogare il DNS locale chiedendo l'indirizzo per `www.example.com` ora esso possiederebbe la risposta in cache e potrebbe rispondere subito risparmiando tempo.

Tuttavia se si volesse interrogare `mail.example.com` il DNS locale non avrebbe la risposta pronta, però interrogherebbe subito l'indirizzo IP di autorità per tutti i sottodomini `example.com` in quanto se lo era memorizzando durante la prima interrogazione di tutti i TLD, poi interrogherà il DNS responsabile per `mail.example.com` e memorizzerà in cache l'indirizzo IP associato.

## Formato di un messaggio DNS
Il formato di un messaggio di query per un DNS è formato da **Header**, **Question**, **Answer**, **Authority**, **Additional**.

L'**header** contiene i seguenti campi:

| Campo               | Descrizione                                                                                                                                                                                                                       |
| ------------------- | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **ID**              | Numero univoco che il client inserisce nel messaggio, il server lo replicherà nella risposta, viene usato per capire quale risposta corrisponde a quale query, in quanto un client potrebbe fare query in parallelo a diversi DNS |
| **QR (Query Type)** | Richiesta o risposta                                                                                                                                                                                                              |
| **AA**              | Indica se il server che risponde è un'autorità oppure no                                                                                                                                                                          |
| **RA**              | Il client richiede un richiesta _ricorsiva_                                                                                                                                                                                       |
| **RCODE**           | Codice di risposta (ok: $0$, errori: $1-5$)                                                                                                                                                                                       |
| **QDCOUNT**         | Numero di _Question_ nel messaggio                                                                                                                                                                                                |
| **ANCOUNT**         | Numero di _Answer_ nel messaggio                                                                                                                                                                                                  |
| **NSCOUNT**         | Numero di _Authority_ nel messaggio                                                                                                                                                                                               |
| **ARCOUNT**         | Numero di _Additional_ (information) nel messaggio                                                                                                                                                                                |

Gli ultimi quattro campi sono chiamati **Resource Records (RR)** e anch'essi possiedono un formato specifico:

| Campo        | Descrizione                                                                                                             |
| ------------ | ----------------------------------------------------------------------------------------------------------------------- |
| **NAME**     | Il nome che è stato richiesto                                                                                           |
| **TYPE**     | A: IPv4, AAAA: IPv6, NS: server autoritario                                                                             |
| **TTL**      | Indica il numero di volte che questa informazione può essere memorizzata prima di dover essere richiesta un'altra volta |
| **RDLENGTH** | Lunghezza del campo _RDATA_                                                                                             |
| **RDATA**    | L'informazione effettiva                                                                                                |

>Questo tipo di protocolli sono difficili da modificare, per cui molto spesso possiedono dei bit non utilizzati destinati per usi futuri.

### Reverse DNS
Quando si registra un dominio è possibile (non obbligatorio) aggiungere un **PTR** resource record in cui si va a specificare il dominio in una forma speciale ad esempio: `5.3.2.1.in-addr.arpa`.

Il dominio `in-addr.arpa` è utilizzato per eseguire i **reverse lookup** i quali consentono di tradurre indirizzi IP in nomi di dominio.
Se Alice volesse conoscere l'indirizzo di dominio associato a `1.2.3.5`, eseguirà una query DNS cercando `5.3.2.1.in-addr.arpa`, ciò fornirà una lista di domini associati a tale IP.

I **byte vengono invertiti** nella query in quanto anche il reverse DNS è gerarchico, `in-addr.arpa` non conosce tutte le risoluzioni, ma delega alle entità che possiedono tale indirizzo IP, e dato che gli indirizzi IP sono anch'essi gerarchici dobbiamo seguire tale gerarchia.

## DNS operations
Normalmente durante la risoluzione il DNS locale scopre più di un DNS autoritario, essendo i server DNS **ridondanti**, se uno non risponde la stessa query è ripetuta secondo il metodo round-robin a tutti gli altri.

In alcuni casi eseguire una query ad un DNS autoritario potrebbe fornire un indirizzo IP diverso in quanto lo stesso servizio potrebbe essere replicato su più macchine per garantire bilanciamento del carico tra i server.
