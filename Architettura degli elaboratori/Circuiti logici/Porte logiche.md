I computer operano con segnali elettrici che **lavorano con valori discreti**:
- **True** (1 o asserted) $\rightarrow$ high;
- **False** (0 o deasserted) $\rightarrow$ low.

Grazie a queste porte logiche possiamo creare dei circuiti:
- **Circuito combinatorio**: _senza_ elementi di memoria;
- **Circuito sequenziale**: l'output _dipende_ anche dallo stato della memoria

## Tabelle di verità
Dati $n$ bit di input, il <u>numero delle configurazioni possibili</u> sarà uguale a $2^n$.
Gli input vengono poi combinati tramite le operazioni di somma, prodotto e inversione:

- **A$\cdot$B** = AND
- **A+B** = OR
- **~A** = NOT
![[Porte logiche.png]]

## Proprietà dell'algebra di Boole
|   **Proprietà**  |                   **OR**                  |                   **AND**                   |
|:------------:|:-------------------------------------:|:---------------------------------------:|
|   **Identità**   |                 A+0=A                 |               A $\cdot$ 1=A               |
|     **Nullo**    |                 A+1=1                 |               A $\cdot$ 0=0               |
|  **Idempotente** |                 A+A=A                 |               A$\cdot$A=A               |
|    **Inverso**   |                A+(~A)=1               |              A$\cdot$(~A)=0             |
|  **Commutativa** |                A+B=B+A                |           A$\cdot$B=B$\cdot$A           |
|  **Associativa** |            A+(B+C)=(A+B)+C            | A$\cdot$(B$\cdot$C)=(A$\cdot$B)$\cdot$C |
| **Distributiva** | A$\cdot$(B+C)=(A$\cdot$B)+(A$\cdot$C) |     A+(B$\cdot$C)=(A+B)$\cdot$(A+C)     |
|   **De Morgan**  |         ~(A+B)=(~A)$\cdot$(~B)        |          ~(A$\cdot$B)=(~A)+(~B)         |

### Operazioni NAND e NOR
Le porte logiche **NAND** ($\overline{A\cdot D}$) e **NOR**($\overline{A+B}$) sono considerate **universali** in quanto <u>utilizzando solo una o l'altra è possibile creare qualsiasi tipo di circuito</u>.

## Porte logiche implementate attraverso transistor
Questa parte riguardante i transistor non verrà approfondita durante questo corso.
Viene utilizzata la tecnologia **CMOS**(Complementary Metal Oxide Semiconductor) per realizzare i transistor e si dividono principalmente in due tipi:
- **NMOS**:
	- Con voltaggio **alto** (Vdd) fa passare la corrente;
	- Con voltaggio **basso** (GND) interrompe la conduzione.
- **PMOS**:
	- Con voltaggio **alto** (Vdd) interrompe la conduzione;
	- Con voltaggio **basso** (GND) fa passare la corrente.

---
## Forme canoniche
Ogni funzione può essere rappresentata attraverso una _tabella di verità_ oppure una **equazione** che può essere riportata in **forma canonica** tramite l'uso dei soli operatori AND, OR e NOT.

### SP (Somma di prodotti)
Per ogni output uguale a $1$ **genera un prodotto** (_mintermine_) degli input, dove gli input a $0$ appaiono negati.
>[!Example]
>Considerando la seguente tabella di verità che ha come output **D**:
>
>| **A** | **B** | **C** | **D** |
|:-----:|:-----:|:-----:|-------|
|   0   |   0   |   1   |  _1_  |
|   0   |   1   |   0   |  _0_  |
|   1   |   1   |   0   |  _1_  |
>
>Scriveremo l'equazione in forma canonica **SP** nel seguente modo:
>$$E=(\overline{AB}C)+(AB\overline{C})$$

### Prodotto di somme
Per ogni output uguale a $0$ **genera una somma** (_maxtermine_) degli input, dove gli input a $1$ appaiono negati.
>[!Example]
>Considerando la seguente tabella di verità che ha come output **D**:
>
>| **A** | **B** | **C** | **D** |
|:-----:|:-----:|:-----:|-------|
|   0   |   0   |   0  |  _0_  |
|   0   |   0   |   1   |  _1_  |
|   0   |   1   |   0   |  _0_  |
|   1   |   1   |   0   |  _1_  |
>
>Scriveremo l'equazione in forma canonica **PS** nel seguente modo:
>$$E= (A+B+C)\cdot(A+\overline{B}+C)$$

### 2-level logic
Per realizzare un circuito efficiente possiamo usare la **2-level logic** che ci permette di usare:
- **1° livello di porte AND** per i prodotti, che avrà **_arietà** (fan-in o numero di ingressi)_ per ogni porta pari al numero di fattori dei prodotti;
- **2° livello di porte OR** per la somma, che avrà **_arietà_** pari al numero dei prodotti.
![[2-level logic.png]]
