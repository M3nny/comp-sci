Il **Basic Input Output System (BIOS)** controlla la prima fase del processo di avvio, ovvero controlla le periferiche e cerca una unità di massa da cui avviare il sistema operativo.

Recentemente il concetto di BIOS è stato sostituito da **BIOS UEFI (Unified Extensible Firmware Interface)**, esso consente di avviare da dischi molto capienti grazie a **GUID Partition Table (GPT)**, inoltre possiede dei vantaggi come:
- Architettura indipendente da CPU e driver
- Ambiente **preOS**
- Eliminazione della necessità di un bootloader
- Esecuzione di moduli firmati (**secure boot**), a differenza del sistema precedente basato su **Master Boot Record (MBR)**, utilizza dei moduli firmati per la definizione dei boot record associati all'avvio dei sistemi operativi

Una volta finiti i check, il BIOS **cerca un MBR** solitamente memorizzato nel primo settore del disco, ne carica il contenuto in memoria e gli passa il controllo.
Successivamente il MBR cerca la prima partizione _attiva_, ne **legge il record di avvio**, il quale contiene istruzioni su come caricare il **boot loader** ed infine carica quest'ultimo e gli passa il controllo.
>Una partizione è detta attiva se la sua flag di boot è posta a $1$.

### Boot loader
In **Windows** il compito di boot loader veniva svolto da **NTLDR.exe**, il quale faceva scegliere un sistema operativo mostrando un'interfaccia basata sulle informazioni di **boot.ini**.

Per **Linux** viene utilizzato solitamente **GRUB (GRand Unified Bootloader)**, esso gestisce facilmente il boot di più OS anche su dischi diversi.

Dopo aver scelto un'opzione dal boot loader, viene caricato in memoria il **kernel** del sistema operativo, esso controlla le periferiche, carica i driver e dopo aver riconosciuto le partizioni cede il controllo al processo **init**.

**Initrd** è un piccolo file system temporaneo che viene carico in memoria nella fase iniziale di boot, la sua funzione è fornire al kernel i moduli che non possiede al suo interno e senza di essi potrebbe non far funzionare qualche periferica.
>Initrd è un file, mentre init è un processo.

**Runlevel** è uno stato del sistema che permette solo determinate azioni, ne esistono **sette**, da $0$ a $6$.
```bash
# mostra il runlevel corrente
runlevel

# passa a runlevel 3
init 3
```

**SysV Init** era il processo standard in Linux per controllare l'esecuzione all'avvio, funzionava così:
- Il kernel carica init in `/sbin` e lo avvia cedendogli il controllo
- Init diventa padre di tutti i processi avviati automaticamente dal sistema
- Init legge `/etc/inittab` per leggere la configurazione di ogni runlevel
- Init avvia tutti i processi in background
- Init avvia i processi delle console di sistema ed esegue `/etc/rc.local`

Al giorno d'oggi **Systemd** ha rimpiazzato init fornendo flessibilità e semplicità nell'avvio di daemon.

## Partizionamento
Una fase importante durante l'installazione di un sistema operativo è quella di **partizionamento** dello storage, che è differente in base alla tipologie di server da installare.

Lo **swap** viene utilizzato per liberare memoria RAM, contiene i dati che hanno minore probabilità di essere richiesti in futuro, tuttavia quando si usa questa memoria le prestazioni crollano in quanto è locata su hard disk.

Esistono due modi principali per la gestione dello swap:

| Area di swap           | File di swap                                          |
| ---------------------- | ----------------------------------------------------- |
| Dimensione fissa       | Dimensione variabile                                  |
| Nessuna frammentazione | Rischio di frammentazione                             |
| Migliori performance   | Performance vincolate dalle operazioni di I/O su file |

Su **Linux** fino a pochi anni fa l'area di swap doveva essere più grande della capacità della RAM in quanto avrebbe dovuto contenere l'intero dump della memoria in caso di crash del kernel, attualmente la sua dimensione varia dal $10\%$ al $50\%$ della capacità della RAM.

Su **Windows** lo swap è gestito da `pagefile.sys`, ed i dump di memoria solitamente si trovano in `C:\Windows\System32`.

