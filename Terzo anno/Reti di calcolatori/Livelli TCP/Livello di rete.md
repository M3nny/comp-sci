Il datalink si prende cura della connettività fisica tra host, mentre il **livello di rete** si prende cura di trasmettere l'informazione a host che non fanno parte della stessa rete attraverso dei router.

Si assume che il datalink layer sia _quasi affidabile_, quindi la perdita di pacchetti può succedere, ma ci si aspetta che non sia frequente.
>La SDU utilizzata a questo livello sono i **pacchetti**.

## Datagram-oriented Network Layer
Ogni host è identificato da un **indirizzo di rete**, per mandare l'informazione ad un host remoto verrà creato un **pacchetto** contenente:
- L'indirizzo di rete del destinatario
- L'indirizzo di rete del mittente
- L'informazione da inoltrare

I router utilizzano un forwarding di tipo **hop-by-hop** dove se un pacchetto non è destinato ad un router, esso lo inoltrerà al prossimo router tramite una sua decisione, e questo si ripeterà finchè l'informazione non arriva al destinatario.

Tale decisione è fatta attraverso una **forwarding table**, ovvero una struttura dati che mappa indirizzo di destinazione ad una interfaccia del router.

Tra gli errori possibili causati da forwarding table troviamo:
- **Black holes** nel caso un router non sappia verso chi inoltrare il pacchetto ricevuto scarterà il pacchetto
- **Routing loops** nel caso una forwarding table sia mal formata è possibile che un pacchetto venga continuamente rimbalzato tra una serie di hop

Un router è diviso in due parti:
- **Data Plane**: eseguirà il forwarding dei pacchetti secondo la forwarding table
- **Control Plane**: si prende cura di creare le forwarding table

Un modo per gestire il _control plane_ è creando le forwarding table **manualmente**, tuttavia non è fattibile per reti grandi che possono anche cambiare.
I router per gestire tale tabelle dovranno scambiarsi informazioni tra di loro, in una rete locale potrebbe esserci un **controller** il quale configura tutte le tabelle e le aggiusta quando qualcosa cambia, ma per internet bisogna utilizzare un approccio **distribuito**.

### Indirizzamento e eterogeneità
Abbiamo detto che le forwarding table contengono gli indirizzo di destinazione verso cui inoltrare i pacchetti, in uno **schema piatto** vengono memorizzati gli indirizzo dell'hardware, per quanto semplice da impostare le tabelle si ritroveranno ad avere miliardi di righe.

In uno **schema gerarchico** gli indirizzi sono raggruppati in blocchi, quindi non è necessario sapere l'indirizzo di tutti gli host, ma solo di alcuni blocchi, tuttavia quando un host cambia rete è necessario assegnargli automaticamente un nuovo indirizzo.

Non possiamo assumere che il datalink sia uguale per tutti i link a causa dell'**eterogeneità** della rete.
![[Eterogeneità di rete.png]]

Immaginiamo che $A$ mandi un pacchetto incapsulato in un frame da $1000$ Byte destinato a $B$ attraverso $R1$. 
In questo caso $R1$ può fare tre cose:
1. **Scartare** il pacchetto e notificare $A$ (non ottimale)
2. **Frammentare** il pacchetto e farlo **riassemblare** dal **next hop** (crea delay a causa del possibile riassemblamento ad ogni hop)
3. **Frammentare** il pacchetto e farlo **riassemblare** alla **destinazione** (migliore opzione)

## Algoritmi di routing
Un algoritmo utilizzato agli albori di internet era l'**hot potato**, immaginiamo che la rete si sia appena "accesa" con le tabelle di forwarding vuote e che l'host $A$ voglia mandare un pacchetto a $B$:
![[Hot potato.png]]

1. $A$ manda il pacchetto al suo unico link
2. $R1$ quando riceve il pacchetto capisce che $A$ è raggiungibile dalla sua interfaccia Ovest
3. $R1$ non essendo la destinazione esegue un **broadcast** su tutte le sue interfacce escludendo quella da cui è arrivato il pacchetto
4. Il pacchetto prima o poi arriverà anche all'host $C$, esso lo scarterà in quanto non è indirizzato a lui
5. Alla fine quando il pacchetto sarà arrivato a $B$, tutti i router avranno una riga corrispettiva all'host $A$, la prossima volta che qualcuno vorrà comunicare con $A$ non dovrà eseguire un broadcast

Funziona bene in reti piccole, tuttavia se dovessero esserci dei **cicli** il destinatario riceverebbe all'**infinito** il pacchetto del mittente, inoltre ci sarebbe tanto traffico inutile.

L'algoritmo _hot potato_ non necessità di un _control plane_, ma nel mondo reale servono **algoritmi** più complessi, i quali vengono poi implementati dai **protocolli di routing** in esecuzione dai **deamon** in background.

