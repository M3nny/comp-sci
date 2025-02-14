Un **modello astratto** è la rappresentazione formale di idee e conoscenze relative ad un fenomeno.

```mermaid
graph TD
A[ANALISI DEI REQUISITI]
A --> B[PROGETTAZIONE CONCETTUALE]
B --> C[PROGETTAZIONE LOGICA]
C --> D[PROGETTAZIONE FISICA]
```
## Modellazione concettuale
- **Entità**: sono ciò di cui interessa rappresentare alcune proprietà, può essere anche una <u>collezione</u> di entità uguali (e.g. studenti)
- **Proprietà**: sono fatti che descrivono caratteristiche delle entità, in particolare è una _coppia_ <Attributo, valore> e può essere:
	- atomica (e.g. nome)
	- strutturata (e.g. indirizzo residenza)
	- multivalore (e.g recapiti telefonici)

>Spesso le _collezioni_ rappresentano **specializzazioni/generalizzazioni** (e.g. utenti => studenti, docenti) dove una collezione specializzata è un sottoinsieme che possiede le proprietà della superclasse (collezione da cui eredita proprietà)

### Associazioni
Una associazione <u>lega più collezioni tra loro</u> dove il **dominio** è dato dal prodotto cartesiano delle due collezioni, ed è caratterizzata dalle seguenti proprietà strutturali:

- **Cardinalità** (o molteplicità) considerando gli insiemi X e Y può essere:
	- **1:1**: ogni elemento x è associato al massimo 1 elemento di Y e viceversa
	- **1:N**: ogni elemento x può avere più associazioni verso gli elementi di Y, ma gli elementi y possono avere solo 1 associazione con con elementi di X
	- **N:1**: ogni elemento x può avere al massimo 1 associazione con 1 elemento di Y, ma gli elementi y possono avere più associazioni con elementi di X
	- **N:M**: ogni elemento di X e Y può avere più associazioni verso elementi dell'altro insieme

Con il **vincolo di univocità** definiamo un'associazione <u>univoca da X a Y</u> se ogni elemento x è associato _al massimo_ ad un elemento di Y altrimenti è <u>multivalore</u>.

Con il **vincolo di totalità** definiamo un'associazione <u>totale da X a Y</u> se ogni elemento x è associato ad _almeno_ un elemento di Y, altrimenti è <u>parziale</u>.


>[!Example]
>- **NataA(Persone, Città)**
>	(N:1), totale su Persone e parziale su CIttà
>- **HaVisitato(Persone, CIttà)**
>	(N:M), parziale su entrambe
>- **SindacoDi(Persone, CIttà)**
>	(1:1), parziale su entrambe

### Vincoli di integrità
I **vincoli di integrità** sono usati per applicare <u>restrizioni</u> su possibili valori e sui modi in cui essi possono evolvere nel tempo, possono essere:
- **Statici**: definiscono condizioni sui valori indipendentemente da come evolveranno (e.g. età deve essere un intero positivo)
- **Dinamici**: definiscono condizioni sul modo in cui i valori potranno evolversi (e.g. DataNascita non può essere cambiata)

---
## Cosa si modella
- **Classe** (o entità o collezioni di oggetti): insiemi di oggetti dello stesso tipo
- **Oggetto**: una istanza della classe (riga nella tabella)

I **tipi degli attributi** possono essere:
- **Primitivi**: int, real, bool, data, string
- **Non primitivi**:
	- _record_: `{A1:T1; ...; An:Tn}`
	- _Enumerazione_: `(Val1; ...; Valn)`
	- _Sequenza_: `seq T` dove T è un tipo, e.g.: it, us, fr

### Associazioni
Le associazioni sono indicate dalle frecce:
- <--> 1:1
- <-->> 1:n
- <<--> n:1
- <<-->> n:n

Inoltre se la freccia appare _sbarrata_ vuol dire che l'associazione è **parziale** (qualche elemento potrebbe non avere una relazione verso elementi dell'altra classe) verso la parte in cui la freccia è sbarrata, altrimenti è **totale** (tutti gli elementi hanno almeno un elemento a cui sono relazionati rispetto l'altra classe). 

Possono avere **proprietà** ed anche essere **ricorsive**, specificando così una relazione tra oggetti dello stesso tipo.

![[Tipi di associazioni.png]]

>[!Example]
>Si vuole rappresentare l’associazione tra Voli, Passeggeri e Posti. Per ogni volo, al momento dell’imbarco, viene assegnato un posto a ciascun passeggero.
>
>![[Esempio associazioni.png]]

### Gerarchie ed ereditarietà
Con la relazione di **sottotipo** ($\leq$) tra $t\leq t'$ indichiamo che gli elementi di $t$ hanno tutti gli attributi degli elementi di $t'$ dove anche i tipi di $t$ sono uguali o sottotipi rispetto ai tipi di $t'$.

Possiamo definire una **sottoclasse** con vincolo:
- _estensionale_: dove C è sottoclasse di C' e le entità in C sono un sottoinsieme di quelle di C'
- _intensionale_: dove C è sottoclasse di C' ed il tipo delle entità in C è sottotipo degli elementi di C'

![[Vincoli sottoclassi.png|700]]
Dopo aver visto i vari vincoli vediamo come si possono combinare per creare varie sottoclassi:
- **Scorrelate**: possono avere cose in comune tra loro, assieme non formano la classe padre
- **Disgiunte**: non hanno nulla in comune tra loro, assieme non formano la classe padre
- **Copertura**: possono avere cose in comune tra loro, assieme formano la classe padre
- **Partizione**: non hanno nulla in comune tra loro, assieme formano la classe padre