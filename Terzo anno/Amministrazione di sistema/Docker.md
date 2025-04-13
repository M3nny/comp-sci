Un **container** è un oggetto **leggero** dato che sfrutta i servizi offerti dal kernel ospitante, **portabile** in quanto viene distribuito in un formato standard (i.e. immagini docker) ed autosufficiente perchè contiene tutti i dati di cui necessita un'applicazione per essere eseguita senza richiedere particolari configurazioni sull'host.

Un'**immagine docker** elenca tutti i dati di cui necessita l'applicazione da distribuire, essa viene utilizzata per costruire un container, ovvero un'istanza dell'immagine.

>[!Cite] Immagini e container
>Una classe sta ad una immagine come un container sta ad un oggetto di tale classe.

Ogni container è identificato da un **id** unico che cambia ad ogni riavvio del container, tuttavia è possibile fissare un **nome** manualmente per riferirsi sempre ad un determinato container.

Docker possiede performance migliori rispetto ad una macchina virtuale in quanto viene rimosso il layer del **hypervisor**, infatti i processi sono eseguiti dal sistema ospitante sfruttando i servizi offerti dal kernel, il quale si occuperà anche di soddisfare i requisiti di flessibilità e sicurezza (che prima erano gestiti dal hypervisor).

Linux dispone **control groups** e **namespaces** proprio per trattare l'assegnamento delle risorse e l'isolamento dei programmi in esecuzione su ogni container.

### Control groups
I **control groups (cgroups)** gestiscono l'utilizzo delle risorse di calcolo da parte di un gruppo di processi.
>Possono limitare le risorse assegnate ai processi.

In Linux i cgroups si differenziano in base al **resource controller (subsystem)** a cui sono associati (i.e. quali risorse gestiscono).

I cgroup sono organizzati in modo gerarchico in una **struttura ad albero**, dove ogni **nodo** rappresenta un gruppo che va a definire delle regole per le risorse ad esso associate.

È possibile interagire con i cgroup tramite il **filesystem virtuale** `/sys`, quelli attualmente in uso risiedono in `/sys/fs/cgroup`.

Quando un container è configurato con un limite su delle risorse, docker crea i corrispondenti cgroups in `/sys/fs/cgroup` ed aggiunge automaticamente i pid dei processi in esecuzione nel container.

### Namespaces
Un processo in esecuzione su un container non deve poter accedere direttamente alla macchina ospitante o ad altri container, per questo esistono i **namespaces** i quali astraggono le risorse offerte dal kernel.

Quando un processo fa parte di un namespace, potrà <u>accedere soltanto alle risorse presenti nel namespace stesso</u>.

Per ciascun container in esecuzione, docker crea un opportuno namespace a cui associare i processi in esecuzione nel container, creando di fatto delle **sandbox**.

>[!Info] Container Linux su kernel Windows
>Non è possibile eseguire container Linux sul kernel Windows dato che non si virtualizza il sistema operativo ospite, in questi casi docker crea una VM Linux in esecuzione su HyperV.

### Immagini e repository
Nel caso in cui una immagine non fosse installata localmente, docker la cercherà in automatico nelle sue repository.

```bash
# esegue un container sfruttando un'immagine specificata
docker run <image>

# mostra le immagini scaricate
docker images
```

Docker di default scaricherà dalla repository la versione più recente, identificata tramite una stringa detta **tag**, la quale sarà uguale a `latest`.
>Se la repository non possiede `latest` darà un errore, è consigliabile riferirsi alle immagini con `repository:tag`.

Le immagini possiedono dei **layer** (immutabili) i quali contribuiscono alla definizione del file system del container.

### I container
Essendo un'immagine composta da layer immutabili, consente la condivisione di layer comuni.

Quando docker crea un container di fatto solo uno è un **layer scrivibile**, detto **layer container**, gli altri sono **layer immagine**.
>Il layer container viene distrutto ad ogni spegnimento.

Per memorizzare dei dati generati nel container è necessario ricorrere all'utilizzo di un **data volume**, il quale crea un <u>ponte tra il filesystem del container e quello del sistema operativo sottostante</u>.
```bash
docker run -it -v /home/m3nny/documentation:/docs ubuntu /bin/bash
```

- Tramite `-v` creiamo un container con una nuova directory `/docs` la quale riflette i contenuti di `/home/m3nny/documentation` del sistema ospitante, è possibile modificare i contenuti della cartella dall'interno del container.
- Tramite `-it` ci si collega in modalità interattiva ad un container.

I container sono isolati anche a livello di rete.

Supponiamo di voler eseguire un web server apache (`docker run httpd:latest`) e di voler ottenere l'**indirizzo ip del container**:
- In Linux è lo stesso della macchina che ospita docker
- In Windows, essendo docker ospitato su una VM con dentro Linux, è necessario utilizzare il comando `docker-machine ip` per ottenere l'ip corretto

Tuttavia essendo che i container blindano tutto ciò che è al loro interno, non è possibile collegarsi tramite browser al web server, per cui ci sono due soluzioni:
- Mappare la porta 80 del container su una della macchina ospitante
```bash
# -d serve per eseguire il container in background
docker run -d -p 8088:80 httpd:2.6
```

- Utilizzare un web server (e.g. nginx) installato sulla macchina ospitante con funzione di proxy

## Dockerfile
È possibile descrivere le immagini di docker tramite **Dockerfile**, il quale possiede un proprio linguaggio detto **Domain-Specific Language (DSL)**, vediamo ora le clausole più importanti.

