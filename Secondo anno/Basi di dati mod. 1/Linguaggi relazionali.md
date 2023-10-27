Usati per interrogare basi di dati relazionali.

Vengono definiti:
- **Operatori primitivi**: ridenominazione, proiezione, unione, differenza, restrizione e prodotto
- **Operatori derivati**: giunzione, divisione
Oltre a questi ci sono altri operatori come `group by`, `order by` e altri.

Viene usato come rappresentazione delle interrogazioni esprimendo **cosa** vogliamo ottenere, non come.
## Algebra relazionale
- **Ridenominazione (alias)**: $\rho$
	Cambia il nome di un attributo, utile quando in una query usiamo tabelle con attributi che hanno alcuni nomi uguali.

- **Unione e differenza**: $\cup, -$
	L'operatore di unione può essere usato solo su relazioni dello stesso tipo.

- **Proiezione (select)**: $\pi$
	Seleziona un sottoinsieme di attributi nella relazione.

- **Restrizione (where)**: $\sigma_\phi$
	Restringe le ennuple selezionate, confrontandole una ad una con la condizione posta da $\phi$ su un loro attributo.

- **Prodotto (cross join)**: $\times$
	Concatena tutte le ennuple di $R$ a quelle di $S$, i nomi degli attributi devono essere tutti distinti, altrimenti bisogna usare $\rho$.
