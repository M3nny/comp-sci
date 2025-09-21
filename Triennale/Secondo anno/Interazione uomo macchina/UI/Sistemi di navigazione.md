Facciamo una distinzione iniziale tra **embedded navigation system** il quale comprende i sistemi di navigazione visibili sulla pagina, e poi il **supplemental navigation system** il quale comprende i sistemi di navigazione al di fuori della pagina (e.g. sitemaps, indici, guide).

### Navigazione globale
Tenendo a mente la struttura organizzativa a _gerarchia_, un sistema di navigazione globale deve essere presente in ogni pagina, esso consente di **saltare ai punti più importanti** dell'app.

Possiamo suddividerlo ulteriormente in:
- **Navigazione verticale**: padre $\leftrightarrows$ figlio
	Una **barra di navigazione** solitamente viene usata da padre a figlio, mentre da figlio a padre solitamente si usano **breadcrumbs** o **back arrows**

- **Navigazione orizzontale**: consente di **navigare tra i fratelli**, non necessariamente deve essere in ogni livello della gerarchia

- **Navigazione locale**: viene usata come complemento per la navigazione globale, solitamente rappresenta una **feature specifica dell'app** (e.g. schermata di pagamento, mappa geografica)

- **Navigazione trasversale**: consente la navigazione in nodi dello stesso livello della gerarchia
### Punti d'accesso
Bisogna definire i punti d'accesso nell'applicazione, dove quello **principale** sarà alla **radice della gerarchia**.

Ulteriori punti d'accesso sono azionati da **eventi interni ed esterni** (e.g. notifica, evento geografico, evento azionato dall'orario).
#### Ecosistemi
Un'applicazione potrebbe far interagire più dispositivi con la stessa applicazione installata, ad esempio premere un pulsante sullo smartphone potrebbe attivare qualcosa sullo smartwatch, permettendo quindi una **cross-device interaction**.

---
## Sistema di navigazione supplementare
Questi sistemi di navigazione vengono usati come "backup" nel caso non si capisca il sistema di navigazione embedded.

- **Sitemaps**:
	rappresentano la struttura del sito in modo gerarchico, è necessario che le label elencate nella sitemaps

- **Indici**:
	elencano in modo alfabetico i contenuto del sito, si possono avere vari livelli di granularità (profondità di livelli elencati)

- **Guide**:
	possono essere realizzate in più modi. solitamente guidano l'utente passo passo all'esplorazione sequenziale per il sito.
	Utili per il marketing in quanto mostrano il prodotto ai possibili clienti

>Nelle app solitamente vengono usate le **guide** nella sezione di **onboarding**.

- **Social navigation**:
	usufruisce della **folksonomia** creando delle **word cloud** clickabili che portano ad una pagina intermedia che contiene tutti gli elementi taggati con quella parola (magari quelli in tendenza)

---
### UI wireframes
Definiscono le componenti del sito/app in maniera grezza mostrando anche gli elementi di navigazione.

