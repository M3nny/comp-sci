#### [Barra di navigazione/menu](https://m3.material.io/components/navigation-bar/overview)
Rappresenta una **collezione di link distinti** e può supportare la navigazione: globale, locale o trasversale, l'importante è **non mischiare i tipi di navigazione**.

Solitamente le barre di navigazione vengono poste sopra e/o sotto allo schermo.
#### [Tabs](https://m3.material.io/components/tabs/overview)
Permettono la **navigazione orizzontale**.
#### [Dashboard](https://tailwindcomponents.com/components/dashboard)
Solitamente la dashboard è **associata alla home page**: il punto di ingresso dell'app.

Dovrebbe permettere di <u>raggiungere tutti gli elementi del primo livello di gerarchia</u>, solitamente si presenta come un insieme di **cards**.

Volendo è possibile anche mostrare **shortcut** a figli più profondi, però il link (card, o elemento grafico in questione) **devono essere distinguibili** da quelli che portano al primo livello di gerarchia.
#### [Breadcrumbs](https://tailwindui.com/components/application-ui/navigation/breadcrumbs)
Elencano il percorso dalla home alla pagina dove si è posizionati tramite del link sequenziali clickabili.
e.g.: `home >> livello_1 >> livello_2 >> poszione_attuale`.
>Sono segno di una buona struttura gerarchica.

Un altro modo di utilizzare i **breadcrumbs** è per **elencare una sequenza di step**, ad esempio gli step per un pagamento, dove lo **step attuale è evidenziato**, in questo modo è possibile capire quanto manca prima di concludere la procedura.
#### [Back arrows](https://m2.material.io/design/navigation/understanding-navigation.html)
Nelle applicazioni mobile a causa della mancanza di spazio, vengono utilizzate delle frecce per **tornare al padre** nella gerarchia.
>Sia i **breadcrumbs** e sia le **back arrows** devono essere posizionati **in cima allo schermo**.
#### [Menu ad hamburger (o drawers)](https://m3.material.io/components/navigation-drawer/overview)
Rappresentano un sistema di **navigazione globale** e consentono di raggiungere le aree fondamentali dell'applicazione.

Molto **utili soprattutto nelle app per mobile**, dove la presenza di una barra di navigazione potrebbe occupare gran parte dello schermo.
#### [Navigation rail](https://m3.material.io/components/navigation-rail/overview)
Rappresentano un **menu laterale ad hamburger già aperto** con delle icone che permettono di cambiare vista nell'applicazione.
#### [Widget lists](https://m3.material.io/components/lists/overview)
Implementano una **navigazione verticale**, gli elementi di una lista inoltre **rappresentano lo stesso tipo di elementi** (e.g. elenco di scarpe da comprare).
#### [Carousel](https://m3.material.io/components/carousel/overview)
Implementano la navigazione **orizzontale o trasversale**.

Anche in questo caso **rappresentano lo stesso tipo di elementi**, inoltre solitamente contengono dei puntini per capire a quale punto del carousel ci si trova e volendo anche delle frecce per scorrerlo sequenzialmente.

Si trovano anche nelle schermate di **onboarding**.
#### [Floating action buttons](https://m3.material.io/components/floating-action-button/overview)
Rappresentano **l'azione principale che l'utente compierà** in quella schermata, (e.g. "scrivi" in gmail).

Non sono quindi usati per la navigazione, bensì per le funzionalità riguardanti la pagina attuale.

Potrebbero rendere l'**esperienza meno immersiva** in quanto vanno ad occupare parte di UI.
#### [Splash screen](https://m2.material.io/design/communication/launch-screen.html#placeholder-ui)
**Dichiara l'identità dell'applicazione**, appare per pochi secondi per poi dare spazio alla schermata home.
#### [Notifiche](https://m2.material.io/design/platform-guidance/android-notifications.html#anatomy-of-a-notification)
Sebbene non facciano parte della UI dell'app, hanno un **grande impatto nella UX**.
#### [Switchers](https://m3.material.io/components/switch/overview)
**Designati per l'interazione touch**, servono per attivare o disattivare un'opzione.
#### [Date pickers](https://m3.material.io/components/date-pickers/overview)
Sono finestre che possono **far parte del layout**, **oppure** apparire come **finestre modali**, fanno selezionare una data, dove l'interfaccia usata consente di selezionare facilmente giorno, mese anno.
#### [Picker screens](https://developer.apple.com/design/human-interface-guidelines/pickers)
**Consentono di selezionare un'opzione tra un set di alternative**, portando l'utente in una pagina dedicata con _back arrow_.
>Meglio dei menu **pull-down**.
#### [Pull-down menu](https://developer.apple.com/design/human-interface-guidelines/pull-down-buttons)
Rappresentano un'alternativa alla creazione di una nuova sezione, **possono essere parzialmente nascosti**.

