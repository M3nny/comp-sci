Abbandoniamo l'idea di completare l'istruzione in un singolo ciclo di clock.
Ho quindi bisogno di **registri di stato che salvano i risultati parziali di un'istruzione** così da poterla fare continuare nel prossimo ciclo di clock.
Lo stesso per **l'instruction register** che deve essere sempre quello fino a quando è finita l'operazione.

## Sequenza passi (cicli) esecuzione
1. **Fetch istruzione** _e_ **incremento PC**.
2. **Decodifica dell'istruzione** _e_ **leggo i registri** (in parallelo) nel caso servisse ad una istruzione dopo, inoltre **anticipo del lavoro per il branch** in modo tale che se dopo ci sarà una _beq_, essa potrà terminare in un ciclo al posto di impiegarne due
3. **R-type exe** _o_ **calcolo indirizzo memoria** _o_ **completo beq** _o_ **completo jump**
4. **Completo R-type** _o_ **completo store** (**sw**)
5. **Write back**, ovvero scrivo sul registro (**lw**)

>Ogni passo viene eseguito in un ciclo di clock, ogni istruzione impiega da 3 a 5 cicli

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
 
## Controllo
Dato che stiamo usando una CPU multiciclo, dobbiamo mandare segnali di controllo adatti ad ogni ciclo, il **controllo sarà** infatti implementato come **circuito sequenziale** (Moore).

### Segnali di controllo di 1 bit
| **Segnale** | **cosa verifica**                                                                              |
| ----------- | ---------------------------------------------------------------------------------------------- |
| **RegDst**      | chi scrive nel register-type                                                                   |
| **Reg Write**   | se il register file è abilitato alla scrittura                                                 |
| **AluSrcA**     | 1° ingresso ALU (PC, reg. A)                                                                                |
| **MemRead**     | se si può leggere dalla memoria                                                                |
| **MemWrite**    | se si può scrivere in memoria                                                                  |
| **MemtoReg**    | chi scrive nel register file: (ALUOut, MDR)                                                       |
| **IorD**        | che indirizzo portare alla memoria (PC, ALUOut)                                                            |
| **IRWrite**     | se posso scrivere nel registro che indica l'istruzione corrente (viene scritto solo nel fetch) |
| **PCWrite**     | aggiorno il PC (in base al normale PC + 4 oppure in base ad una jump)                          |
| **PCWriteCond** | aggiorno PC perchè beq è vera (zero=1)                                                         |

Praticamente <u>scrivo nel PC quando PCWrite è affermato oppure quando PCWriteCond è affermato</u>: ==PCWrite _or_ (PCWriteCond _and_ Zero)==.

### Segnali di controllo di 2 bit
| **Segnale**  | **Cosa verifica**                             |
| ------------ | --------------------------------------------- |
| **ALUOp**    | Istruzione                                    |
| **ALUSrcB**  | 2° ingresso ALU (reg. B, costante 4 per incrementare PC, costante da estendere segno)                              |
| **PCSource** | cosa viene scritto nel PC (PC + 4, beq, jump) |

>**Nota**: tutti i registri sono da 32 bit.

---
## Passi di esecuzione
Vengono riassunte nella seguente tabella le istruzioni in notazione RTL (Register Transfer Language) per ogni ciclo di clock:

![[Istruzioni RTL.png]]

## Considerazioni sul costo delle istruzioni
Usando una _CPU multiciclo_, le varie istruzioni possono avere diverso **CPI** (Cicli Per Istruzione), la load ad esempio è quella che impiega più tempo.

Sembrerebbe quindi di aver ottenuto un risparmio solo per la _beq_ e la _jump_, questo perchè non abbiamo considerato operazioni molto più costose che ci avrebbero portato ad avere un ciclo di clock molto lungo se dovessimo usare la _CPU a singolo ciclo_.