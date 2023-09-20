Distinguiamo due tipi di sistemi per gestire le informazioni:
- **Sistema informatico**: tecnologie informatiche a supporto delle attività di una organizzazione
- **Sistema informativo**: combinazione di risorse e procedure che agiscono con delle informazioni anche provenienti dal _sistema informatico_

Nel primo abbiamo **dati** grezzi, mentre nel secondo assumono un significato.

A partire dagli anni '60 si nota che molte operazioni ripetitive possono cominciare ad essere automatizzate, per questo negli anni '70 nascono i primi **DBMS** (Data Base Management System) i quali garantiscono la disponibilità dei dati ed un accesso efficiente ad essi.

## Classificazione dei sistemi informatici
- **Operativi**: i dati sono organizzati in DB con schemi rigidi e aggiornati in tempo reale inoltre su di essi possono anche essere eseguite delle transazioni (OnLine Transaction Processing)
- **Direzionali**: i dati sono estratti da varie fonti e possono usare schemi flessibili, parliamo quindi di _data warehouse_, i quali solitamente vengono aggiornati periodicamente tramite processi di ETL (Extract Transform Load)

Sui **data warehouse** possiamo eseguire operazioni complesse **OLAP** (OnLine Analytical Processing) su molti dati aggregati anche storici le quali consistono solo in una **lettura** in chiave diversa dei dati dispersi che già avevamo.