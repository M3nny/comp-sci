# Rappresentazione dell'informazione
Le informazioni all'interno del computer devono essere **rappresentate** secondo delle convenzioni comuni, per fare questo dobbiamo prima distinguere:
- **simbolo** che rappresenta l'informazione
- **valore** che corrisponde al significato dell'informazione

Quindi per **codificare** l'informazione avremmo bisogno di un alfabeto di simboli <u>finito</u>, nel caso del computer useremo i simboli $\{0,1 \}$ , i quali sono associati a segnali elettrici differenti.

>[!INFO]
>Una **codifica** fornisce corrispondenza tra **sequenze** di simboli ed i **dati**.


Con un alfabeto di $N$ simboli e sequenze di lunghezza $k$, avrò: $N^{k}$ combinazioni.

Esistono 2 tipi generali di codifiche:
- **Non numeriche**: effettuate in maniera semi arbitraria, dato che basta fissare uno standard comune come  il <u>codice ASCII</u>
- **Numeriche**: devono essere più accurate in quanto devono avvenire delle operazioni con la rappresentazione in uso

## Conversioni

### Binario$_2$ $\rightarrow$ Decimale$_{10}$
>[!example]
>$1011101_2 = 2^0 \cdot 1 + 2^1 \cdot 0 + 2^2 \cdot 1 + 2^3 \cdot 1 + 2^4 \cdot 1 + 2^5 \cdot 0 + 2^6 \cdot 1 = 1+4+8+16+64=93$ 
>$140_5 = 5^0 \cdot 0 + 5^1 \cdot 4 + 5^2 \cdot 1 = 0+20+25 = 45$

### Decimale$_{10}$ $\rightarrow$ Binario$_2$
Si procede per divisioni intere successive.

>[!Example]
>Convertiamo $25_{10}$ in base binaria
>![[Dec_Bin.svg]]


### Binario$_2$ $\rightarrow$ Ottale$_8$
Raggruppiamo per 3 le cifre binarie da destra (3 perchè la base ottale è uguale a $2^3$).

>[!Example]
>Convertiamo $1011010101_2$ in base ottale
>![[Bin_Oct.svg]]
>Dopo aver convertito in binario i gruppetti da 3 li mettiamo assieme, per trovare la conversione, ovvero:
>$$1325_8$$

### Binario$_2$ $\rightarrow$ Esadecimale$_{16}$
In questo caso basta raggruppare le cifre binare in gruppi da 4 al posto di tre come nella conversione ottale, questo perchè stiamo convertendo nella base $2^{4}$.

>[!Example]
>Convertiamo $1001011111_2$ in base esadecimale
>![[Bin_Hex.svg]]
>Dopo aver fatto la conversione dei singoli gruppetti da 4 bit, li mettiamo assieme per trovare:
>$$25F_{16}$$

## Operazioni con i numeri binari

### Somma
- È possibile che si verifichi l'**overflow**, ovvero che la somma non è rappresentabile in un numero $x$ finito di bit.
![[Somma_bin.png]]
### Sottrazione
- Per eseguire la sottrazione, è possibile che il numero diventi negativo, per questo esistono diversi tipi di rappresentazioni dei numeri
|                             Modulo e segno                            |                 Complemento a 1                |                          Complemento a 2                          |
|:---------------------------------------------------------------------:|:----------------------------------------------:|:-----------------------------------------------------------------:|
| Viene utilizzato il primo bit per rappresentare il segno: 0 = + 1 = - | Inverto i bit per indicare il numero negativo. | Eseguo il complemento a 1 e successivamente sommo 1 al risultato. |
### Caratteristiche delle rappresentazioni
- **Bilanciamento**: nel caso del <u>complemento a 2</u>, si ha uno sbilanciamento di numeri negativi rispetto a quelli positivi.
- **Numero di zeri**: Esistono 2 modi di rappresentare lo 0 nella rappresentazione <u>M.e.S.</u>
- **Semplicità delle operazioni**: per <u>M.e.S.</u> è complicato capire se bisogna sottrarre o sommare dato che bisogna capire quale è il segno dei moduli.





