Per **backup** si intende gestire le copie dei dati, e l'operazione di estrazione dei dati da un _backup_, è detta **restore**.

Deve essere effettuato su unità di storage diverse da quelle che contengono i dati da proteggere.

---
### Backup in LAN
Prima dell'avvento di [[NAS e SAN]], gli storage erano connessi direttamente ai server e l'unico modo per effettuare un backup era trasferire i dati all'unità di backup tramite la LAN.

Questo porta ad alcuni problemi:
- Traffico elevato sulla LAN
- I server oltre ad elaborare le normali richieste spendono tempo anche a fare il backup
- Spesso i dati da salvare viaggiano in chiaro all'interno della LAN, la quale può essere usata anche dagli utenti

### Backup con NAS e SAN
Con l'avvento di NAS e SAN è ora possibile eseguire backup di qualsiasi tipo senza intasare la banda della LAN e senza limitare le risorse di calcolo.

In ogni caso, è spesso utile avere un **backup del sistema di backup**.

### Tipologie di backup
#### Backup completo
Consiste nell'effettuare periodicamente la **copia completa** di tutti i dati da salvare.

È una soluzione ottimale solo per piccole quantità di dati e/o cicli di backup lunghi.

Un semplice backup della propria home su linux si può eseguire con:
```bash
# creazione del backup
tar cvf m3nny.tar /home/m3nny

# restore
tar xvf m3nny.tar
```

#### Backup incrementale
Questo tipo di backup salva solo i dati modificati successivamente all'orario in cui è stato effettuato l'ultimo backup.
>Si parte in ogni caso da un backup completo il quale dovrà essere rinnovato periodicamente.

Il vantaggio è la **velocità di esecuzione** del backup, lo svantaggio è che spesso il ripristino di uno o più file richiede l'analisi di più backup incrementali.

Per il rispristino di un intero filesystem è necessario recuperare l'ultimo backup completo e poi tutti gli incrementali successivi.

#### Backup differenziale
Sono simili a quelli _incrementali_, ovvero salvano solo i file modificati dall'ultimo backup, però sono **cumulativi**.

Con uno schema differenziale, una volta che un file viene modificato, esso continua ad essere incluso in tutti i backup differenziali successivi (fino al backup completo).

In pratica un backup differenziale <u>contiene tutti i file modificati dall'ultimo backup completo</u>, in questo modo l'operazione di ripristino completo sarà possibile con solo l'ultimo backup completo e l'ultimo backup differenziale.
>Anche in questo caso si parte con un backup completo che dovrà essere rinnovato periodicamente.

**Rsnapshot** è una applicazione in grado di eseguire il backup differenziale di porzioni di file system, sfruttando **rsync** è possibile anche conservare diverse copie di backup realizzate in diversi istanti di tempo, inoltre con **ssh** può effettuare il backup anche di sistemi remoti.
