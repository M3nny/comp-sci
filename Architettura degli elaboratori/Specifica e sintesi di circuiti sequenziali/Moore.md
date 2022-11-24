Realizzare un circuito che controlla i semafori di un incrocio tra una strada North/South e una East/West.
- **input** sensori che controllano se sono presenti macchine in attesa
- **output**: segnali che determinano l'accensione (rosso/verde) dei semafori

**NScar** e **EWcar** quando sono a $1$ segnalano la presenza di macchine nella relativa strada (north south/east west).
**NSlite** e **EWlite** quando sono a $1$ segnalano che i corrispettivi semafori di quella strada sono verdi.

NSlite e EWlite non possono mai essere accesi/spenti allo stesso momento.

##### Ricavo l'automa
![[Automa Moore.svg]]
Indico con i cerchi i 2 possibili stati dei semafori:
- **NSgreen**: è verde per la strada north/south
- **EWgreen**: è verde per la strada east/west

Se non ci sono macchine in attesa nella strada opposta rimango nello stesso stato.
Se sono presenti macchine in attesa nella strada opposta, allora passo allo dove è verde nella strada opposta.
Indico con x gli input don't care.

##### Realizzo le tabelle di verità
Rappresento gli **stati**
Dato che sono 2, mi basta 1 bit
| **Stato** | **s** |
| --------- | ----- |
| NSgreen   | 0     |
| EWgreen   | 1     |

Rappresento gli **output**
Le combinazioni di valori all'interno dei nodi sono 2 quindi mi basta 1 bit
| **s** | **NSlite** | **EWlite** |
| ----- | ---------- | ---------- |
| 0     | 1          | 0          |
| 1     | 0          | 1          |

##### Realizzo le tabelle di verità per NEXT_STATE
Ora prendendo in considerazioni gli input (frecce entranti in ogni nodo) ne vado a determinare il loro stato successivo.
| **s** | **NScar** | **EWcar** | **s'** |
| ----- | --------- | --------- | ------ |
| 0     | x         | 0         | 0      |
| 0     | x         | 1         | 1      |
| 1     | 0         | x         | 1      |
| 1     | 1         | x         | 0      |

Espandendola diventa
| **s** | **NScar** | **EWcar** | **s'** |
| ----- | --------- | --------- | ------ |
| 0     | 0         | 0         | 0      |
| 0     | 0         | 1         | 1      |
| 0     | 1         | 0         | 0      |
| 0     | 1         | 1         | 1      |
| 1     | 0         | 0         | 1      |
| 1     | 0         | 1         | 1      |
| 1     | 1         | 0         | 0      |
| 1     | 1         | 1         | 0      |

##### Riduco in mintermini con le mappe di Karnaugh
![[Karnaugh Moore.svg]]
s'= $\overline{s}\cdot \text{EWcar}+s\cdot \overline{\text{NScar}}$ 

##### Realizzo il circuito
![[Circuito Moore.png]]