**FROM**: non può mancare, specifica un'immagine di base da cui partire per derivare quella personalizzata.
```bash
FROM <immagine>:<tag>
```

**ENV**: permette di impostare variabili di ambiente per tutto il contesto di esecuzione di un Dockerfile.
```bash
ENV <chiave>="valore"
```

**RUN**: esegue dei comandi all'interno dell'immagine che andremo a generare, questa clausole ogni volta che viene incontrata fa generare un nuovo layer immutabile, per cui i comandi correlati vanno concatenati (e.g. `&&`), ad esempio utilizzare questa clausola due volte per eseguire `apt update` e `apt install` separatamente potrebbe far fallire il secondo comando nel caso un pacchetto non fosse disponibile (quando in realtà lo è nelle repository aggiornate).
```bash
RUN <comando> <parametri>
```

**ADD/COPY**: producono entrambe lo stesso risultato, ovvero montare sul filesystem dell'immagine dei file presenti nel sistema ospitante, utilizza solo path relativi per `<src>`.
```bash
ADD <src> <dst>
COPY <src> <dst>
```

**ENTRYPOINT**: permette di eseguire un comando all'interno del container al suo avvio, a differenza di RUN che agisce sull'immagine, questa clausola agisce sul container (non crea un nuovo layer), solitamente lo si usa per far partire un daemon all'avvio.
```bash
ENTRYPOINT <comando> <parametri>
```

**CMD**: è possibile specificare solo una clausola di questo tipo, se ne vengono specificate di più verrà presa in considerazione l'ultima, il suo comportamento cambia in base alla presenza o meno dell'istruzione ENTRYPOINT:
- Non è presente ENTRYPOINT: ha lo stesso comportamento di ENTRYPOINT, ma il comando può essere sovrascritto all'avvio del container `docker run <image> <comando>`
- È presente ENTRYPOINT: fornisce dei parametri per il comando definito dall'ENTRYPOINT, in questo caso non è più sovrascrivibile a meno che non si specifichi la flag `entrypoint` quando si avvia un container
```bash
# ENTRYPOINT non presente
CMD <comando> <parametri>

# ENTRYPOINT presente
CMD ["parametro_1", "parametro_n"]
```

**WORKDIR**: specifica la directory all'interno del container su cui avranno effetto tutte le successive istruzioni, se non è specificata è di default `/`.
```bash
WORKDIR /path/to/directory
```

**LABEL**: aggiunge metadati alle immagini, come RUN crea layer aggiuntivi.
```bash
LABEL VERSION="1.0.0" MAINTAINER="user"
```

**EXPOSE**: richiede a docker di effettuare il forwarding della porta specificata durante l'avvio dell'immagine, durante l'avvio del container invece è possibile esporre le porte esposte tramite la flag `-p`.
```bash
EXPOSE <porta_1> <porta_n>
```

**VOLUME**: espone parti del filesystem del container, le quali possono essere utilizzate per mappare un path locale ad uno del container all'avvio.
```bash
VOLUME ["path"]
```

Esempio completo:
```bash
FROM ubuntu:latest
ENV TO_BE_INSTALLED="vim"
RUN apt_install $TO_BE_INSTALLED
COPY *.txt /docs
ENTRYPOINT du
CMD ["-hs"]
WORKDIR /usr
LABEL VERSION="1.0.0" MAINTAINER="user"
EXPOSE 80 443
VOLUME ["/var/www"]
```

### Creazione delle immagini
La sintassi per costruire immagini partendo da un Dockerfile è:
```bash
docker build <opzioni> <build context>

# esempio
# -t assegna un nome all'immagine che si sta creando
docker build -t webserver:v1 .
```

`<build_context>` è necessario in quanto viene usato da alcuni comandi come `ADD/COPY` che potrebbero sfruttare indirizzi relativi.

Eseguiremo poi l'immagine come:
```bash
# -P espone tutte le porte definite nel Dockerfile
docker run -d --name webserver -P webserver

# -p per esporre singolarmente
docker run -d --name webserver -p 8088:80 webserver
```

## Compose
Nel caso fosse necessario creare applicazioni che utilizzano più container, è possibile utilizzare `docker compose` specificando un file yaml.
```bash
version: "3.8"
services:
	web:
	build: .
	ports:
		- "5000:5000"
	volumes:
		- .:/code
		- logvolume01:/var/log
	links:
		- redis
	redis:
		image: redis
volumes:
	logvolume01: {}
```

Per avviare ed eseguire l'intera applicazione in background si utilizza `docker compose up -d` all'interno di una directory contenente il file `docker-compose.yml` oppure specificando il file di configurazione tramite `-f`.

#### Gestire i container
Di seguito alcuni comandi utili per docker.
```bash
# ritorna le immagini contenenti <immagini> dalle repo ufficiali
docker search <immagine>

# recupera un immagine dalle repository ufficiali
docker pull <immagine>

# container in esecuzione
docker ps

# container presenti nel sistema
docker ps -a

# avvia un container utilizzando il suo id o nome
docker run <id/nome>

# ferma un container utilizzando il suo id o nome
docker stop <id/nome>

# cancella un container utilizzando il suo id o nome
docker rm <id/nome>
```

### Portainer
Portainer permette di amministrare container tramite un'interfaccia.

Inoltre consente di visualizzare le statistiche in tempo reale riguardo alle risorse fornite da cpu e memoria oppure verificare le attività di rete e dei processi all'interno di ciascun container.

Possiede anche un sistema di **template** per la messa in produzione di applicazioni e piattaforme comuni (e.g. MySQL).
