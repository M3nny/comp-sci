Un **canale (o mezzo) trasmissivo** è il supporto tramite il quale un segnale si propaga da un punto all'altro di una rete.
- Cavo di rete
- Wi-Fi
- Fibra ottica

Viene a crearsi un **canale di comunicazione** quando due interlocutori si mettono in collegamento.
- **Simplex**: flusso unidirezionale
- **Half duplex**: flusso unidirezionale alternato
- **Full duplex**: flusso simultaneo in ambe le direzioni

>Ci possono essere più comunicazioni su un mezzo, ed una comunicazioni può usare più mezzi.

### Mezzi trasmissivi
La **velocità** di trasmissione è misurata in **bps** o suoi multipli, lo stesso vale per la **larghezza di banda**.
Su un mezzo trasmissivo possono essere realizzati più canali che si spartiscono la banda.

#### Cavo ethernet (doppino telefonico)
Comprende **da due a otto fili di rame** intrecciati, la categoria del cavo ne definisce la banda massima garantita (e.g. Cat. 5/5a/6a/7).

#### Fibra
Costituito da **decine o centinaia fibre di vetro (o materiale plastico)** che trasmettono impulsi di luce.

Un sistema di trasmissione su fibra consiste in una **sorgente luminosa** la quale converte segnali elettrici in impulsi, e di un ricevitore che converte segnali luminosi in segnali elettrici.

#### Wi-Fi
Viene utilizzato un **access point** collegato fisicamente alla rete via cavo che comunica con gli utenti attraverso segnali radio, i computer degli utenti devono essere dotati di una **scheda di rete**.

#### Li-Fi
Il **Li-Fi (Light Fidelity)** è il corrispettivo del Wi-Fi ma con frequenze che appartengono allo spettro della luce visibile.

In questo modo è possibile **comunicare tramite segnali di luce** senza dover invadere l'intervallo di frequenze radio.
>Il segnale è limitato alla portata ottica (4m).

### Networking
Identifichiamo tre tipologie di rete in base alla loro estensione fisica:
- **LAN (Local Area Network)**: rete composta da computer collegati tra loro solitamente all'interno di un singolo edificio
- **MAN (Metropolitan Area Network)**: collega tra loro varie LAN, solitamente ci si riferisce ad una MAN come la rete di una città
- **WAN (Wide Area Network)**: una rete di grande estensione che connette varie sotto-reti, _Internet_ è una WAN

### TCP/IP
Lo stack TCP/IP è un insieme di **protocolli** costruito su un modello a livelli in cui le informazioni vengono incapsulate ed eventualmente frammentate.

Ogni host è identificato da un **IP univoco** all'interno di una rete.

### Dispositivi di rete
- **Scheda di rete (NIC)**: permette di collegare un host alla rete, ogni scheda è dotata di un indirizzo MAC che ne identifica produttore ed essa stessa
- **Hub**: inoltra i pacchetti in arrivo su tutte le porte
- **Switch**: mantiene una tabella di corrispondenza tra porte e indirizzi MAC delle NIC associate
- **Router**: instrada i pacchetti di rete
- **Access point**: instrada pacchetti dalla LAN ad Internet e viceversa, viene anche definito default gateway

### Indirizzi MAC
Il **MAC (Media Access Control)** è un codice di $48$ bit ($6$ byte) univoco per ogni scheda di rete, i quali identificano la scheda ed il produttore.

È modificabile a livello software, inoltre i $48$ bit sono divisi in $12$ cifre esadecimali:
- Le prime $6$ individuano il produttore dell'interfaccia di rete
- Le successive $6$ corrispondono al numero di serie della scheda stessa

### IPv4
Sono composti da $32$ bit raggruppati in $4$ gruppi da $8$ bit, è possibile distinguere l'**indirizzo di rete** da quello dell'**host** grazie alla **netmask**, la quale indica quali bit dell'indirizzo indicano la rete di appartenenza.

L'indirizzo di rete si può ottenere tramite _and_ logico tra IP e netmask:
$$157.138.22.21 \land 255.255.255.0 = 157.138.22.0$$

Gli indirizzi IP sono divisi in **cinque classi** le quali differiscono per il numero di host che ciascuna rete può contenere, sono facilmente riconoscibili dalla netmask:
- **Classe A**: `/8 -> 1.0.0.0 - 127.255.255.255`
	**Privati**: `10.0.0.0 - 10.255.255.255`
 
- **Classe B**: `/16 -> 128.0.0.0 - 192.255.255.255`
	**Privati**: `172.16.0.0 - 172.31.255.255`

- **Classe C**: `/24 -> 192.0.0.0 - 223.255.255.255`
	**Privati**: `192.168.0.0 - 192.168.255.255`

Poi abbiamo due classi per uso speciale, ovvero:
- **Classe D**: `224.0.0.0 - 239.255.255.255`
	Identifica gli indirizzi multicast, non assegnabili ai singoli host
- **Classe E**: `240.0.0.0 - 255.255.255.255`
	Riservati per usi futuri

#### Indirizzi speciali
Alcuni indirizzi non possono essere assegnati per l'identificazione di un host in una sotto-rete, ovvero:
- **Default**: `0.0.0.0`
	viene assegnato a dispositivi che non possiedono ancora un IP assegnato nella rete
- **Indirizzo di rete**: `X.X.X.0`
- **Broadcast sotto-rete**: `X.X.X.255`
- **Broadcast di rete**: `255.255.255.255`
- **Loopback**: `127.0.0.1`

### IPv6
Gli indirizzi IPv4 sono ancora utilizzati grazie al [[IPv4#Network Address Translation (NAT)|NAT]], altrimenti non ce ne sarebbero abbastanza per coprire tutti i dispositivi, tenere una tabella di NAT rallenta i router, questo è un problema che risolverebbe [[ICMP e IPv6#IPv6|IPv6]] in quanto non sarebbe necessario creare sotto-reti dato che gli indirizzi disponibili sarebbero ordini di grandezza superiori.

