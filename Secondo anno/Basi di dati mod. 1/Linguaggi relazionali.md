Usati per interrogare basi di dati relazionali.

Vengono definiti:
- **Operatori primitivi**: ridenominazione, proiezione, unione, differenza, restrizione e prodotto
- **Operatori derivati**: giunzione, divisione
Oltre a questi ci sono altri operatori come `group by`, `order by` e altri.

Viene usato come rappresentazione delle interrogazioni esprimendo **cosa** vogliamo ottenere, non come.
## Algebra relazionale
- **Ridenominazione (alias)**: $\rho$
	Cambia il nome di un attributo, utile quando in una query usiamo tabelle con attributi che hanno alcuni nomi uguali.
	$\rho_{A\leftarrow B}(R)$: rinomino l'attributo $A$ (di $R$) con $B$.

- **Unione e differenza (UNION, -)**: $\cup, -$
	Gli operatori di unione e differenza possono essere usati solo su relazioni dello stesso tipo.
	Con $R\cup S$ creo una tabella con le righe di $R$ e $S$ togliendo i duplicati:
	$R\cup S\{t: t\in R\lor t\in S\}$.
	Con $R-S$ creo una tabella con le righe di $R$ che non compaiono in $S$:
	$R-S=\{t:t\in R\land t \notin S\}$.

- **Proiezione (select)**: $\pi$
	Seleziona un sottoinsieme di attributi nella relazione.
	Una proiezione può essere anche **generalizzata** se comprende espressioni.
	e.g. $\pi_{\text{Codice, SalarioLordo - Trattenute AS stipendio}}\text{(Utente)}$ 

- **Restrizione (where)**: $\sigma_\phi$
	Restringe le ennuple selezionate, confrontandole una ad una con la condizione posta da $\phi$ su un loro attributo.

- **Prodotto (cross join)**: $\times$
	Concatena tutte le ennuple di $R$ a quelle di $S$, i nomi degli attributi devono essere tutti distinti, altrimenti bisogna usare $\rho$.
	![[Prodotto cartesiano.png|500]]

- **Giunzione naturale (natural join)**: $\bowtie$
	Se $R(x,y)$ e $S(x, z)$ allora $R\bowtie S(xyz)$, se non ci sono attributi uguali, risulta essere un prodotto cartesiano.

$R$: 

| ID  | Nome  | 
| --- | ----- |
| 1   | Mario |
| 2   | Luigi |
| 3   | Peach |

$S$:

| ID  | Città   |
| --- | ------- |
| 1   | Roma    |
| 2   | Milano  |
| 4   | Venezia |

$R\bowtie S$:

| ID  | Nome  | Città  |
| --- | ----- | ------ |
| 1   | Mario | Roma   |
| 2   | Luigi | Milano |

- **Giunzione (inner join)**: $R \underset{R.a=S.b}{\bowtie} S$
	Crea una tabella dove vengono collegate le righe che hanno in comune l'attributo specificato nella clausola di join.

- **Giunzione esterna (outer join)**: $\underset{R.a=S.b}{\stackrel{\leftrightarrow}{\bowtie}}$
	A differenza della _giunzione naturale_, vengono incluse anche le righe non presenti in una delle due tabelle, mettendo a NULL i valori assenti.
	Ha una clausola di join.

$R \underset{R.ID=S.ID}{\stackrel{\leftrightarrow}{\bowtie}} S$:

| ID  | Nome  | Città   |
| --- | ----- | ------- |
| 1   | Mario | Roma    |
| 2   | Luigi | Milano  |
| 3   | Peach | NULL    |
| 4   | NULL  | Venezia |

- **Giunzione esterna sinistra (left outer join)**: $\underset{R.a=S.b}{\stackrel{\leftarrow}{\bowtie}}$
	Crea una tabella con tutte le righe della tabella a sinistra dell'operatore, se non ci sono corrispondenze sulla tabella di destra, viene assegnato il valore di NULL sui valori mancanti.
	Ha una clausola di join.

$R \underset{R.ID=S.ID}{\stackrel{\leftarrow}{\bowtie}} S$:

| ID  | Nome  | Città  |
| --- | ----- | ------ |
| 1   | Mario | Roma   |
| 2   | Luigi | Milano |
| 3   | Peach | NULL   |

- **Giunzione esterna destra (right outer join)**: $\underset{R.a=S.b}{\stackrel{\rightarrow}{\bowtie}}$
	Discorso analogo alla _giunzione esterna sinistra_, solo che in questo caso la tabella creata avrà tutte le righe della tabella di destra.
	Ha una clausola di join.

$R \underset{R.ID=S.ID}{\stackrel{\rightarrow}{\bowtie}} S$:

| ID  | Nome  | Città   |
| --- | ----- | ------- |
| 1   | Mario | Roma    |
| 2   | Luigi | Milano  |
| 4   | NULL  | Venezia |

- **Intersezione (intersect)**: $\cap$
	Crea una tabella contenente solo le righe in comune tra le due tabelle su cui effettuare l'intersezione.

- **Divisione**: $\textdiv$
	Crea una tabella dove ogni elemento $t_1$ non appartenente alla seconda tabella è concatenato almeno con i valori della seconda tabella.
	Crea una tabella partendo da $R$ dove:
		- Le colonne in comune con $S$ sono rimosse
		- Vengono mantenute le righe di $R$ che possedevano almeno tutti i valori delle colonne condivise
	Esprimibile come: $\pi_X(R)-\pi_X((\pi_X(R)\times S)-R)$ 

$R$:

| $X$ | $Y$ |
| ---- | ---- |
| a | 1 |
| a | 2 |
| a | 3 |
| b | 1 |
| c | 1 |
| c | 2 |

$S$:

| Y   |
| --- |
| 1   |
| 2   |

$R \textdiv S$:

| X   |
| --- |
| a   |
| c   |

- **Raggruppamento (group by)**: $\gamma$
	Raggruppa le righe a seconda delle funzioni di aggregazione.
	e.g. $A_1,...,A_n\gamma f_1,...,f_k(R)$ dove $A_i$ sono gli attributi di $R$ e $f_i$ sono funzioni di aggregazione.


## Funzioni di aggregazione
Hanno come argomenti più insiemi e ritornano un valore.
- **sum**: ritorna la somma degli elementi
- **avg**: ritorna la media degli elementi
- **count**: ritorna il numero degli elementi
- **min** e **max**: ritornano rispettivamente il minimo ed il massimo valore degli elementi
Se si vuole ignorare eventuali duplicati, si mette alla fine della funzione **-distinct**.

>[!Example]
>Trovare per ogni candidato il numero di esami, voto minimo, massimo e medio.
>
>| Materia | Candidato | Data     | Voto | Lode |
>| ------- | --------- | -------- | ---- | ---- |
>| BD      | 1234      | 01.01.03 | 20   | N    |
>| FIS     | 4321      | 02.03.04 | 26   | N    |
>| ASD     | 1234      | 07.02.03 | 30   | S    |
>| BD      | 4321      | 10.12.05 | 28   | N    |
>
>$$\text{Candidato}\gamma_{\text{count(*),min(Voto),max(Voto),avg(Voto)}}\text{(Esami)}$$
>
>| Candidato | Count(*) | min(Voto) | max(Voto) | avg(Voto) |
>| --------- | ------- | --------- | --------- | --------- |
>| 1234      | 2       | 20        | 30        | 25        |
>| 4321      | 2       | 26        | 28        | 27        |