Lo scopo di un _control plane_ o di un _protocollo di routing_ è quello di **costruire una routing table**.
Una _routing table_ $R$ può essere vista come una struttura dati che per ogni indirizzo di destinazione $d$ (noto) memorizza i seguenti attributi:
- `R[d].link`: il link di uscita usato per inoltrare i pacchetti verso la destinazione `d`
- `R[d].cost`: somma delle metriche usate per stabilire il [[Secondo anno/Algoritmi e strutture dati/Mod. 1/Cammini minimi/Introduzione|cammino minimo]]
- `R[d].time`: timestamp dell'ultimo pacchetto di controllo che trasportava informazioni riguardo a `d`

Una **routing table** è un concetto più astratto di una **forwarding table**, infatti in un router possono esiste varie routing table configurate automaticamente o meno, le quali vengono poi combinate in una singola forwarding table utilizzata dal router.

### Distance vector routing
Un algoritmo di **distance vector routing** implementa l'algoritmo di [[Bellman-Ford]] in modo **distribuito**.

Assumiamo che ogni link abbia un **costo** il quale rappresenta una penalità per passare attraverso tale link, e ogni DV router inizializza la tabella di routing $R$ con una entry per il suo indirizzo con distanza $0$.

Periodicamente il router **invierà** la proprio routing table (distance vector) ai suoi nodi vicini in un ordine qualsiasi:
```python
# Ogni N secondi
v = []
for d in R[]:
	v.add(Pair(d, R[d].cost))
for i in interfaces:
	send(v, i)
```

Successivamente ogni router procederà come segue al **ricevimento** di un DV da parte di un vicino:
```python
# V: vettore ricevuto
# l: link attraverso il quale il vettore è ricevuto
def received(V, l):
	# ricevuto vettore dal link l
	for d in V[]:
		if not (d in R[]):
			# nuova route
			R[d].link = l
			R[d].cost = V[d].cost + l.cost
			R[d].time = now()
		else:
			# aggiorna il cammino minimo se la route esiste di già
			if (V[d].cost + l.cost) < R[d].cost or R[d].link == l:
				R[d].link = l
				R[d].cost = V[d].cost + l.cost
				R[d].time = now()
```

Ci possono essere diverse configurazioni in base all'ordine dei router, tuttavia avranno tutte costo minimo.

Immaginando di avere un costo pari a $1$ per ogni link, questa è la situazione dopo che $A$ ha inoltrato il suo DV a $B$ e $D$, nella seguente immagine $D$ sta inoltrando il suo DV ai suoi vicini:
![[DV routing.png]]

La **convergenza** avverrà quando ogni routing table possiede il costo minimo per ogni router nella rete:
![[Convergenza DV.png]]

Come tutti i router inoltrano i propri DV ogni $N$ secondi, il timestamp di ogni route deve essere regolarmente aggiornato, quindi nessuna route deve avere un timestamp più vecchio di $N$ secondi.

#### Guasti
I router ogni $N$ secondi **controllano i timestamp** delle route, e se qualcuna è più vecchia di $3\cdot N$ secondi il suo costo viene **impostato a $\infty$**, dopo altri $3\cdot N$ secondi **la route viene rimossa** dalla routing table, questo tempo aggiuntivo prima della cancellazione è usato per informare i vicini che quella route non è più raggiungibile o eventualmente aggiustare il peso con uno più basso.
>$3$ è un valore arbitrario che dipende dai protocolli di rete, è basso perchè si assume che i link siano abbastanza affidabili.

Dopo che il link $A-B$ si rompe, le destinazioni che utilizzano quel link per effettuare un camino minimo vengono poste a $\infty$:
![[Guasto DV.png]]

---
## Count to infinity and poison reverse
Finora abbiamo considerato che tutti i pacchetti venissero consegnati senza problemi, assumiamo ora che il link $D-E$ si rompa, la rete ora è divisa in due, e $D$ è il primo ad accorgersene e quindi imposta il costo verso $B,C,E$ a $\infty$.

Supponiamo però che $A$ invii il suo $DV$ a $D$ prima che quest'ultimo possa informare dell'accaduto:
![[Count to infinity.png]]

Ora $D$ sa che può raggiungere gli altri nodi tramite $A$, ma non può sapere che $A$ passava attraverso $D$ per raggiungere gli altri nodi, così facendo continueranno a "rimbalzarsi" i $DV$ tra loro e aumenteranno ad ogni invio il costo delle destinazioni di $1$ (costo unitario scelto precedentemente), questo problema è definito come **count to infinity**.
>Può accadere in presenza di cicli (un link full-duplex è un ciclo) quando avviene un cambio della topologia della rete ed un pacchetto è perso.

