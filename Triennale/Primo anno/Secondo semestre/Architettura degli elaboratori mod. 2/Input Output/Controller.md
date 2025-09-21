Per effettuare trasferimenti di dati occorre comunicare con il **controller** di ciascun dispositivo, attraverso il quale è possibile dare comandi, leggere e scrivere il dispositivo in questione.

Il controller in genere contiene dei registri, tra cui:
- **Command**: invia comandi al controller
- **Status**: per conoscere lo stato del dispositivo
- **Data write**: per scrivere nel device
- **Data read**: per leggere dal device

**Comunicare con il controller** significa leggere e scrivere i registri del controller:
1. <u>Memory mapped I/O</u>: i registri sono visti come locazioni speciali di memoria, è la Memory Management Unit ad indirizzare le richieste al dispositivo (non la RAM)
2. <u>Istruzioni speciali</u>: l'ISA della CPU comprende istruzioni speciali per leggere i registri di determinati controller

---
## Gestione dell'IO
Esistono varie tecniche per gestire le operazioni di IO, le quali consistono nel: verificare lo stato del dispositivo, dare comandi, leggere e scrivere nei registri.

### Programmed IO (Polling)
La <u>CPU controlla periodicamente lo stato del dispositivo</u> per vedere se deve trasferire dati, nel caso dovesse trasferire dati allora la CPU li trasferisce alla RAM, altrimenti continua a controllare lo stato.

**Vantaggi**:
- Utile in applicazioni real-time, dato che è molto probabile che il dispositivo debba trasferire dati molto spesso
- Utile se si trasferisce spesso (real-time, ...)
**Svantaggi**:
- La CPU spreca tempo a controllare sempre lo stato del dispositivo
- La CPU spreca tempo per trasferire dati dal dispositivo alla RAM

### Interrupt-driven IO
In questo caso <u>è il dispositivo a generare degli interrupt quando vuole comunicare</u>, quindi la CPU salta ad un indirizzo di memoria contenente l'interrupt handler:
- Salva lo stato del programma attualmente in esecuzione
- Individua il dispositivo che che ha generato l'istruzione e comunica con esso

**Vantaggi**:
- Utile se il dispositivo comunica raramente o ad intervalli non predicibili
- Non serve impostare la frequenza di polling
**Svantaggi**:
- Overhead per la gestione dell'interrupt alto
- Dispendioso se il dispositivo comunica frequentemente

---
## Direct Memory Access (DMA)
Usiamo questo **controller** per evitare di usare la CPU come ponte tra le richieste dei dispositivi.
La <u>CPU si limita a fornire al DMA informazioni su quanti dati leggere/scrivere e gli indirizzi coinvolti</u>, il trasferimento avverrà poi tra DMA-RAM, notificando la CPU tramite interrupt al termine del trasferimento.