## Operazioni su multinsiemi
- **Proiezione senza eliminazione dei duplicati**:
$$\pi^b_{A_1,...,A_n}(O)$$
- **Eliminazione di duplicati**:
$$\delta(O)$$
- **Ordinamento**:
$$\tau A_1,...,A_n(O)$$
- **Unione, intersezione e differenza**:
$$O_1\cup^bO_2$$
in questa unione vengono inseriti tutti i duplicati (non si sottrae l'intersezione).
$$R\cap^bS$$
in questa intersezione possono esserci più righe uguali, il numero di righe uguali rispecchia il numero di duplicati della tabella che ne aveva di meno.
$$O_1-^bO_2$$
in questa differenza solo una singola occorrenza di ogni elemento in $O_2$ viene rimossa da $O_1$, quindi se un elemento appare più volte in $O_1$, ma solo una volta in $O_2$, allora questa differenza conserverà le occorrenze extra di quell’elemento in $O_1$.

### Trasformazioni algebriche
- $\pi_A(\pi_{A,B}(R))\equiv\pi_A(R)$
- $\sigma_{C_1}(\sigma_{C_2}(R))\equiv\sigma_{C_1\land C_2}(R)$
- $\sigma_{C_1\land C_2}(R\times S)\equiv\sigma_{C_1}(R)\times\sigma_{C_2}(S)$
- $R\times(S\times T)\equiv(R\times S)\times T$
- $(R\times S)\equiv(S\times R)$
- $\sigma_C(_X\gamma_F(R))\equiv _X\gamma_F(\sigma_C(R))$

>[!Example]
>- Trovare le lingue ufficiali parlate da piu del 50% della popolazione di una nazione europea.
> 	$\pi_{language}(\sigma_{\text{continent='Europe'}\land \text{percentage}>50\land \text{isofficial = true}} (\text{Contrylanguage}\underset{\text{code=countrycode}}{\bowtie}\text{Country}))$
> - Trovare il nome dei prodotti fabbricati da produttori colombiani aventi costo maggiore di 1000 dollari.
> 	$\pi_{\text{nomeProdotto}}(\sigma_{\text{prezzo} > 1000\land \text{paese = 'Colombia'}}(\text{produttori} \bowtie \rho_{\text{nome}\leftarrow\text{nomeProdotto}}(\text{prodotti})))$
> - Trovare il nome e cognome degli atleti italiani o svedesi che hanno vinto una medaglia d’argento nella disciplina Short track.
> 	$\pi_{\text{nome, cognome}(\sigma_{(\text{nazione='Italia'}\lor\text{nazione='Svezia})\land\text{tipo='Argento'}\land\text{disciplina='Short track'}}(\text{atleti }\bowtie\text{ medaglie})}$


---
## Calcolo relazionale
Il **calcolo relazionale (CR)** è un'alternativa all'algebra relazionale, ne esistono due varianti:
- Su **ennuple (CRE)**
- Su **domini (CRD)**

Ogni interrogazione è esprimibile ognuno di questi metodi (algebra relazionale inclusa) in quanto sono **relazionalmente completi**.

A differenza dell'algebra relazionale che è un **linguaggio procedurale** che oltre a specificare cosa recuperare specifica anche come farlo, nel calcolo relazionale, il quale è un **linguaggio dichiarativo**, si specifica un'espressione di affermazioni logiche, la quale interpretazione da luogo alle ennuple desiderate (sarà il DBMS a capire come ricavare le informazioni).

Vengono quindi usati:
- **Termini**: costanti, variabili e funzioni
- **Formule**: $\land, \lor,\neg,\implies,\iff,\forall,\exists,...$ 
#### Traduzione da AR a CRE
- **Proiezione**: $\pi_{\text{Nome, Cognome}}(\text{Studenti})=\{\text{t.Nome, t.Cognome}|t\in \text{Studenti}\}$
- **Restrizione**: $\sigma_\text{Provincia='VE'}(\text{Studenti})=\{t|t\in \text{Studenti}\land \text{t.Prov = 'VE'}\}$ 
- **Unione**: $\text{Studenti}\cup\text{Docenti}=\{t|t\in\text{Studenti}\lor t\in\text{Docenti}\}$
- **Intersezione**: $\text{Studenti}\cap\text{Docenti}=\{t|t\in\text{Studenti}\land t\in\text{Docenti}\}$
- **Differenza**: $\text{Studenti - Docenti} = \{t|t\in\text{Studenti}\land\neg(t\in\text{Docenti}\}$
- **Prodotto**: $\text{Studenti}\times\text{Esami}=\{s,e|s\in\text{Studenti}\land e\in\text{Esami}\}$

