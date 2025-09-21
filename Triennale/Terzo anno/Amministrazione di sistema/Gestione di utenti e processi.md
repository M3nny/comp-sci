I sistemi UNIX hanno una **singola gerarchia**, quindi non esiste il concetto di lettera di unità come in Windows.

Per estendere il file system se ne innesta un altro all'interno di una directory detta **mountpoint**.
>La configurazione dei mountpoint è definita in `/etc/fstab`.

Tramite `df -h` è possibile vedere lo spazio del disco occupato dai vari file system montati.

Per creare un file system si utilizza il comando `mkfs`, la sua sintassi è la seguente:
```bash
# mkfs.<filesystem> /partizione
mkfs.ext4 /dev/sdd1
```

## Utenti e gruppi
In sistemi Unix-like, ogni utente è descritto dai seguenti campi:
- Login name
- User ID (ciò che lo identifica realmente)
- Gruppo primario
- Home directory
- Login shell

I **gruppi** vengono usati per assegnare dei permessi in modo collettivo agli utenti appartenenti a tale gruppo.

Esiste un utente speciale con **UID 0** che è il **root**, l'amministratore di sistema userà tale utente tramite `su` il quale apre una shell come utente root, volendo si possono eseguire comandi con permessi di root tramite `sudo <comando>` a patto che si faccia parte del gruppo `sudo`.
>In Windows `Administrator` e `runas` sono i corrispettivi di `root` e `sudo`.

### Permessi
Ogni oggetto del file system in Unix ha associati un utente ed un gruppo che lo posseggono, vedi [[Unix access control#Controllo degli accessi|controllo degli accessi]].

Si distinguono i permessi, composti da **9 bit**, di **lettura** (`r`), **scrittura** (`w`), **esecuzione** (`x`) per ogni **utente** (`u`) appartenente al **gruppo** (`g`).

I **modificatori** sono invece, `setuid`, `setgid` e `sticky bit`.

Per cambiare il proprietario ed il gruppo di un file si usano rispettivamente i comandi `chown` e `chgrp`, mentre per cambiare i permessi si usa `chmod`.

Lo **sticky bit** viene usato per le directory destinate a contenere file temporanei di più utenti, se viene impostato su una directory indica che i file al suo interno possono essere cancellati o rinominati solo da:
- Proprietario
- Proprietario della directory
- Root
>Viene spesso usato sulle directory `/tmp` e `/var/tmp`.

Il modificatore **setuid** permette di eseguire un file con i permessi del suo proprietario, un esempio è l'assegnazione di tale permesso al comando `mount` per permettere anche agli utenti normali di montare dei file system (e.g. chiavette USB) con i permessi di root, cosa che altrimenti non potrebbero fare.

Analogamente **setgid** permette di eseguire un file con i permessi del gruppo a cui appartiene anche se l'utente non possiede i permessi di tale gruppo, mentre sui file non eseguibili permette di usare il **mandatory locking**, ovvero un lock non aggirabile dai processi (utile per alcuni file in `/tmp`e `/run`).

Ad oggi non esiste un completo consenso su un modello di permessi da adottare, per cui la base comune è quella descritta finora.

È possibile assegnare una <u>quantità massima di spazio sul disco occupato</u> detta **quota**.
```bash
# restituisce lo stato
quota <utente>

# cambia la configurazione della quota per tale utente
edquota -u <utente>
```

## Controllo dei processi
In Unix ogni programma in esecuzione è rappresentato da almeno un processo identificato da un **PID**, ed i suoi permessi (ad eccezione di modificatori) sono quelli dell'utente che lo ha avviato.

È possibile **terminare** un processo tramite `kill`, inoltre è possibile modificare la sua **priorità di esecuzione** usando i comandi:
- `nice`: esegue un programma con una determinata priorità
- `renice`: cambia la priorità di un processo in esecuzione
- `ionice`: cambia la classe di I/O scheduling e la priorità del processo

### Gestione della rete
È possibile vedere le connessioni di rete effettuate dai processi in esecuzione:
```bash
# --inet: solo connessioni IP
# -a: tutti i socket
# -n: solo gli IP degli host collegati
netstat --inet -an
```

La **gestione delle interfacce** avviene tramite `ifconfig`, il file di configurazione di rete si può trovare in `/etc/netplan` nella maggior parte delle distribuzioni, mentre la configurazione dei DNS si trova invece in `/etc/resolv.conf` il quale viene generato dalle configurazioni specificate nella configurazione di rete.
