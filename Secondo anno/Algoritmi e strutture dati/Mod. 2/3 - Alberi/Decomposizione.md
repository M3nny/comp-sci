Le operazioni sugli alberi si possono ridurre in un algoritmo _divide et impera_:
```
decomponi (Node u)
	if u == NULL // operazione su albero vuoto
		// risolvi direttamente
	else if
		// possibili altri casi base
	else
		risultato_sx = decomponi(u.left)
		risultato_dx = decomponi(u.right)
		return ricombina(risultato_sx, risultato_dx)
```

Vediamo un'applicazione pratica scrivendo una funzione che restituisce il numero di nodi intermedi di un albero data la sua radice.

Un **nodo intermedio** è detto tale se la somma dei valori all'interno dei nodi del sottoalbero di radice $u$ è uguale alla somma dei nodi da $u$ (non compreso) alla radice, se $u$ è la radice dell'albero completo allora la somma del percorso fino alla radice è $0$.
![[Nodo intermedio.svg]]
```c++
struct Node {
	int key;
	Node* left;
	Node* right;
}
typedef Node* pNode;

int intermedi(pNode r) { // funzione cappello
	int sum_sott;
	return intermedi_aux(r, 0, sum_sott);
}

int intermedi_aux(pNode u, int sum_p, int& sum_sott) {
	if (u == nullptr) {
		sum_sott = 0;
		return 0;
	}
	
	int num_sx, num_dx, sum_sx, sum_dx;
	num_sx = intermedi_aux(u->left, sum_p + u->key, sum_sx);
	num_dx = intermedi_aux(u->right, sum_p + u->key, sum_dx);
	sum_sott = sum_sx + sum_dx + u->key;
	
	if (sum_sott == sum_p) {
		return 1 + num_sx + num_dx;
	} else {
		return num_sx + num_dx;
	}
}
```
##### Complessità
Essendo che abbiamo usato la decomposizione, e quindi scomposto il problema usando la visita DFS e operando sui nodi, la complessità sarà uguale alla complessità della DFS dato che le altre operazioni sono tutte costanti.
$$T(n)=\Theta(n)$$
