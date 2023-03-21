A differenza della [[Cache diretta|cache diretta]]  la quale usa una funzione per mappare i blocchi con gli indirizzi, si dice **cache completamente associativa** se ogni blocco può essere associato con un blocco qualsiasi della cache.

L'accesso non dipende dall'indirizzo dato che la ricerca viene fatta scorrendo tutti i possibili blocchi (_poco efficiente_ con molti blocchi).

![[Diretta vs associativa.png|500]]

Non esiste solo un tipo di cache associativa, si differenziano in base al numero di insiemi e blocchi (vie) ciascuno.

### N-way
- La **scelta dell'insieme (set)** avviene con una funzione di mapping come nella cache diretta.
- La **scelta della via** avviene senza una funzione di mapping, come nella cache completamente associativa.

![[N-ways comparison.svg|500]]
Solitamente blocchi e insiemi sono multipli di 2, la **funzione di mapping per la scelta dell'insieme** funziona nel seguente modo:
$$\text{Block address} = \frac{\text{address}}{\text{block size}}$$
$$\text{Index} = \text{block address} \space\%\space \text{numero di set}$$

Dopo aver trovato l'index dobbiamo scorrere tutti i tag per individuare il blocco specifico.
![[Mapping 2-way.svg|700]]
>[!Example]
>Avendo block address = [0, 8, 0, 6, 8]
>L'index dell'insieme è dato da (block address % numero di set) quindi:
>[0%2 = 0, 8%2 = 0, 0%2 = 0, 6%2 = 0, 8%2 = 0]
>
>![[Esempio 2-way.png]]
>1. 0 non è presente in cache, dopo il miss viene inserito nel set 0 nella prima posizione libera
>2. 8 non è presente in cache, dopo il miss viene inserito nel set 0 nella prima posizione libera
>3. 0 è presente in cache, hit
>4. 6 non è presente in cache ed il suo index è pari a 0 ma il set 0 è già pieno, quindi viene rimpiazzato il blocco non utilizzato da più tempo, ovvero 8
>5. 8 è stato appena rimpiazzato e quindi non è presente in memoria, il suo index è 0 ma il set 0 è già pieno, quindi viene rimpiazzato 0 in questo caso dato che 6 è appena stato aggiunto

## Gestione dei miss
Nella cache diretta abbiamo la funzione di mapping che ci dice quale blocco sostituire, in questo caso indichiamo solo l'index, poi abbiamo due modi per risolvere il miss:
- Usare un possibile blocco libero del set
- Se sono tutti occupati bisogna **rimpiazzare un blocco** 

### Politiche di rimpiazzamento blocchi
- **Casuale** 
- **Leat Recently Used (LRU)**: si rimpiazza il blocco usato meno recentemente, per fare ciò vengono usati dei bit aggiuntivi per memorizzare da quanto tempo un blocco non viene acceduto.

