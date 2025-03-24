La **virtualizzazione** è la creazione di una rappresentazione **virtuale** di un **oggetto**.

Essa rappresenta il modo più completo ed efficace per ridurre le spese, è possibile virtualizzare: <u>app, server, storage e reti</u>.

**Vantaggi**:
- Costi operativi ridotti
- Downtime ridotto
- Miglioramento di produttività efficienza e agilità
- Fornitura di app e risorse più rapido
- Continuità di business e recupero da guasti
- Semplificazione della gestione del data center

### Virtualizzazione dei server
Il **cloud computing** si basa sulla **virtualizzazione di server** in esecuzione su un sistema operativo anch'esso virtuale, in questo modo un unico server fisico potrà svolgere più servizi contemporaneamente.

### Virtualizzazione del desktop
Offre la possibilità di avere dei **thin client**, ovvero macchine poco potenti che si collegano ad un desktop remoto ospitato in un server.
>Anche in questo caso i costi vengono diminuiti.

I tre **tipi di virtualizzazione** più diffusi sono:
- **Virtual Desktop Infrastructure (VDI)**: simula il modello di elaborazione desktop su VM nel cloud, ciò porta ad un investimento iniziale, ma così si va ad eliminare l'esigenza di aggiornare i terminali degli utenti, essi infatti saranno solo dei _thin client_
- **Remote Desktop Services (RDS)**: le applicazioni vengono inviate in streaming all'utente finale il quale interagisce con esse tramite il proprio sistema operativo
- **Desktop as a Service (DaaS)**: desktop completo (con OS e applicazioni) presente all'interno di un cloud, l'utente finale ci può accedere con qualsiasi dispositivo (anche mobile)

### Virtualizzazione della rete
Consiste nella riproduzione di una rete fisica a livello software, offrono le stesse funzionalità e garanzie di una rete fisica, ma assicurano l'**indipendenza dall'hardware**.

### Virtualizzazione dello storage
Astrae i dischi all'interno dei server, nas, etc, e li combina in un **pool di storage** distribuendoli tramite applicazioni software.

Questo metodo viene chiamato **software-defined storage**, alcuni esempi sono google drive e dropbox.

### Macchine virtuali
Un sistema informatico virtuale, viene chiamato **macchina virtuale**, esso è un contenitore di software **totalmente isolato**, dotato di OS e applicazioni.

Uno strato software, denominato **hypervisor**, separa le macchine virtuali dall'host e assegna le risorse di elaborazione a ciascuna macchina dinamicamente.

Vediamo di seguito le **proprietà di una VM**:
- **Partizionamento**: è possibile eseguire più OS sulla stessa macchina fisica suddividendo le risorse dell'host fisico
- **Isolamento**: ogni VM risiede in un ambiente isolato rispetto alle altre VM e host fisico, è possibile garantire la protezione delle prestazioni assicurando ad ogni VM un funzionamento adeguato
- **Incapsulamento**: lo stato di una VM è salvato su file, lo stesso vale per il suo storage
- **Indipendenza dall'hardware**: le VM non dipendono strettamente dall'hardware dell'host, ma dipendono dall'hardware emulato dall'hypervisor

### Sistemi di virtualizzazione
Oltre a sistemi di emulazione famosi come VMware, Microsoft Hyper-V, poniamo l'attenzione su **XEN** il quale non mira ad emulare l'hardware, bensì regola l'accesso alle risorse fisiche dell'host da parte delle varie VM.

Questo approccio prende il nome di **para-virtualizzazione** ed è simile a ciò che viene utilizzato nei mainframe e supercomputer.

Anticipiamo che **docker** utilizza delle feature del kernel Linux per isolare dei processi e mandarli in esecuzione all'interno dei **container**, in modo simile ad una para-virtualizzazione.
