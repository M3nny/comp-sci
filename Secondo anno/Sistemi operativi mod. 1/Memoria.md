Come visto in [[Tipologie di memoria|passato]] abbiamo una gerarchia di memoria, dalla più piccola, veloce e costosa:
- **Cache**: memorizza una copia dei dati più usati per un accesso veloce
- **Principale**: memorizza solo dati e programmi necessari ai programmi in esecuzione
- **Secondaria**: memorizza dati e programmi non necessari al momento

Esistono varie **strategie** di gestione della memoria, tra cui quelle di:
- **Fetch**: decide _quando_ copiare i dati di un programma
- **Posizionamento**: decide _dove_ inserire i dati e programmi in memoria principale
- **Sostituzione**: decide _quali_ dati o programmi rimuovere dalla memoria principale per creare spazio

L'**allocazione** può essere:
- **Contigua**: un programma deve essere memorizzato in un **unico** blocco di indirizzi contigui, anche se ha poco overhead, questo tipo di allocazione potrebbe non trovare un blocco contiguo grande abbastanza
- **Non contigua**: il programma è diviso in **segmenti** allocati diverse parti della memoria, essendo più facile trovare buchi, ci possono stare più processi, il che compensa l'overhead di questa tecnica