### LVM
**Logical Volume Manager (LVM)** è un software per facilitare la gestione dello storage, l'idea di base è quella di tratta i dischi come risorse flessibili all'interno di un pool unificato detto **volume group**, ciò consente di ridimensionare lo spazio su disco dinamicamente creando dei **volumi logici**.

Se si ha bisogno di più spazio per una applicazione o servizio è possibile ridimensionare un volume logico al volo senza smontare il file system o interrompere il servizio.
>È usato su server, database e NAS per gestire lo storage.

![[LVM.png]]
- **Physical Volumes (PV)**: rappresentano i dischi fisici
- **Volume Groups (VG)**: è un insieme di PV, un VG può essere visto come un grande disco virtuale composto da dischi fisici
- **Logical Volumes (LV)**: vengono usati come partizioni dei dischi virtuali (VG)

Oltre alla flessibilità, LVM consente di creare **snapshot** dei volumi, **migrare** i dati da un disco fisico ad un altro senza interruzioni, e in generale offre un **gestione centralizzata** dello storage.

**Comandi**:
```bash
# Inizializzazione dei Physical Volumes
pvcreate /dev/sda
pvcreate /dev/sdc2

# Creazione di un Volume Group
vgcreate master-vg /dev/sda /dev/sdc2

# Creazione di Logical Volumes
lvcreate -L 50G -n home-lv master-vg

# Formattazione e montaggio
mkfs.ext4 /dev/master-vg/home-lv
mount /dev/master-vg/home-lv /home

# Ridimensionamento dei Logical Volumes
lvextend -L +50G /dev/master-vg/home-lv
resize2fs /dev/master-vg/home-lv

# Creazione di snapshot
lvcreate -L 5G -s -n home_snapshot /dev/master-vg/home-lv

# Migrazione dei dati tra dischi
pvmove /dev/sdc2 /dev/sdb1
```

>[!Example]
>Supponendo di disporre di uno **storage da 10 TB** e **512 gb di RAM**, come partizionereste il sistema Linux con autenticazione centralizzata ed export delle Home? Per comodità si immagini di dover gestire **50 utenti**, si stima che ogni utente possa occupare al massimo **100gb di spazio**. Considerare **swap=0,25 ram, swap=0,5 ram , swap=0,75 ram**. Calcolare la swap anche con il metodo classico. **Quanti utenti può ospitare il sistema?**
>
>Possibile soluzione:
>- `swap` (metodo classico): $512GB\cdot 1.5$
>- `swap` ($0.5$): $512GB\cdot 0.25$
>- `/home`: $50\cdot 100GB+10\%$
>- `/`: $500GB$
>- `/var`: $1TB$
>- `/var/log`: $500GB$
>- `/usr`: $1.5TB$
>
>Considerando $100GB$ ad utente e considerando $swap=\frac{ram}{2}$:
>$$NumUtenti=\frac{\text{storage-ram}}{\text{spazio per utente}}=\frac{10TB-256GB}{100GB}\simeq 100\text{ utenti}$$ 

### Protocollo SSH
Il protocollo **Secure SHell (SSH)** permette di stabilire una sessione remota cifrata da riga di comando con un altro host.
```bash
ssh utente@example.com
```

È anche possibile spedire e ricevere file da un sistema remoto con il comando `scp`, oppure tramite `sftp`.

Per evitare di effettuare il login ogni volta sul host remoto si utilizza una **coppia di chiavi** (pubblica e privata) per autenticarsi, e per sbloccare le chiavi viene richiesta una **passphrase**, il che è comoda in quanto verrebbe usata la stessa per ogni host a cui ci vogliamo collegare al posto di inserire la password di ogni host remoto.

Lasciare una **passphrase vuota** è sicuramente più comodo in quanto non verrà più richiesta alcuna password o passphrase, però il furto della chiave sarebbe un grande problema.

Con **ssh-agent** tuttavia si può mantenere la chiave sbloccata per la sessione corrente.

Una volta collegati all'host remoto si dovrà **memorizzare la propria chiave pubblica** all'interno delle chiavi autorizzate, questo può essere fatto manualmente oppure attraverso il comando `ssh-copy-id`.

