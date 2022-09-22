# Insiemi
Gli insiemi di numeri sono indicati da una lettera grande mentre i loro elementi sono indicati con una lettera piccola.
- $A = \{a,b,c\}$
- $b \in A$
- Se $A = \{\} $\implies \emptyset$

## Operazioni tra insiemi
**Unione**: $A \cup B = \{x \in X | (x \in A) \lor (x \in B)\}$
**Intersezione**: $A \cap B = \{x \in X | (x \in A) \land (x \in B) \}$
**Complementare**: $A^c = \{ x \in X | (x \notin A)\}$
**Differenza**: $A \setminus B = \{x \in X | (x \in A) \cap (x \notin B) \}$
**Prodotto Cartesiano**: $A \times B = \{(x,y) | x \in A \land y \in B\}$

## Proprietà degli insiemi
$$A \cup A = A; \quad A \cap A = A$$
$$A \cup B = B \cup A; \quad A \cap B = B \cap A$$
$$A \cup \emptyset = A; \quad A \cap \emptyset = \emptyset$$
$$A \cup B \supseteq A; \quad A \cap B \subseteq A$$
$$A \cup B \supseteq B; \quad A \cap B \subseteq B$$
$$A \cup B = A \iff B \subseteq A; \quad A \cap B = A \iff A \subseteq B$$
$$A \cup (B \cap C) = (A \cup B) \cap (A \cup C);\quad
A \cap (B \cup C) = (A \cap B) \cup (A \cap C)$$
## Esempio di dimostrazione
Dimostriamo che $A \cup B = A \iff B \subseteq A$.
Per farlo, dobbiamo dimostrarlo per entrambi i sensi:
1. $A \cup B = A \implies B \subseteq A$
2. $B \subseteq A \implies A \cup B = A$

1. Sappiamo che $A \cup B = A$ quindi l'insieme $B$ deve essere:
	- Vuoto $\emptyset$
	- Contenuto dentro $A$, quindi $B \subseteq A$
	- Uguale ad A
	Per cui ne deduciamo che $B \subseteq A$

2. Sappiamo che $B \subseteq A$ 
	- $A \cup B = \{ x \in X | (x \in A) \lor (x \in B) \}$ 
	- Ma in questo caso tutti gli elementi di $B$ sono contenuti in $A$ perciò possiamo affermare che $A \cup B = A$ 
