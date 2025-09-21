In questo punto si identificano le **informazioni** di cui si ha bisogno, si presta attenzione ai **bisogni del pubblico di riferimento** e si prende nota dei vari **vincoli** che esistono: sia riguardanti al contesto, sia riguardanti le tecnologie.

---
## Architettura dell'informazione
In questa fase definiamo come l'informazione è suddivisa nell'applicazione.

L'**informazione** si colloca tra **dati** e **conoscenza**, non esiste una singola risposta "giusta" in quanto essa è rappresentata tramite molti metodi differenti.
Con l'informazione dovremo:
- **Strutturarla**: determinare le relazioni tra i pezzi singoli di informazione
- **Organizzarla**: raggruppare i pezzi singoli di informazione in categorie così da far capire all'utente in che sezione dell'applicazione si trova
- **Labeling**: dare un nome alle categorie create

In base al tipo di informazione ricercata. il **pattern di ricerca** di un utente può variare, è quindi importante capire i bisogni di un utente e adattare il design.

Il modello **semplicistico** funziona come segue: l'utente fa una domanda e riceve la risposta esatta, ma ci sono problemi in questo modello in quanto:
- Le persone non sanno esattamente cosa vogliono
- La risposta o è parzialmente corretta o è completamente sbagliata
- Non si tiene conto di cosa succede mentre l'utente sta navigando l'applicazione
Questo modello è costruito sul **concetto errato** per cui trovare l'informazione è un problema diretto che può essere risolto con un semplice algoritmo.

#### Berry picking
Una persona quando cerca un'informazione su un sito web può imbattersi in queste situazioni:
- L'utente sta cercando la risposta esatta alla sua domanda specifica
- L'utente sta cercando più di una risposta corretta
- L'utente si sta informando su un argomento (e.g. ricerca per la tesi)
- L'utente pone un segnalibro sulla pagina trovata per poterla ritrovare facilmente

### Organizzare l'informazione
Organizzare le informazioni è complicato per svariati motivi:
- **Ambiguità**: le parole possono essere interpretate in modo diverso da quello previsto
- **Eterogeneità**: i siti sono composti da vari livelli di granularità di informazione, e non sono tutti organizzati allo stesso modo
- **Questione di prospettive**: la ricerca è condizionata anche dal modo di fare del creatore del sito (e.g. il modo in cui nomina gli elementi, come li dispone...)
- **Politiche interne**: bisogna prestare attenzione alle politiche interne dell'organizzazione

Uno **schema organizzativo** definisce le caratteristiche condivise degli elementi e ne influenza il loro **raggruppamento logico**.

Una **struttura organizzativa** definisce i tipi di relazione tra il contenuto degli elementi ed il loro **gruppo di appartenenza**.

## Schema organizzativo
- **Schema esatto** (o oggettivo):
	divide l'informazione in **sezioni ben definite** e suddivise, in questo modo è facile sapere dove si potrebbe trovare l'informazione **senza ambiguità**, questo <u>prevede che l'utente sappia il nome di quello che sta cercando</u>.
	**È facile** da progettare, mantenere e usare

- **Schema alfabetico**:
	usato principalmente per enciclopedie e dizionari, solitamente serve come punto di partenza per altri schemi organizzativi

- **Schema cronologico**:
	certi tipi di informazioni si prestano bene per questo tipo di schema, ad esempio calendari.
	Finchè si sa quando un evento è accaduto, questo schema è facile da progettare e da usare

- **Schema geografico**:
	facili da implementare e dritti al punto (e.g. maps)

Esistono poi **schemi ambigui** (o soggettivi) i quali suddividono l'informazione in categorie che non rispecchiano esattamente la loro definizione, potrebbe quindi essere difficile scegliere dove collocarla.
Tuttavia questo tipo di schemi sebbene più **difficili da progettare**, sono più **facili da navigare** in quanto non sempre l'utente sa cosa sta cercando.

L'utente infatti può imparare come sono disposti gli elementi per navigare il sito senza particolari conoscenze (**associative learning**).

- **Schema a "topic"**:
	l'organizzazione per materia è difficile, e sebbene si pensi che i gruppi siano fissi, essi rappresentano costrutti sociali che possono cambiare col tempo (e.g. giornali), è importante definire gli **argomenti coperti**

- **Schema orientato a task**:
	questo tipo di schema famoso in ambienti desktop, mobile e nel web in quanto vengono **raggruppati processi e funzioni**

- **Schemi rivolti ad un pubblico specifico**:
	nel caso l'applicazione sia rivolta a più di una audience specifica, ha senso creare più schemi differenti, questo tipo di schema viene definito **aperto** se un determinato pubblico può accedere ad uno schema non progettato per esso, **chiuso** altrimenti (e.g. senior - caregiver)

- **Schema metafora**:
	utilizza metafore per far relazionare quello che già conosce l'utente con il software nuovo, bisogna fare attenzione che l'audience colga le metafore

- **Schema ibrido**:
	finchè gli schemi sono presentati in modo separato, continueranno a suggerire un modello mentale all'utente

## Strutture organizzative
- **Sequenza**:
	l'informazione semplicemente è messa in sequenza, utile per siti educativi dove bisogna scorrere i materiali in ordine

- **Gerarchia**:
	siamo sempre stati abituati ad usare schemi gerarchici per tutto, per questo, lo schema in questione risulta essere **semplice da apprendere**.
	
	**Regole per lo sviluppo di una gerarchia**:
	- Ogni elemento deve avere al massimo un padre
	- Non deve essere troppo profonda in quanto bisognerebbe navigare attraverso molti livelli dell'applicazione, e non deve essere troppo piatta in quanto questo presenterebbe molte opzioni a schermo

- **Ipertesto**:
	l'ipertesto usato dai siti web è un modo **non lineare** per strutturare l'informazione, esso è rappresentato da nodi e link ad altri nodi, se progettato male potrebbe disorientare l'utente, per questo solitamente non sono mai la scelta primaria, ma è una **struttura complementare** ad un'altra (e.g. gerarchia)

Strutture realizzate dagli utenti:
- **Free listing**:
	gli utenti sono chiamati a creare una lista di elementi informativi a partire dalla descrizione di un topic consegnatogli

- **Card sorting**:
	permette agli utenti di strutturare il contenuto, si distingue in due tipi di sorting:
	- **Open card sorting**: gli utenti sono chiamati a formare dei gruppi con delle label fornite
	- **Closed card sorting**: gli utenti in questo caso hanno sia le label e dei gruppi, il loro compito è posizionare le label nei gruppi predefiniti

- **Tree testing**:
	viene usato per **validare una gerarchia**, l'utente naviga dei menu a tendina che rappresentano la gerarchia, e dopo che gli viene posta una domanda, dovrà cercare nel menu la sezione dove secondo lui potrà trovare l'informazione

- **Social classification**:
	viene utilizzato il **free tagging**, ovvero in questo caso è l'utente a definire il tag per il proprio contenuto, e quando ci sono tanti tag uguali è possibile definire una categoria per quell'argomento specifico.
	Il risultato del _free tagging_ è chiamato [folksonomia](https://it.wikipedia.org/wiki/Folksonomia):
	- **Folksonomia ampia**: un contenuto può essere avere più tag, anche uguali
	- **Folksonomia ristretta**: gli utenti possono taggare un contenuto solo con tag che non sono già stati usati in precedenza

