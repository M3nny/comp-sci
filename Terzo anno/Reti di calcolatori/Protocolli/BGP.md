Un  **Autonomous System (AS)** è una collezione di IP sotto il controllo di uno o più operatori che rispondono ad una singola entità amministrativa (e.g. ISP, governi), inoltre essi possiedono un numero identificativo fornito da IANA.

Uno **Stub AS** è un AS finale, ovvero non provvede transito di pacchetti verso altri AS (e.g. università, organizzazioni), ciò non vieta che possa essere connesso ad uno (single-homed) o più (multi-home) AS.

Un **transit AS** è un AS che connette molteplici AS consentendo ai pacchetti di passare attraverso esso.

Gli AS hanno dei **Point of Presence (POP)**, ovvero posti dove sono fisicamente accessibili.

Esistono due modi principali per collegare degli AS:
- **Private peering**: connessione diretta privata e solitamente non dichiarata tra due router di due AS differenti
- **Internet Exchange Points (IXP)**: rappresentano data-center condivisi dove gli AS mettono i loro POP e si connettono uno all'altro

In un **accordo di transito** commerciale tra un AS $A$ ed un AS $B$ dove $B$ offre ad $A$ di connettersi ad Internet si dice che $B$ funge da **gateway** per $A$.

- Un **accordo transito** solitamente prevede un prezzo da pagare per connettersi ad Internet
- Un **accordo di peering** solitamente è un affare gratuito tra due AS in modo che possano scambiarsi il traffico senza costo

## BGP
Un AS può decidere autonomamente come gestire il routing interno, tuttavia per comunicare tra vari AS esiste un singolo protocollo, ovvero il **Border Gateway Protocol (BGP)**.

