### Riga di comando
**Pro**:
- Accesso diretto alle funzioni del sistema
- Flessibilità con parametri
**Contro**:
- Difficoltà di utilizzo e di apprendimento

Inizialmente erano presenti solo dei **menu grezzi**, in questa forma limitata di un sistema WIMP, gli spostamenti e la selezione della varie opzioni avviene con un meccanismo di [[La macchina#Posizionamento discreto - indiretto|posizionamento discreto]].

L'utilizzo del **linguaggio naturale** non funziona bene con i computer, in quanto il nostro linguaggio può essere ambiguo, per questo utilizziamo linguaggi formali per comunicare con il computer.

- L'interfaccia a **scelta multipla e risposta aperta** è adatta ad utenti occasionali
- L'interfaccia con **linguaggi di interrogazione** non è adatta ad utenti occasionali e serve per recuperare informazioni da un database

### Linguaggi visuali
I linguaggi visuali rendono impossibile generare errori di sintassi se ben progettati, essi spaziano tra molti domini e applicazioni diverse:
- **Simulink**: ambiente di programmazione grafica basato su matlab
- **VVVV**: toolkit per la sintesi video
- **MAXMSP**: programmazione visuale per musica e multimedia
- **Web MGISql**: è possibile specificare relazioni tra elementi visuali per creare una query (fatto da Unive)
- **Scratch**
- **Blockly**: libreria javascript che imita scratch, è possibile usare blocchi di linguaggi di programmazione differenti
- **Dash and dot**: minirobot che si muovono in base al programma di blockly
- **App inventor**: interfaccia simile a scratch ma più complessa per creare applicazioni
- **Unreal engine blueprint**: consente di definire concetti tramite nodi

---
## Interfacce WIMP
Le interfacce **WIMP**: Window Icon Menu Pointer
nascono con l'avvento dei personal computer per renderli più usufruibili da più persone tramite **widget visuali**.

Nascono negli anni '70 nei laboratori di **Xerox**.

Vengono utilizzate delle **metafore** per insegnare nuovi concetti in riferimento a quelli già noti, in particolare nelle interfacce WIMP viene usata la metafora dell'ufficio, dove si ha una scrivania e si può interagire con varie elementi.
Bisogna rendere le **metafore coerenti** con tutta l'interfaccia grafica.

Viene usata la metafora **mondo modello** per dire che l'interfaccia è un mondo su cui l'utente agisce e ne cambia lo stato, l'utente inoltre ha la sensazione che le sue azioni siano **dirette** senza elementi intermedi.
>Per l'utente l'interfaccia **è** il sistema.

Caratteristiche della **manipolazione diretta**:
- Visibilità degli oggetti
- Azioni incrementali e feedback veloce
- Reversabilità delle azioni
- Ogni azione è ammessa (non come "command not found" nelle cli)

L'**input** e **output** vengono **mischiati**, ad esempio un'icona è sia un output che un input in quanto può essere trascinata.

L'**interfaccia industriale** è un intermediario tra l'operatore ed il mondo reale, in quanto l'operatore riceve feedback sia dall'interfaccia e sia dal macchinario controllato.

### Elementi delle interfacce WIMP
**Window**: usata per separare i diversi compiti dell'utente, si distinguono le finestre di dialogo:
- **Modali**: blocca l'interazione con l'applicazione fino a quando non viene premuto OK (e.g. segnalazioni, errori)
- **Non modali**: non bloccano l'interazione

**Icon**: usate per rappresentare finestre chiuse e le funzioni accessibili dall'utente.

**Menu**: attivano una funzionalità legata ad un'applicazione, hanno struttura **lineare, gerarchica o circolare**, si distinguono in menu:
- **Fall-down**: si aprono `on-hover`, possono causare affollamento non voluto dell'interfaccia
- **Pull-down**: si aprono premendo sul menu

Gli elementi di un menu dovrebbero essere **raggruppati per funzione**, utilizzando **separatori interni**, dovrebbero essere ordinati anche secondo **importanza e frequenza** di utilizzo, le **funzionalità opposte** devono essere ben separate.

I **menu circolari** vengono generati dopo una combinazione di tasti e mostrano attorno al cursore delle opzioni da scegliere facilmente raggiungibili.

**Pointer**: identifica la **zona attiva**, inoltre può assumere varie forme in base al contesto.

### Elementi vari
**Pulsanti**: è importante distinguere tra:
- **Radio button**: permettono una sola scelta
- **Check box**: permettono zero o più scelte

**Toolbar**: collezione di pulsanti dotati di icona, (shortcut per elementi nei menu).
**Palette**: collezione di pulsanti fluttuante, alternativa alla _toolbar_ fissa, alcune palette consentono la selezione di elementi nascosti una volta che il cursore è sopra un suo pulsante.

**Tabs**: collezioni di pulsanti per organizzare informazioni correlate, possono creare **ambiguità** se usate assieme a _finestre modali_ in quanto con l'opzione OK non si sa se si va a confermare le scelte della tab oppure dell'intera finestra modale.
È possibile sciogliere queste ambiguità rappresentando se il pulsante OK fa parte della tab o meno.

**Ribbon**: evoluzione della _toolbar_, ospita categorie diverse di entità.

>[!Info] Cose da non fare
>- Tabs su righe multiple
>- Tab singoli

### Interfacce WIMP 3D
In questo tipo di interfacce 3D vengono effettuate alcune modifiche:
- Posizionamento di finestre in uno spazio 3D
- Trasformazione di widget 2D in 3D
- La sostituzione del mouse con dispositivi più immersivi

**Windows Vista** proponeva una soluzione in cui tutte le finestre comparivano in 3 dimensioni, una volta selezionata però si ritornava a lavorare in 2D.
**Steam VR** utilizza un controller con un raggio luminoso (virtuale) per selezionare vari elementi.

---
## Gestualità
Esistono tre tipi di gesti:
- **Manipolativi**: imitano l'azione nel mondo reale
- **Deittici**: usati per indicare
- **Simbolici**: si basano su convenzioni dipendenti dalla cultura

essi possono essere eseguiti su una **superficie** oppure **nell'aria**, a differenza dei sistemi WIMP basati su mouse, i sistemi basati su gestures **non sono standardizzati** perchè possiedono un elevato grado di espressività.

Le principali gestualità che si possono applicare sono:
- **Drag/move**
- **Enlarge/shrink**
- **Rotate**
- **Sweep** (spostamento di più oggetti)
- **Flick** (breve spinta di un oggetto)
- **Hold** (tocco fermo per mantenere in posizione un oggetto)

È **desiderabile** convergere verso un insieme di **gesture standard** per ridurre i tempi di apprendimento su dispositivi che usano gestures.
La realtà è diversa però, in quanto:
- Le gesture implementate dagli sviluppatori delle app possono essere diverse da quelle del sistema operativo
- Le gestures tra vari dispositivi variano anche a causa di brevetti depositati

### Output
Con l'avvento delle interfacce touch, anche l'output ha subito cambiamenti, ad esempio bisogna prestare attenzione all'**occlusione dello schermo** da parte della mano (vedi tastiera con lettera pop up sopra al dito).

La **minore precisone** del tocco ha portato ad **aree più estese** per la selezione di comandi, le **finestre modali** occupano gran parte dello schermo, i **checkbox** sono diventati degli **switch**.

#### Brevettare un gesto
Esistono molti gesti brevettati come lo **slide to unlock** di apple implementato nei primi iphone.

Un altro esempio è il **scroll-back and bounce** di apple, in cui la pagina rimbalza indietro una volta raggiunto il limite, questo porta altri produttori a creare qualcosa di diverso, come un **effetto di luminescenza** al raggiungimento della fine della pagina.

<u>Al momento in Europa non è consentito brevettare le interfacce</u> (a differenza degli Stati Uniti).
Però è possibile depositare un modello costituito da uno o più disegni per descrivere un'interfaccia ed una sequenza di animazione che la caratterizza.

Secondo **Norman** e **Nielsen** le interfacce gestuali hanno portato problemi tra cui:
- **Mancanza di linee guida**
- **Creazioni di nuove convenzioni** ignorando quelle esistenti
- **Noncuranza** da parte degli sviluppatori, ignorando la storia della ricerca nell'interazione uomo macchina

### Mid-air gestures
Le gestures in aria hanno ancora più problemi di standardizzazione, inoltre sono soggette a **problemi di identificazione del significato** a causa di vari aspetti culturali.
>Pure i linguaggi dei segni cambiano di paese in paese.

---
## Modelli di interazione
I **modelli di interazione** sono utili per identificare le componenti del dialogo tra utente e sistema, e gli eventuali problemi.

- **Dominio**: descrive un'area di interesse
- **Obiettivo**: il risultato che si desidera ottenere
- **Intenzione**: modalità con cui si raggiunge l'obiettivo
- **Compito (task)**: articolazione dell'intenzione in **azioni**

#### Ciclo di esecuzione e valutazione (D. Norman)
Formato da 7 componenti:
1. Stabilire l'obiettivo
2. Concepire l'intenzione
3. Formulare una sequenza di azioni
4. Eseguire le azioni
5. Percepire lo stato del sistema
6. Interpretare lo stato del sistema
7. Valutare lo stato del sistema rispetto all'obiettivo

Questo modello si concentra solo sull'**interfaccia** che viene percepita dall'utente come sistema.
#### Interaction framework (Abowd & Beale)
Rappresenta un'estensione del modello di Norman, nella quale viene esplicitamente considerato il sistema dietro l'interfaccia.

Formato da 4 componenti:
1. Utente
2. Interfaccia di input
3. Sistema
4. Interfaccia di output

  I problemi di interazione sono **problemi di traduzione**, le traduzioni che avvengono sono le seguenti:
  - **Articolazione**: l'utente articola il linguaggio del compito in linguaggio di input
  - **Performance**: l'interfaccia traduce il linguaggio di input in stimoli per il sistema
  - **Presentazione**: il sistema presenta il risultato formulato nel linguaggio di output
  - **Osservazione**: l'utente traduce il linguaggio di output nel proprio linguaggio

  **Risoluzione di problemi**:
  - È possibile applicare delle etichette esplicite che spieghino il significato di input
- Bisogna tradurre bene lo stato del sistema in output in questo modo si evitano incomprensioni


  