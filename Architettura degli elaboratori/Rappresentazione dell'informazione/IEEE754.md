# Lo standard IEEE754
Questo metodo ha due rappresentazioni:
- Singola precisione (32 bit).
- Doppia precisione (64 bit).

Questo standard utilizza una _notazione scientifica normalizzata_ dove $d_0 = 1$.
>[!Example]
>- $0.1101\cdot 2^7$ non è normalizzato.
>- $1.101\cdot 2^6$ è normalizzato perchè ci siamo ricondotti ad un forma dove $d_0$ è uguale a 1.

Tenendo sempre $d_0$ (numero a sx della virgola) possiamo anche fare a meno di rappresentarlo perchè <u>lo diamo per scontato</u>, in questo modo <u>risparmiamo 1 bit</u> che possiamo usare per rappresentare una mantissa più lunga e più precisa.

Utilizzando questo standard siamo in grado di capire subito:
- Segno del numero espresso in binario.
- Quanto è grande un numero rispetto ad un altro, confrontando il valore assoluto dell'esponente.

Per semplificare il confronto tra rappresentazioni binarie, questo standard si prefissa di voler rappresentare l'**esponente più negativo** con una serie di $00...0_2$ mentre l'**esponente più positivo** come una serie di $11...1_2$, per fare questo utilizzeremo la _notazione polarizzata_.

## Notazione polarizzata
Polarizzazione:
- Singola precisione: $127=01111111_2$.
- Doppia precisione: $1023=01111111111_2$.

La polarizzazione va **aggiunta** all'esponente che vogliamo rappresentare.
>[!Example]
>Esprimere i seguenti numeri con lo standard IEEE754
>- $-125_{10} \quad \rightarrow \quad -125+127=2=00000010_2$
>- $0_{10} \quad \rightarrow \quad 0+127=127=01111111_2$
>- $+125_{10} \quad \rightarrow \quad 125+127=252=11111100_2$

Per ottenere un numero dalla notazione polarizzata dovremmo quindi fare il procedimento inverso e usare la seguente formula:
$$(-1)^s\cdot(1+m)\cdot 2^{e-\text{polarizzazione}}$$
- L'esponente $11...1_2$ è riservato per casi particolari come: numeri non rappresentabili, infinito, NaN.

>[!Example]
>**Rappresentare il seguente numero in notazione scientifica polarizzata IEEE754:**
>$$-0.25_{10}$$
>
>$-0.25_{10} = -0.01_2 \quad \rightarrow \quad 1.0\cdot 2^{-2}$
>
>Procedo andando a trovare segno, esponente e mantissa:
>- **S**$=1$
>- **E**$=-2+127=125_{10}=01111101_2$
>- **M**$=1.0=(1+0.0)$
>
>Sono ora in grado di rappresentare il numero:
>$$1|01111101|000..0$$
>
>**Rappresentare in forma decimale il seguente numero rappresentato in notazione scientifica polarizzata IEEE754:**
>$$1|00001011|01000..0$$
>
>- **S**$=1$
>- **E**$=11-127=-116$
>- **M**$=1+0.01=1.01$
>
>Sono ora in grado di ricostruire il numero decimale:
>$$(-1)^1\cdot 2^{-116}\cdot 1.01=-2^{-116}\cdot 1.25$$

## Somma di numeri FP
Per eseguire la somma tra numeri a virgola mobile devo prima assicurarmi che entrambi siano positivi e che abbiano lo stesso esponente (<u>quello più piccolo allineato a quello più grande</u>) e poi procedo come una normale somma.

>[!Example]
>**Esegui la somma dei seguenti numeri:**
>$$5_{10} \quad 3.625_{10}$$
>
>- $5_{10}=101_2=1.01\cdot 2^2$
>- $3.625_{10}=11.101_2=1.1101\cdot 2^1$
>
>Allineo l'esponente più piccolo a quello più grande:
>
>**Shifting**:  $1.1101\cdot 2^1 = 0.11101\cdot 2^2$
>
>Ora posso sommare normalmente i due numeri:
>
>![[SommaFP.svg]]
>
>**Normalizzazione**: $1.000101\cdot 2^3$
>**Arrotondamento a 4 bit dopo la virgola**: $1.0001\cdot 2^3$
>>[!Attention]
>>In questo caso l'**arrotondamento avviene per difetto** perchè dopo il quarto bit dopo la virgola trovo uno $0$, se avessi trovato un $1$ avrei arrotondato per eccesso nel seguente modo:
>>$$1.001$$

## Problemi di rappresentazione dei numeri FP
Per colpa del numero limitato di bit utilizzato in una rappresentazione, ci potrebbero essere errori di rappresentazione, per cui <u>la proprietà associativa non funzionerà in tutti i casi</u> (su MIPS e ARM posso sommare solo 2 numeri alla volta).
Infatti **allineando l'esponente più piccolo a quello più grande potrei perdere l'informazione** dato che potrebbe non essere rappresentabile in uno spazio limitato di bit.

Ad esempio:
- $x=1.5\cdot 10^{38}$
- $y=1.0_{10}$

Allineando $y$ a $x$ perdo l'$1$ perchè viene spostato troppo.