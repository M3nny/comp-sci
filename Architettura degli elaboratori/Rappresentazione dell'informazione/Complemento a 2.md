# Complemento a 2

>[!Example]
>**Rappresentare $-2$ su $3$ bit in complemento a 2 in base 2.**
>Seguiamo la regola generale:
>$$2^n-|N|$$
>quindi:
>$$2^3-2=8-2=6_{10}=110_2$$
>
>**Che valore ha $110_2$ in complemento a 2.**
>Per prima cosa devo guardare se il primo bit è 1(negativo) o 0(positivo), in questo caso è negativo, quindi procedo a fare la conversione da base 2 a base 10 con la differenza che il primo bit non sarà $2^x$ ma $-2^x$.
>$$110=-2^2\cdot 1 + 2^1\cdot 1 + 2^0\cdot 0=4+2=6_{10}$$

### Cambio di segno con compl. a 2
Esistono 2 algoritmi per per trovare l'opposto di un numero in compl. a 2:
1. Eseguo il complemento a 1 e poi sommo 1 al risultato.
2. Inverto tutti i bit a sinistra del bit meno significativo (il bit 1 più a destra).
	- Se ho $1101_2=-3$, allora $0011_2=3$ 
	- **nota**: il cambio di segno non funziona per il negativo più piccolo rappresentabile nel numero di bit a disposizione.

## Estensione dei bit della rappresentazione
Estendo il bit di segno per il restante numero dei bit a disposizione:
>[!Example]
>- 2 con 4 bit: 0010
>- 2 con 8 bit: 0000 0010

>[!Tip]
>Esiste un'operazione su assembler che permette di shiftare i bit:
>$$0001<<1 \rightarrow 0010$$
>- Questo shift moltiplica per 2 se non perdo bit significativi.
>- Se shifto verso destra faccio la divisione per 2, devo stare attento comunque a non perdere bit significativi.
>$$0010>>1 \rightarrow 0001$$

### Addizioni e sottrazioni in complemento a 2
- Gli **overflow** nella somma/sottrazione complemento a 2 **si scoprono in modo diverso**.
- Avviene overflow se sommando 2 positivi ottengo un numero negativo oppure se sommando 2 negativi ottengo un numero positivo.
- Non posso andare in overflow se sommo/sottraggo 0.

|    |   Somma  | Sottrazione |
|----|:--------:|:-----------:|
| ++ | SI(neg.) |      NO     |
| -- | SI(pos.) |      NO     |
| +- |    NO    |   SI(neg.)  |
| -+ |    NO    |   SI(pos.)  |
- È possibile adoperare un'altra regola altrimenti, ovvero: guardo gli ultimi 2 **riporti**
	- Se sono **discordi** allora c'è overflow.
	- Se sono **concordi** <u>non</u> c'è overflow.


