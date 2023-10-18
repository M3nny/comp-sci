Un dizionario rappresenta il concetto matematico di una **relazione univoca**$R:D\to C$ fra gli elementi di un insieme $D$ (dominio) e gli elementi di un insieme $C$ (codominio).
Gli elementi del dominio sono detti **chiavi** e gli elementi del codominio sono detti **valori**.

- **Dati**: un insieme di coppie (chiave-valore)
- **Operazioni**:
	- `search(Dizionario S, Chiave K) -> elem or {NIL}`
		**Post**: restituisce il valore associato alla chiave $K$ se presente in $S$, altrimenti restituisce NIL.
	- `insert(Dizionario S, Elem v, Chiave K)
		**Post**: associa il valore $v$ alla chiave $K$ 
	- `delete(Dizionario S, Chiave K)`
		**Pre**: $K$ deve essere presente in $S$
		**Post**: cancella da $S$ la coppia con chiave $K$
