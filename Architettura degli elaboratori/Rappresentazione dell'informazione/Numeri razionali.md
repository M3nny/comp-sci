# Numeri razionali con virgola

## Virgola fissa (fixed point)
Per convertire da base 10 a base 2 un numero, razionale con la virgola:
- Per la **parte intera** procediamo con le **divisioni**.
- Per la **parte decimale** procediamo con le **moltiplicazioni** per 2.
>[!Example]
>$2.75_{10} \rightarrow ?_2$
>1. Converto 2 in binario quindi $2_{10} = 10_{2}$
>2. Converto la parte decimale in binario:
>	Per farlo moltiplico la parte decimale per 2 e prendo per buono la parte a sinistra della virgola, e moltiplico ancora la parte a destra della virgola per 2 finchè non ottengo 1.0
>
>$$0.75\cdot 2 = 1.5 \quad d_{-1}=1$$
>$$0.5\cdot 2 = 1.0 \quad d_{-2}=1$$
>
>In questo caso il risultato della virgola lo leggo nell'ordine in cui è venuto fuori, non al contrario come per la parte intera convertita, quindi:
>$$2.75_{10} \rightarrow 10.11_2$$

- I numeri razionali a virgola fissa <u>sono limitanti</u> quando devo rappresentare un numero tanto grande o tanto piccolo.

## Virgola mobile (floating point)
Per rappresentare i numeri a virgola mobile utilizziamo la notazione scientifica, utilizzando **segno, esponente e mantissa**.

>[!Example]
>$$0.40625_{10} \rightarrow 0.01101_2$$
>Normalizzando il numero in notazione scientifica scriveremo:
>$$1.101_2 \cdot 2^{-2}$$
>L'esponente in questo caso sarà 2 dato che siamo in base 2, se fossimo stati in base 10 avremmo usato $10^x$.

- 1 bit per il segno.
- x bit per l'esponente, aumentano l'intervallo di numeri rappresentabili.
- x bit per la mantissa, forniscono accuratezza.

- **Overflow**: si verifica quando l'esponente è <u>troppo grande</u> per essere rappresentato.
- **Underflow**: si verifica quando l'esponente è <u>troppo piccolo</u> per essere rappresentato.

**Nota**:
I casi di _overflow_ e _underflow_ sono legati all'esponente e non al troncamento della mantissa.