Una soluzione banale potrebbe essere un **triggered update**, ovvero $D$ manda il suo $DV$ appena rileva che il link non funziona, ciò non funziona perchè il problema potrebbe verificarsi ancora:
- Per quanto veloce può essere comunque potrebbe ricevere un $DV$ da $A$ prima di riuscire ad inviare il suo $DV$
- Il pacchetto contenente il $DV$ potrebbe essere perso

Per evitare il problema di _count to infinity_ è possibile utilizzare un algoritmo chiamato **split horizon with poison reverse**, il quale modifica l'**invio** dei $DV$:
```python
# Ogni N secondi
for interface in interfaces
	v = Vector()
	for d in R[]:
		if R[d].link != interface:
			v.add(Pair(d, R[d].cost))
		else:
			v.add(Pair(d, ∞))
	send(v, interface)
```

In questo modo il mittente sta "avvelenando" la routing table del vicino dicendo che non possiede un cammino verso le destinazioni che dovrebbero essere raggiunte tramite esso.

Immaginando che $A$ utilizzi tale algoritmo, allora $D$ al ricevimento del $DV=[0,\infty,\infty,\infty,\infty]$ non aggiornerà la sua routing table in quanto avrà un costo maggiore, al prossimo intervallo di tempo $D$ inoltrerà il $DV$ corretto ad $A$ così da correggere la sua routing table.

Tuttavia il problema _count to infinity_ può ripresentarsi nel caso di un ciclo formato da $3$ o più router, un modo per evitarlo è **ignorare gli update** per un periodo di tempo dopo che una destinazione è stata impostata a $\infty$, così facendo ci si assicura che l'informazione del guasto raggiunga tutti i vicini senza preoccuparsi della perdita di pacchetti.
>Renderà la <u>convergenza molto lenta</u>.

---
## Link-State routing
Il **Link-State (LS) routing**, a differenza dei router basati su distance vector, il link-state routing consente ai router di <u>scambiarsi messaggi per capire l'intera topologia della rete</u>.

Una volta imparata la topologia è possibile computare la routing table utilizzando l'[[Dijkstra|algoritmo di Dijkstra]].

Ogni router ha un **indirizzo unico**, essi si scambiano messaggi $\text{HELLO}$ ogni $N$ secondi per capire quali sono i vicini, tale messaggio <u>contiene l'indirizzo del router</u>, ed un link è da **considerarsi guasto** se nessun messaggio $\text{HELLO}$ è stato ricevuto da un vicino per un periodo di $k\times N$ secondi (con $k$ costante).

Una volta che un router è a conoscenza dei suoi vicini distribuirà la sua **topologia locale** agli altri router, ogni router quindi costruisce un **Link-State Packet (LSP)** contenente:
- `LSP.Router`: indirizzo (univoco) del mittente
- `LSP.age`: età o tempo rimanente di vita del LSP
- `LSP.seq`: numero di sequenza (incrementale) del LSP
- `LSP.Links[]`: il quale contiene i link locali con campi:
	- `LSP.Links[i].Id`: indirizzo (univoco) del vicino
	- `LSP.Links[i].cost`: costo del link

I LSP devono essere **distribuiti in modo affidabile** prima di costruire una routing table, per farlo viene utilizzato un **algoritmo di flooding** per distribuire efficientemente i LSP ai router. 
Ogni router che implementa tale algoritmo possiede un **Link-State DataBase (LSDB)** contenente l'ultimo LSP ricevuto da ogni router.

Prima di inoltrare ai vicini un LSP viene controllato se esso è già presente nel LSDB utilizzando il numero di sequenza, nel caso non fosse presente il LSP viene inoltrato a tutti i vicini tranne al vicino mittente:
```python
# all'arrivo di un LSP al link l
if newer(LSP, LSDB(LSP.Router)):
	LSDB.add(LSP)
	for i in links:
		if i != l:
			send(LSP, i)
```

![[LSP.png]]

Dopo l'algoritmo di _flooding_:
![[LSP flooding.png|700]]

Nel caso di guasti al link dopo $k\times N$ secondi i router alle estremità del link rileveranno il guasto e aggiorneranno i link adiacenti, di conseguenza anche gli altri router tramite gli LSP aggiusteranno la topologia della rete.

>[!Attention]
>Se qualche messaggio viene perso la convergenza potrebbe non avvenire, è dunque necessario che l'algoritmo di flooding sia accompagnato da segnali di **ack** oppure che sia **periodico**.

In conclusione:
- LS routing converge più velocemente rispetto al DV routing
- LS routing ha bisogno di più risorse computazionali rispetto al DV routing (e.g. ad ogni cambiamento di topologia tutti i router devono ricomputare Dijkstra, infattibile in quanto non scalabile)

>Al livello di rete i pacchetti possono essere persi, corrotti, duplicati o ricevuti in disordine, per cui i livelli superiori devono tenerne conto.

