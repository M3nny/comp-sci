Esistono **7 temi fondamentali** riguardanti la sicurezza di un sistema:
- **Disponibilità** dei dati
- **Autenticità** dei dati
- **Integrità** dei dati
- **Confidenzialità** dei dati
- **Controllo degli accessi**
- **Non ripudio** (impossibilità di negare la paternità di una dichiarazione)
- **Anonimità**

#### Disponibilità
Un servizio deve sempre essere raggiungibile.
La disponibilità è violata se si è vittime di un attacco **DoS (Denial of Service)**, inoltre è la cosa più difficile da assicurare a causa di limiti fisici dei dispositivi su cui si basa il servizio.
>Realizzata tramite un **buon design della rete** ed una corretta analisi dei rischi.

#### Autenticità
Solitamente l'autenticazione viene divisa in:
- **Data origin**: chi riceve l'informazione deve essere sicuro che sia stato il mittente effettivo a mandare i dati
- **Peer entity**: chi riceve l'informazione deve essere sicuro della sorgente effettiva da cui riceve i dati (i.e. router al posto di un host locale)
>Realizzata tramite **firme digitali**.

#### Integrità
I dati devono raggiungere la destinazione senza essere soggetti a modifiche.
>Realizzata tramite **meccanismi di hashing**.

#### Confidenzialità
I dati scambiati devono rimanere riservati tra le parti che partecipano allo scambio.
>Realizzata tramite **meccanismi di crittografia**.

#### Controllo degli accessi
L'accesso ad un servizio deve essere ristretto alle sole entità autorizzate.
Perdere il controllo degli accessi comporta essere utilizzati come testa di ponte per attacchi contro terzi.

#### Non ripudio
La non ripudiabilità previene sia al mittente e sia al destinatario la possibilità di negare un messaggio trasmesso.
Quando un messaggio è inviato, il destinatario può provare che il presunto mittente abbia effettivamente inviato il messaggio, discorso analogo per il mittente.

#### Anonimità
La capacità di utilizzare un sistema senza che il sistema sia in grado di identificare il mittente.

L'anonimità non è un servizio canonico offerto dalla sicurezza, tuttavia è sempre più importante, essa può essere un'arma o  una salvezza.
Qualche volta è positiva per chi offre servizi in quanto meno si sa dei propri utenti, meno domande si possono ricevere da terzi.
>Contraddice altri servizi (e.g. controllo degli accessi).

### Componenti del modello
L'astrazione che solitamente si usa per rappresentare un modello di rete è la seguente:
![[Model components.png]]

**Alice** vuole comunicare un messaggio a **Bob** attraverso il canale **Eve** il quale è identificato come l'attore malevolo, il quale può mettere mani nel canale di comunicazione.
>Questo non rappresenta sempre un caso reale però se un sistema è resistente a questo tipo di attacchi lo sarà anche ad altri.

Le **trasformazioni** che avvengono in _Alice_ e _Bob_ si assume che siano meccanismi robusti di crittografia.

Il **Trusted third party** è un'entità di cui _Alice_ e _Bob_ si fidano, inoltre anche _Eve_ ci può interagire.

>[!Attention]
>C'è sempre un **trade-off** nell'aumentare la sicurezza, ovvero rendere il sistema meno usabile, per questo è importante identificare i servizi critici e da che attacchi proteggerli.

## Crittografia
Un **algoritmo crittografico** è una sequenza di operazioni matematiche applicate ad un messaggio.
>Alcuni protocolli combinano **funzioni crittografiche** per fornire sicurezza ai servizi.

### Funzioni hash
Una **funzione hash** è una funzione **unidirezionale** $H$ che dopo essere stata applicata a dei dati genera un **digest**, ovvero una stringa con **dimensione fissa**.

Gli hash sono usati per ottenere l'**integrità dei dati**, ad esempio:
Alice manda un messaggio $M$ a Bob assieme al suo hash $H(M)=D$, Bob una volta ricevuto il messaggio ricalcola $H(M)=D'$, se $D=D'$ il messaggio non è stato modificato nel tragitto, quindi si ottiene l'_integrità_.

- La computazione degli hash digest deve avvenire velocemente.
- La dimensione del **dominio** della funzione di hash è molto più grande del **codominio**.

**Non invertibilità**
Dato un digest $D$, trovare $X$ per cui $H(X)=D$ deve essere _impossibile da calcolare_.

**Resistenza alle collisioni debole**
Dato $X$, trovare $Y$ per cui $H(X)=H(Y)$ deve essere _impossibile da calcolare_.
Ogni hash deve essere molto diverso da un altro, anche se il documento originale cambia di un solo bit, in questo modo si evitano attacchi _brute force_ sulla distanza dei digest.

**Resistenza alle collisioni forte**
Trovare $X$ e $Y$ per cui $H(X)=H(Y)$ deve essere _impossibile da calcolare_,
anche se ogni digest di dimensione finita implica una <u>probabilità di collisione non nulla</u>.

>[!Info] Impossibile da calcolare
>La crittografia si basa spesso su qualcosa che è "impossibile".
>Molto spesso non significa che è realmente impossibile, ma significa che la potenza di calcolo disponibile al giorno d'oggi non lo consente, ed è quindi altamente improbabile che accada.
>
>Un problema è detto **computazionalmente impossibile** se non esiste alcun algoritmo con [[Teoria della NP completezza|complessità polinomiale]] in grado di risolvere tale problema. 

