Usati per interrogare basi di dati relazionali.

Vengono definiti:
- **Operatori primitivi**: ridenominazione, proiezione, unione, differenza, restrizione e prodotto
- **Operatori derivati**: giunzione, divisione
Oltre a questi ci sono altri operatori come `group by`, `order by` e altri.

Viene usato come rappresentazione delle interrogazioni esprimendo **cosa** vogliamo ottenere, non come.
## Algebra relazionale
- **Ridenominazione (alias)**: $\rho$
	Cambia il nome di un attributo, utile quando in una query usiamo tabelle con attributi che hanno alcuni nomi uguali.

- **Unione e differenza (UNION, -)**: $\cup, -$
	Gli operatori di unione e differenza possono essere usati solo su relazioni dello stesso tipo.
	Con $R\cup S$ creo una tabella con le righe di $R$ e $S$ togliendo i duplicati.
	Con $R-S$ creo una tabella con le righe di $R$ che non compaiono in $S$.

- **Proiezione (select)**: $\pi$
	Seleziona un sottoinsieme di attributi nella relazione.

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

$R$:

| X   | Y   |
| --- | --- |
| a   | 1   |
| b   | 2   |
| a   | 2   |
| c   | 1   |
| c   | 2   |
| a   | 3   |

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

