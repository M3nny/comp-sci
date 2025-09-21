I sistemi di I/O sono usati per collegare il computer alle periferiche.
Questo collegamento è solitamente realizzato mediante un **bus**, il quale implementa un canale di comunicazione condiviso da più sottosistemi.

**Vantaggi**:
- Versatilità: facile aggiungere/ rimuovere dispositivi.
- Basso costo: un collegamento per più esigenze.
**Svantaggi**:
- Può rappresentare un bottleneck in quanto limita la massima frequenza di I/O.

### Esempi di bus
- **System bus**: Connette CPU e RAM, sono corti e molto veloci.
- **Backplane**: connettono dispositivi diversi con bande diverse, mediamente lunghi e veloci (PCIe).
- **I/O**: gestisce catene di dischi, molto lunghi ma lenti.

---
## Bus sincrono
Rappresenta una **linea di clock condivisa** tra tutti gli elementi connessi ad esso, <u>il clock condiviso viene sfruttato per arbitrare gli accessi al bus</u>.
- Limitato a bus corti proprietari come CPU<->RAM
- Con bus lunghi si avrebbe il fenomeno del **clock skew** (disallineamento del segnale di clock)

## Bus asincrono
Il **clock non è condiviso** tra gli elementi connessi, in questo modo permette la <u>comunicazione tra periferiche con velocità diverse</u>.
- Utilizzato da bus standard (USB, PCIe, ...)

### Trasferimento di dati su bus asincrono
Per effettuare una transazione di IO richiede un **handshake** iniziale (comporta un certo overhead).
Dato che due dispositivi avranno il proprio clock indipendente occorrono **3 linee**: Req, Ack, Data (all'inizio sono tutte not asserted).
![[Bus asincrono.png|500]]
1. A mette i dati da trasferire su DATA e imposta Req=1
2. B si accorge che Req=1 e legge da DATA, quando ha finito di leggere imposta Ack=1
3. A si accorge che Ack=1 e sa che la lettura è terminata, imposta Req=DATA=0
4. B si accorge che Req=0 e imposta Ack=0

---
## Arbitraggio
Se il bus è condiviso da 3+ dispositivi, occorre un arbitraggio per evitare conflitti.
Gli attori che possono iniziare una transazione sul bus sono chiamati **master** del bus, i dispositivi che competono per l'uso del bus hanno <u>linee aggiuntive</u> che li collegano all'**arbitro** del bus.

### Daisy chain
![[Daisy chain.png|500]]
Quando un device deve trasmettere imposta request=1, di conseguenza l'arbitro imposta grant=1.
<u>Non sapendo però da chi arriva la richiesta (dato che la linea è condivisa), il device 1 può decidere se prendere lui il controllo del bus</u> (not fair) oppure propagare grant al device successivo.
In ogni caso quando un device riceve grant può iniziare a trasmettere, al termine delle operazioni viene impostato release=1 e l'arbitro imposta grant=0.

**Vantaggio**:
- <u>Semplice</u> da implementare, con pochi segnali di controllo
**Svantaggio**:
- <u>Non è fair</u>, un dispotivo ad alta priorità può causare starvation degli altri dispositivi a bassa priorità
