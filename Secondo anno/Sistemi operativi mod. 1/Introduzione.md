Quando parliamo di **sistema operativo** parliamo di _software che controlla l'hardware_, ovvero un gestore di risorse, dove ogni programma richiede uno _spazio_ ed un _tempo_ in cui allocare risorse.

Interfacciandosi <u>verso l'alto</u>, l'utente vede una macchina astratta, mentre quando il _S.O._ si interfaccia <u>verso il basso</u> ci sono le risorse, le quali devono essere gestite al meglio.

Prevede due **modalità di esecuzione** per il processore:
- **User mode**: per eseguire le applicazioni utente
- **Kernel mode**: è la modalità in cui viene eseguito il SO (prevalentemente)

---
## Storia

### I gen. (1945 - 1955)
Non esistono SO, la programmazione avviene in linguaggio macchina o cablando circuiti.
### II gen. (1955 - 1965)
Nasce assembly e fortran assieme alle schede perforate, in questo periodo con la **monoprogrammazione** è possibile eseguire un _job_ per volta.

Con i primi SO **batch** potevano essere eseguiti dei job consecutivamente senza ulteriore intervento.

La memoria conteneva sempre il SO ed un eventuale compilatore il quale veniva poi sostituito dal programma in esecuzione dopo aver finito di compilare.
### III gen. (1965 - 1980)
Nasce la _multiprogrammazione_ consentendo di gestire una <u>pool di job</u>, ciò significa che un job può usare la CPU mentre altri job usano altre risorse.
Per questo nascono anche:
- **Spooling**: cambio di job durante operazioni di I/O da parte dell'utente
- **Scheduling**: basato su un sistema di divisione del tempo in quanti chiamato _time sharing_ dove ogni job ha un tempo limite per essere eseguito prima di passare al prossimo job 

Compaiono _mainframe_ e _minicomputer_ assieme a linguaggi di alto livello come _C_, oltre ai primi terminali interattivi e l'introduzione della [[Mapping#Principio di funzionamento|memoria virtuale]].
Nascono inoltre i primi sistemi **real time** dove una risposta è data entro un più o meno _breve_ lasso di tempo.

Viene stabilito lo standard **POSIX** per rendere compatibili varie versioni di shell per le chiamate di sistema.

Comincia lo sviluppo di internet (TCP/IP).
### IV gen. (1980 - oggi)
Nascono **personal computer** e **workstation** assieme alle prime _GUI_ e si diffonde il modello **client/server** il quale poi porta a **sistemi paralleli** (con più unità di elaborazione strettamente legate) e **sistemi distribuiti** (diverse unità di elaborazione connesse tra loro) i quali usano linguaggi sempre più astratti e che supportano il _multithreading_ e _oggetti_.

Nasce il **World Wide Web**.