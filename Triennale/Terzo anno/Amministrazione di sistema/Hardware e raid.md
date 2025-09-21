Facciamo un ripasso sulle [[Tipologie di memoria|tipologie di memoria]].

Le **memorie centrali** contengono un numero limitato di informazioni e si dividono in:
- **RAM**: contiene i dati dei programmi in esecuzione in modo volatile
- **ROM**: contiene dati in sola lettura, tra cui il BIOS
- **Cache**: mantiene i dati che verranno usati a breve dalla CPU oppure quelli che sono stati usati da poco

Le **memorie di massa** hanno lo scopo di **conservare i programmi in modo permanente**, esse possono essere interne se presenti dentro al case, esterne altrimenti, inoltre si presentano in vari formati, tra cui: floppy disk, hard disk e SSD.

A differenza di un PC, <u>in un server sono ridondati più componenti possibili</u> (e.g. più alimentatori), questo per garantire la massima **resilienza** in caso di guasti.

I server possono essere **tower** (ormai in disuso) o **rack**, ovvero inseribili in un **armadio rack**.
Un **sistema blade** è composto da una serie di lame che contengono CPU e RAM e che **condividono uno storage**.

Le componenti hardware di un server sono più performanti di quelli di un PC, le CPU hanno **più core**, la RAM oltre ad essere **più veloce e capiente** possiede sistemi di sicurezza per evitare corruzione dei dati in caso di malfunzionamento.

I **dischi** sono più veloci e **hot-swappable**, inoltre sono disposti in **RAID**.

Sistema di **amministrazione remota iLO (integrated Lights-Out)**, è fisicamente una porta ethernet che consente di eseguire operazioni in remoto, questa tecnologia possiede una rete separata, con le seguenti caratteristiche:
- **Riavvia** il server nel caso non risponda attraverso la normale connessione di rete
- **Accende** il server
- **Monta immagini** CD/DVD da remoto
- Accesso al server **IML (Integrated Management Log)**

Elenchiamo anche:
- Molteplici **schede di rete** con throughput elevato
- Sistema di **raffreddamento** con ventole ridondate in sovrannumero
- **Alimentatori** ridondati, sovradimensionati e hot-swappable

## RAID (Redundant Array of Inexpensive Disks)
Un **RAID** rappresenta un'astrazione che, dato un gruppo di **dischi di solito omogenei tra loro**, costruisce una **unità di storage logica**, che viene vista dal sistema operativo come **un'unica memoria di massa** indipendentemente dal tipo di RAID che viene usato e dai dischi che lo compongono.
>Per omogenei si intende della stessa dimensione e con stessa velocità.

Risolve problemi specifici con un occhio al costo:
- **Capacità**: è possibile sommare la capacità di vari dischi
- **Sicurezza**: permette di avere dischi ridondati (**Mirroring**) o **controlli di parità** sui dati
- **Velocità**: aumenta le performance distribuendo i dati sui vari dischi (**Stripping**) permettendo l'accesso parallelo ai dati in lettura

Un RAID può essere di tipo:
- **Software**: se è gestito dal sistema operativo
- **Hardware**: se è gestito da un hardware apposito

Nei server il RAID è di tipo _hardware_ ed è gestito dal **controller dei dischi**, il quale può creare e cancellare un RAID, mantenerne lo schema ed in caso di guasto sostituirne un elemento se è previsto un RAID con **fault tollerance**.
>Il controller operare all'insaputa del sistema operativo ed è dotato di cache.

### RAID 0
Detto anche **stripping**, è un sistema in grado di separare i dati in segmenti e scrivere quest'ultimi in dischi diversi in modo da velocizzare la successiva lettura.
![[RAID 0.png|200]]

**Non è sicuro** in quanto basta un disco guasto per perdere tutti i dati, però ha alte prestazioni.
>Necessita di almeno **due** dischi.

### RAID 1
Detto anche **mirroring**, mantiene una copia degli stessi dati in più dischi diversi, ciò porta ad una maggiore velocità di lettura, ed una minore velocità di scrittura in quanto dovrà replicare i dati scritti su più dischi.
![[RAID 1.png|200]]

Ottiene la **massima ridondanza dei dati**, adatto a piccoli sistemi che compongono un sistema più grande.
>Necessità di almeno **due** dischi.
### RAID 3
Simile allo **stripping**, ma in un disco vengono memorizzate le **stringhe di parità**, ovvero una specie di mappa che permette la ricostruzione dei dati in caso di guasti.
![[RAID 3.png|300]]

**Non è espandibile** in quanto il disco di parità non riuscirebbe a contenere tutte le stringhe, per espanderlo è necessario sostituire tutti i dischi.

Alte prestazioni in accesso a grossi file, ma letture e scritture non sono simultanee.
>Necessità di almeno **tre** dischi.

### RAID 5
Ottimizzazione del RAID 3, le **stringhe di parità** sono salvate in modo ordinato in tutti i dischi del raid.
![[RAID 5.png|300]]

Possiede una capacità pari a:
$$\text{Capacità}=((n-1)\cdot C)$$
- $n$: numero di dischi
- $C$: capacità dei dischi

Usato in grandi sistemi multiutenza dove le scritture sono molto meno rispetto alle letture.

**Fault tollerance** pari a $1$.
>Necessità di almeno **tre** dischi.

### RAID 6
Utilizza una divisione a livello di blocchi con i <u>dati di parità distribuiti due volte tra tutti i dichi</u>.
![[RAID 6.png|400]]

Molto inefficiente se usato con molti dischi.

**Fault tollerance** pari a $2$.
>Necessità di almeno **quattro** dischi.

### RAID 1+0
È una combinazione tra RAID 1 e 0, è <u>in grado di rigenerare i dati anche in presenza di rotture di più dischi</u> mantenendo buone prestazioni.
![[RAID 1+0.png|300]]

<u>Non vengono gestire le informazioni di parità</u> per cui ha migliori prestazioni del RAID 5/6.

È **costoso** in quanto la capacità dei dischi viene dimezzata.

Usato in grandi sistemi in cui si necessita di alte prestazioni con un occhio alla sicurezza, senza badare a costi.
>Necessita di un numero pari di dischi, almeno **quattro**.



