Espandere la capacità di storage al crescere delle esigenze era un problema tempo fa, infatti veniva utilizzata la tecnologia **DAS (Direct Attached Storage)** o **SAS (Server Attached Storage)** in cui lo storage era fisicamente collegato ai server.

## NAS
Un **NAS (Network Attached Storage)** è un host con **grandi capacità di storage** e spesso scarse di calcolo.

Viene utilizzato come **storage**, in modi diversi in base agli usi, esso infatti può servire per memorizzare:
- Home utenti
- Backup
- Database e siti web

Esso può contenere più **volumi** che possono essere replicati su altri NAS.
>Un NAS è dotato di sistema [[Hardware e raid|RAID]].

## SAN
Una **SAN (Storage Area Network)** utilizza i NAS per creare una LAN dedicata allo storage, la quale è affiancata alle LAN aziendali per non impattare sulle prestazioni di quest'ultime.

Ciò consente una grande **scalabilità** e permette di collocare le risorse dove servono, inoltre consentono di aggiungere storage senza interrompere i servizi.

Nel caso si volesse accedere ai dati di una SAN locata in un altro posto geografico si può utilizzare la [[Networking#Fibra|connessione in fibra]] (se vicino), altrimenti protocolli di **storage over IP**.

Il **cloud** può essere visto come una grande SAN.
