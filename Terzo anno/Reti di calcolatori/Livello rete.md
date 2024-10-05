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

Successivamente ogni router procederà come segue all'arrivo di un DV da parte di un vicino:
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

