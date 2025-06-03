I **filesystem** si occupano di gestire i file all'interno di un sistema operativo, essi sono visti differentemente da utente e OS:
- **Utente**: appaiono come un insieme di file e directory
- **OS**: è un insieme di strutture di controllo e blocchi di dati che occupano una partizione del disco

### Vista utente
Un **file** è un'astrazione del sistema operativo che permette di usare in modo semplice ed efficiente i dispositivi di memoria secondaria.
>La lunghezza massima di un nome varia in base al sistema operativo.

Esistono diversi **tipi di file**:
- **File regolari**: rappresentati in formato ASCII o BIN
- **Directory**: contengono vari file e sono organizzate in una struttura gerarchica
- **File speciali a blocchi**: unità di I/O a blocchi
- **File speciali a caratteri**: unità di I/O a caratteri

Una **directory** è un elenco di nomi di file (e/o altre directory) a cui è associato un nome.

### Filesystem in Linux/Unix
- `/etc`: file di configurazione del sistema
- `/bin`: programmi essenziali (e.g. `ls`)
- `/sbin`: programmi essenziali utilizzabili con permessi elevati
- `/lib`: librerie dinamiche usate dai programmi delle due directory precedenti
- `/usr`: programmi non necessari per l'avvio del sistema, al suo interno contiene `/usr/bin`, `/usr/sbin`, `/usr/lib` e `/usr/share`
- `/usr/local`: dispone di sotto-directory simili a quelle di `/usr`, dove vengono memorizzati programmi e librerie installati dall'amministratore (al di fuori di quelli forniti dalla distribuzione)
- `/home`: spazio di memorizzazione personale
- `/root`: home directory dell'utente root
- `/var`: dati relativi ai daemon che forniscono i vari servizi
- `/dev`: file che rappresentano i dispositivi presenti nel sistema
- `/tmp` e `/var/tmp`: usati per memorizzare file temporanei
- `/opt`: simile a `/usr/local`, viene usato per programmi che non seguono la convenzione di separazione tra binari, librerie e file accessori.
- `/boot`: file necessari al boot loader
- `/proc`: file che rappresentano i processi in esecuzione nel sistema (viene mantenuta una directory per processo in esecuzione) e lo stato del sistema
- `/sys`: rappresenta altre configurazioni riguardanti l'hardware a tempo di esecuzione
- `/run`: mantiene alcuni piccoli file per applicazioni di sistema necessari per farle cooperare, non è necessario che vengano mantenuti ad ogni riavvio

La directory `/var/log` è particolarmente importante in quanto contiene i **log del sistema**, ad esempio un web server potrebbe salvare le richieste che gli sono arrivate all'interno di un file di log salvato all'interno di questa directory.

### Journaling
Il **journaling** rappresenta una tecnica implementata da molti filesystem moderni per preservare l'integrità dei dati da eventuali cadute di tensione o reset improvvisi.

È derivata direttamente dalle **transazioni** dei database, infatti quando un processo vuole memorizzare informazioni sul disco, prima memorizza le operazioni che intende fare su un file di log e, solo dopo, eseguirà la scrittura sul disco, e nel mentre "segnerà" quali operazioni (tra quelle dichiarate) ha completato.

In caso di caduta di tensione durante la scrittura nel disco, al riavvio, il file system sarà in grado di **correggere gli errori** presenti nella sua struttura.

### Filesystem popolari
**FAT**
Basato su File Allocation Table (FAT), rende facile la creazione di driver.

**NTFS**
Sviluppato da microsoft, si basa sulla Master File (allocation) Table, ed è journaled.

**exFAT o FAT64**
Versione estesa di FAT, pensato per memorie flash, permette di memorizzare più file (anche più grandi) rispetto a FAT, inoltre possiede il controllo degli accessi e ha prestazioni migliori.

**Ext4**
Filesystem di default su Linux, è journaled e retrocompatibile con le versioni precedenti, supporta grandi file (16 TB) e partizioni grandi fino a 1 EB.

**HFS+**
Una versione del vecchio HFS, ma journaled, la sua affidabilità si riduce con l'aumentare del peso del OS che supporta.

**APFS**
File system realizzato da Apple come alternativa a HFS+, ottimizzato per memorie flash ed implementa il _copy-on-write_, ovvero un meccanismo che riduce le operazioni di duplicazione delle risorse attraverso l'eliminazione delle copie non necessarie.