Nel routing intra-dominio, un [[ICMP e IPv6#Aree OSPF|router OSPF]] condivide sempre tutti i prefissi che conosce, ciò non è sempre il caso nel routing inter-dominio, a causa di accordi commerciali.

<u>Ogni AS deve possedere un router che supporti il protocollo BGP</u>, il quale condividerà il proprio prefisso di rete, ma volendo anche quello di altri AS. 
Tale router oltre al BGP eseguirà il suo protocollo di routing interno (come l'OSPF).
![[Small internet.png]]
In questo esempio AS150 è un **multi-homed stub AS** che possiede la rete di classe C $10.150.0.0/24$.
1. Il router $A$ condivide $10.150.0.0/24$ al router $D$ e $B$, rispettivamente in AS11 e AS151
2. Entrambi gli AS offrono transito verso AS150, quindi annunceranno il prefisso da AS150 (non lo re-inoltreranno però ad $A$)
3. Il router $B$ condivide $10.150.0.0/24$ al router $D$ aggiungendo $151$ al path, mentre il router $D$ condividerà sempre $10.150.0.0/24$ a $B$ aggiungendo $11$ al path

Alla fine dell'ultimo punto i router $B$ e $D$ possiedono due routes per raggiungere $A$, una diretta ed un'altra con due hop, tuttavia **non esisteranno cicli**.

Questo è possibile perchè <u>i router non condividono il prefisso con il router che lo ha inviato inizialmente</u>, inoltre prima di condividere un prefisso <u>gli AS controllano che esso non sia già presente nel path</u>, in modo da evitare cicli.

Il protocollo BGP può essere usato anche internamente ad un AS, in questo caso si parla di **Internal BGP (IBGP)**.

4. I router $D,E,F$ fanno parte dello stesso AS, e quindi $D$ condivide $10.150.0.0/24$ con $E$ ed $F$, tuttavia non aggiunge nulla al path

AS3 e AS160 sono dei **single-homed stub AS**.
5. Il router $F$ condivide $10.150.0.0/24$ con $G$ aggiungendo $11$ al path
6. Il router $E$ condivide $10.150.0.0/24$ con $C$ aggiungendo $11$ al path

Alla fine del processo il prefisso $10.150.0.0/24$ sarà propagato in tutta la nostra piccola inter-rete di esempio, poi ogni altro AS condividerà i propri prefissi con la stessa procedura.

### Routing, recessi e malfunzionamenti
BGP utilizza i principi del [[Livello di rete#Distance vector routing|distance vector routing]] con tre differenze principali:
- Non esporta solo la distanza dalla destinazione, ma anche tutto il path degli AS, infatti è chiamato **Path Vector Protocol**
- **Non condivide regolarmente aggiornamenti**, ma solo quando qualcosa cambia o qualcuno lo chiede esplicitamente
- I messaggi di update contengono **informazioni riguardanti solo alcuni prefissi**, non tutta la routing table

Se per qualche motivo AS150 smetterà di utilizzare il prefisso $10.150.0.0/24$ inoltrerà un **messaggio di recesso**, e come il prefisso è stato condiviso, ora verrà anche cancellato.

Nel caso il link da $A$ a $D$ si rompesse, $D$ ritirerà $10.150.0.0/24$ da $B,E,F$, tuttavia $D$ ha un path alternativo passando attraverso AS151, per cui annuncerà un nuovo path che passerà attraverso $11,151,150$.

### Dettagli del protocollo
Nel grafo BGP **un peer è un vicino** indipendentemente dalla relazione commerciale in utilizzo.

BGP può inoltrare cinque tipi di messaggi:
- **Apertura**: per stabilire connessioni BGP
- **Aggiornamento**: per trasferire informazioni di routing tra peer
- **Keepalive**: per controllare se i peer sono ancora raggiungibili
- **Notifica**: per notificare degli errori ai peer
- **Route-refresh**: un tipo di messaggio usato per supportare la capacità di Route Refresh

In un **messaggio di aggiornamento** ci sono due sezioni:
- I prefissi da condividere
- I prefissi da ritirare
>Non è presente crittografia, autenticazione o segretezza.

### Path prepending
Nel seguente esempio l'AS $6$ può scegliere due percorsi per arrivare a $1$, dove quello di destra è più veloce.
![[Path prepending.png]]

AS1 il quale è un **multi-homed stub** può convincere gli altri AS a percorrere un tragitto con più hop ma con capacità più ampia verso esso, per farlo:
- Condivide il prefisso a $3$ con path $1$
- Condivide il prefisso a $2$ con path $1,1,1,1,1,1$

AS6 riceve due aggiornamenti:
- $5,3,1$
- $4,2,1,1,1,1,1$

AS6 in questo modo utilizzerà il più corto, di conseguenza AS4 e AS2 andranno verso sud.
>Nel caso di malfunzionamento tra AS3 e AS5 comunque AS6 fornirebbe un backup dopo che AS5 inoltra il messaggio di recesso.

Questa tecnica è detta **path prepending** ed è usata per bilanciare il carico su ogni link.

### BGP anycast
Nella rete seguente AS1 e AS6 condividono lo **stesso prefisso**.
![[BGP anycast.png]]

Su internet è possibile che lo stesso prefisso sia condiviso da più di un AS, gli altri AS eseguiranno una route verso quello più vicino.
>Ciò vuol dire che per qualche applicazione più di un host può possedere lo stesso IP.

**Anycast** consente di avere servizi ridondanti eseguendo una route verso l'IP più vicino.

Il path migliore però può essere **ambiguo**, ad esempio se esistesse AS7 tra AS3 e AS5 esso potrebbe cambiare la sua decisione di routing con il tempo.

Per questo motivo **Anycast non è mai utilizzato con servizi stateful** come una connessione TCP, bensì è utilizzato per servizi con stile richiesta-risposta come il DNS.

>[!Info] Anycast a server di root
>Quando viene eseguita una richiesta ad un dominio, BGP inoltrerà la richiesta alla copia più vicina del server DNS, essi sono tutti sincronizzati, non importa se BGP cambia la sua decisione di routing, essendo la richiesta indipendente da quella precedente il sistema funzionerà.
