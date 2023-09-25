Distinguiamo due tipi di sistemi per gestire le informazioni:
- **Sistema informatico**: tecnologie informatiche a supporto delle attività di una organizzazione
- **Sistema informativo**: combinazione di risorse e procedure che agiscono con delle informazioni anche provenienti dal _sistema informatico_

Nel primo abbiamo **dati** grezzi, mentre nel secondo assumono un significato.

A partire dagli anni '60 si nota che molte operazioni ripetitive possono cominciare ad essere automatizzate, per questo negli anni '70 nascono i primi **DBMS** (Data Base Management System) i quali garantiscono la disponibilità dei dati ed un accesso efficiente ad essi.

## Classificazione dei sistemi informatici
- **Operativi**: i dati sono organizzati in DB con schemi rigidi e aggiornati in tempo reale inoltre su di essi possono anche essere eseguite delle transazioni (OnLine Transaction Processing)
- **Direzionali**: i dati sono estratti da varie fonti e possono usare schemi flessibili, parliamo quindi di _data warehouse_, i quali solitamente vengono aggiornati periodicamente tramite processi di ETL (Extract Transform Load)

Sui **data warehouse** possiamo eseguire operazioni complesse **OLAP** (OnLine Analytical Processing) su molti dati aggregati anche storici le quali consistono solo in una **lettura** in chiave diversa dei dati dispersi che già avevamo.

---
### DB e DBMS
Un **DB** è una raccolta di dati permanenti suddivisi in due categorie:
- **Metadati**: definiscono lo _schema_ del DB (struttura dati, vincoli, permessi...)
- **Dati**: rappresentazioni di certi fatti conformi allo schema

I dati sono **molti** e **permanenti** (rimossi solo da operazioni indipendenti dalle applicazioni) organizzati in **insiemi omogenei** fra i quali sono definite **relazioni**, e sono utilizzabili da più utenti contemporaneamente.

Un **DBMS** è un sistema che offre linguaggi/strumenti per **definire lo schema** e **scegliere le strutture dati**, dovrà poi **memorizzare** i dati rispettando i vincoli definiti nello schema.
Inoltre può **recuperare e modificare** tramite query.

### Funzionalità dei DBMS
- **DDL (Data Definition Language)**: per la definizione della struttura dei dati, delle regole di integrità e dei privilegi degli utenti (**CREATE**, **ALTER**, **DROP**)
- **DML (Data Manipulation Language)**: per leggere, inserire, modificare e cancellare dei dati (**SELECT**, **INSERT**, **UPDATE**, **DELETE**)

#### DDL
Esistono tre livelli principali:
- **Logico** (_schema logico_): descrive la struttura degli insiemi di dati e delle relazioni tra essi senza riferimento alla loro organizzazione fisica in memoria
- **Fisico** (_schema fisico_): descrive come vanno organizzati fisicamente i dati in memoria, assieme a strutture dati ausiliare (e.g. indici)
- **Vista logica** (_schema esterno/vista_): descrive come deve apparire la struttura del DB ad una certa applicazione, il DB in questo caso è creato attraverso una query

Deve esserci inoltre **indipendenza fisica e logica** ovvero i programmi non devono essere riscritti a causa di una modifica allo schema fisico o logico.
#### DML
In base al tipo di utente che si interfaccia con il DB, è possibile manipolare i dati tramite:
- Interfaccia
- Linguaggio SQL

---
### Controllo dei dati
- **Integrità**: mantenimento delle proprietà dello schema tramite _vincoli di integrità_
- **Sicurezza**: protezione dei dati da utenti senza permessi necessari, nel caso statistico per proteggere i dati bisogna usare anche la _key anonymity_ ovvero solo se $k$ utenti hanno lo stesso dato uguale allora i dati di quei utenti possono essere visualizzati e analizzati (questo previene di risalire da un utente specifico incrociando le poche occorrenze di dati)
- **Affidabilità** protezione dei dati da accessi concorrenti e malfunzionamenti

#### Transazioni
Una **transazione** è una sequenza di azioni di lettura e scrittura in memoria permanente e di elaborazioni di dati in memoria temporanea al fine di mantenere la consistenza dei dati grazie alle proprietà **ACID**:
- **A** (_Atomicità_): le modifiche in memoria permanente sono eseguite in una volta, le transazioni terminate prematuramente non hanno effetti reali
- **C** (_Consistenza_): il database deve rispettare l'_integrità referenziale_ prima e dopo la transazione
- **I** (_Isolamento_): più transazioni devono poter avvenire senza interferenze tra loro
- **D** (_Durabilità_): il database dev'essere salvato sul disco alla fine della transazione così che i dati non vengano persi in caso di fallimento completo del sistema
