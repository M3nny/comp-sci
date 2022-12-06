Abbandoniamo l'idea di completare l'istruzione in un singolo ciclo di clock.
Ho quindi bisogno di **registri di stato che salvano i risultati parziali di un'istruzione** così da poterla fare continuare nel prossimo ciclo di clock.
Lo stesso per **l'instruction register** che deve essere sempre quello fino a quando è finita l'operazione.

## Sequenza passi (cicli) esecuzione
1. 1
2. Leggo i registri (in parallelo) nel caso servisse ad una istruzione dopo, inoltre anticipo del lavoro per il branch in modo tale che se dopo ci sarà una _beq_, essa potrà terminare in un ciclo al posto di impiegarne due
3. 3
4. Completo R-type e completo store (sw)
5. 5

**Tempi di completamento istruzioni**:
| **n° cicli** | **istruzione** |
| ------------ | -------------- |
| _3_          | jump, beq      |
| _4_          | R-type, store  |
| _5_          | load           |

>[!Tip] Domanda esame
>Quanti sono, cosa sono e cosa si fa nei cicli? (Può chiederlo in generale oppure per una istruzione specifica)

Vediamo ora nel circuito che c'è meno replicazione, inoltre ci sono due multiplexer:
1. **Il 1°** è piccolo perchè **decide il primo operando**, che può essere:
	- R-type, load, store
	- Incremento PC
2. **Il 2°** è più grande perchè **deve decidere il secondo operando** che si divide in:
	- costante immediata, registro
	- scrivere/leggere dalla memoria

È importante far notare che **i due mux devono essere sincronizzati** in quanto non possono essere presentati alla ALU prima il risultato di un mux e poi l'altro, questo ci porterebbe solo problemi.
 
### Controllo
Dato che stiamo usando una CPU multiciclo, dobbiamo mandare segnali di controllo adatti ad ogni ciclo.
