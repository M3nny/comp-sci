I circuiti logici li troviamo sotto la forma di IC (Integrated Circuit) e si distinguono in base al loro livello di integrazione:
- **SSI** (Small Scale Integrated): 1-10 porte;
- **MSI** (Medium Scale Integrated): 10-100 porte;
- **LSI** (Large Scale Integrated): 100-100.000 porte;
- **VLSI** (Very Large Scale Integrated): > 100.000 porte.

Definiamo come **blackbox** un circuito integrato con porte direttamente colelgate ai pin esterni.

## Multiplexer
**n** input **1** output:
- Sulla base dei segnali di controllo, seleziona quale tra gli **n** input sarà l'output del circuito;
- Possono essere usati per definire una qualsiasi funzione logica in $log_2n$ variabili;
- Solitamente I/O sono di 32 bit;
- È presente un grande spreco di porte, dato che le porte AND hanno arietà maggiore del necessario.
![[Multiplexer.png]]

## Demultiplexer
**1** input **n** output:
- Se l'input è uguale a 0, gli output dovranno essere uguali a 0:
- Se l'input è uguale a 1, un solo output dovrà essere uguale a 1, mentre gli altri saranno a 0.
![[Demultiplexer.png]]
## Decoder
**n** input $2^n$ output:
Se la rappresentazione binaria degli input forma il numero $i$ dell'output allora, solo in questo caso il risultato sarà 1, altrimenti per tutti gli altri casi sarà 0.
![[Decoder.png]]

## PLA
**n** input, **m** AND, **o** output/OR:
Il PLA (Programmable Logic Array) consente di costruire funzioni logiche in forma [[Porte logiche#2-level logic|SP]], con porte AND al primo livello e porte OR al secondo livello, questo è possibile bruciando i fusibili così da poter decidere quali sono gli input di ogni porta AND e OR.
![[PLA.png]]

## ROM
La ROM (Read Only Memory) può essere:
- PROM (Programmable ROM): scrivibile solo una volta;
- EPROM (Erasable PROM): cancellabile con l'ultravioletta.
Data una tabella di verità, sono usate per memorizzare le funzioni logiche (corrispondenti a diverse colonne).
![[ROM.png]]

Il PLA rimane comunque una soluzione migliore rispetto ad altri circuiti combinatori in quanto posso realizzarlo con meno componenti possibili. 