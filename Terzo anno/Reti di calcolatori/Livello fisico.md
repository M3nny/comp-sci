Il **bit-rate** rappresenta la velocità di un canale di comunicazione espressa in bit al secondo (bit/s).

Per scoprire <u>cosa influenza il bit-rate</u> di una comunicazione dobbiamo fare qualche menzione di fisica.

## Nozioni di fisica
In fisica il concetto di **lavoro** rappresenta il risultato dell'<u>applicazione di una forza lungo una certa distanza</u>.
>Informalmente è la misura della nostra interazione con un sistema.

Il lavoro può essere visto come un cambiamento di **energia** da parte dell'oggetto che subisce la forza, la forma più semplice di energia è l'**energia cinetica**:
$$KE=\frac{1}{2}mv^2\qquad(\text{m=massa, v=velocità})$$

Come la _forza_ è misurata in _Newtons_ e la _distanza_ in _metri_, l'**energia** è misurata in _Newton-metri_, ovvero **Joule (J)**.

La **potenza** è _energia per secondo_ ed è misurata in _J/s_, ovvero **Watt(W)**, essa rappresenta quanto velocemente un sistema può dare energia.

Un **elettrone** è una particella con _carica negativa_, esso possiede massa, quindi quando si muove ha _energia cinetica_.
Gli elettroni possono muoversi dentro la materia creando **corrente elettrica**, la quale è misurata in _Coulomb/s_, ovvero **Ampere**.
>50mA sono la soglia per cominciare a sentire dolore.

Un **generatore di corrente** "spinge" gli elettroni nel filo, dandogli quindi energia, per accelerare molti elettroni per un certo tempo $t$, il generatore **consuma energia** (potenza).

Quando gli elettroni si muovono in un materiale _rimbalzano_ addosso alla sua struttura perdendo energia, la quale è trasferita al materiale trasformando così l'energia cinetica in **calore**.

È possibile usare uno strumento per capire se c'è corrente nel circuito, lo strumento possiede una **sensibilità**, se la corrente ricevuta è più altra di una certa soglia allora misurerà una certa potenza.

Ora immaginando di inserire uno switch (on/off) nel circuito, e farlo ciclare tra i due stati per $1$ secondo ciascuno otteniamo un **segnale**.

## Attenuazione e rumore
Il filo (di rame) attraverso il quale la corrente passa possiede una resistenza intrinseca che non è mai pari a $0$, per cui parte della potenza è persa nel cavo, più lungo il cavo, maggiore sarà la perdita, chiamiamo questo effetto **attenuazione**.
>Come risultato la forma del segnale è uguale, ma la sua ampiezza è diversa, per questo serve un ricevitore con alta sensibilità.

Gli elettroni o qualsiasi altro mezzo usato per comunicare non viaggiano a velocità infinita, viene quindi introdotta la **latenza**, ovvero il tempo che passa dall'invio del segnale fino a quando comincia ad essere ricevuto.

Gli elettroni non sono mai fermi a temperature normali, quindi anche quando lo switch è su _off_ il sensore misurerà un piccolo segnale casuale, questo è il **rumore termico**.
Ogni comunicazione è composta dal segnale in aggiunta a del rumore (esterno o intrinseco).

La differenza tra segnale e rumore deve essere tale da poter distinguere il primo dal secondo, definiamo quindi il **Signal to Noise Ratio (SNR)**:
$$SNR=\frac{\text{Potenza del segnale ricevuto}}{\text{Potenza del rumore al ricevitore}}$$
Se la potenza ricevuta è maggiore della sensibilità del ricevitore allora la capacità di decodificare correttamente i dati dipende dal SNR.

>[!Info]
>Il SNR è una proprietà del canale di comunicazione, dei suoi estremi e delle condizioni di rumore.
>Maggiore è il SNR, maggiore sarà il bit-rate.

Il mittente ed il destinatario devono accordarsi quando un certo simbolo comincia e finisce, devono quindi essere **sincronizzati** sulla durata di ogni simbolo (generalmente costante).

## Modulazione
In un **segnale modulato** si ha:
- Un **segnale portante**: solitamente una sinusoide con frequenza $f_c$ espressa in _1/s_, ovvero **Hertz**
- Un **segnale modulante**: il segnale da trasportare

L'idea della modulazione è quella di modificare l'ampiezza, frequenza o la fase del portante per codificare l'informazione che rappresenta il segnale modulante ottenendo quindi un **segnale modulato**.

>[!Example]
>Abbiamo un portante $p(t)=A\cdot\cos(2\pi f_pt)$ ed un segnale digitale $m(t)$ da trasmettere.
>Possiamo modificare la frequenza del portante incrementandola di un valore $\Delta$:
>$$\begin{cases}f_p'=f_p&\text{se }m(t)=0\\f_p'=f_p(1+\Delta)&\text{se }m(t)=1\end{cases}$$
>Ciò rende possibile comunicare un segnale binario usando due livelli per il segnale digitale.

![[FM.png]]

In un circuito possiamo sostituire un generatore di corrente continua con un generatore di corrente alternata così da creare un segnale portante.
>Nelle comunicazione wireless al suo posto c'è un'onda elettromagnetica che oscilla fornendo un segnale portante.

>[!Example]
>Immaginiamo di avere $f_p=4$, ovvero $4$ oscillazioni al secondo, e assumiamo che la lunghezza di un bit sia determinata da $4$ oscillazioni, questo è un **simbolo**.
>Mandiamo un simbolo al secondo, ciò rappresenta il **Baud rate (Bd)**, ogni simbolo rappresenta un bit: il bit-rate è $1 b/s$.
>$$\text{bit-rate}=\text{Baud rate}\cdot \text{bit per symbol}$$

Vediamo ora come <u>aumentare il bit-rate</u>.
#### Ridurre la durata del simbolo
Utilizzando l'esempio precedente mandiamo 1 simbolo al secondo il quale è direttamente collegato al bit-rate, per aumentare quest'ultimo potremmo aumentare il baud rate mandando per esempio 1.5 simboli al secondo.
- Più lungo è il simbolo più facile è per il ricevitore distinguerlo
- Se il simbolo è corto potrebbe essere difficile decodificarlo correttamente in canali rumorosi

#### Codificare più di un bit in ogni simbolo
Per codificare più bit è possibile aumentare il numero di frequenze, ad esempio con $M=4$ frequenze otteniamo:
$$\begin{cases}f_p'=f_p&\text{se }m(t)=00\\f_p'=f_p(1+\Delta)&\text{se }m(t)=01\\f_p'=f_p(1+2\Delta)&\text{se }m(t)=10\\f_p'=f_p(1+3\Delta)&\text{se }m(t)=11\end{cases}$$
Ora il Baud rate è lo stesso dell'esempio originale, con la differenza che ogni simbolo trasporta 2 bit incrementando quindi il bit-rate.
Idealmente possiamo codificare un numero arbitrario di bit finchè il ricevitore riesce a distinguere le frequenze.
![[FM 2 bit.png]]

La **larghezza di banda** rappresenta l'intervallo tra la frequenza più bassa e più alta usata usata nelle comunicazioni.

>[!Attention]
>Incrementando la larghezza di banda si incrementa il bit-rate, tuttavia le frequenze sono soggette a limitazioni hardware e legislative.

---
## Teoremi fondamentali
### Teorema di Nyquist
Se una comunicazione utilizza una larghezza di banda $B$ e $M$ livelli discreti (solitamente una potenza di $2$), allora la **capacità massima teorica** della trasmissione in _bit/s_ è:
$$C=2B\log_2(M)$$

>[!Example]
>Un collegamento usa frequenze che vanno dai $2401$ MHz ai $2441$ MHz e usa $M=4$ livelli, quale è il bit-rate massimo?
>$$C=2\cdot (2441\cdot 10^6-2401\cdot 10^6)\cdot\log_2(4)=160Mb/s$$
>---
>Un collegamento usa frequenze che vanno dai $2401$ MHz ai $2441$ MHz e supporta $300$ Mb/s, quale è il numero minimo di livelli $M$?
>$$C=2\cdot (40\cdot 10^6)\log_2(M)>300\cdot 10^6$$
>$$M>2^{\frac{300}{80}}=13.45$$
>
>Dato che $M$ deve essere una potenza di $2$ lo impostiamo a $M=16$, per avere $300Mb/s$ bisogna poter fornire $320Mb/s$.

### Teorema di Shannon
La capacità di un canale con larghezza di banda $B$ con un _gaussian white noise_ aggiunto è data da:
$$C=B\log_2\left(1+\frac{S}{N}\right)$$
>Dove $\frac{S}{N}$ è il _Signal to Noise Ratio_.

Non importa quanto forte è il segnale, dipende sempre dal SNR, inoltre la capacità cresce lentamente a causa del $\log_2$, per aumentarla bisognerà incrementare il SNR di qualche potenza di $2$.

#### Confronto tra i teoremi
Nyquist opera in un mondo ideale senza rumore dove il ricevitore è perfetto, quindi ogni segnale con potenza > 0 è ricevuto.

Shannon è più stretto, dice che dato un certo SNR ed una certa $B$, non si può ottenere più di $C$ anche se Nyquist lo consente, praticamente non è possibile avere un numero arbitrario di livelli dato un certo SNR in quanto quest'ultimo determina il numero massimo di livelli.
>Notare come $B, S, N$ sono legati al collegamento, ma il trasmettitore può scegliere $M$, dovrà però valere $C_N\leq C_S$.

>[!Example]
>Una ADSL può essere descritta da:
>- Potenza di trasmissione del router: $100mW=10^{-3}W$
>- Rumore: $0.0001mW$
>- Attenuazione: la potenza è divisa di $25$ ad ogni $km$
>- Larghezza di banda: $2.2MHz$
>
>Quale è il massimo bit-rate ottenibile a $2km$ considerando il rumore?
>La potenza dopo $2km$ è $\frac{100}{25^2}=0.16mW$, per cui applicando Shannon:
>$$C_S=2.2\cdot 10^6\cdot\log_2(1+\frac{0.16}{0.0001})\simeq 23Mb/s$$
>---
>Quale è la migliore modulazione che possiamo usare? (valore più alto di $M$)
>Ci ricaviamo questo dato utilizzando Nyquist ponendo:
>$$2B\log_2(M)\leq C_S\implies M=2^{\frac{C_S}{2B}}$$
>$$M=2^{\lfloor\frac{23\cdot 10^6}{2\cdot 2.2\cdot 10^6}\rfloor}=2^{\lfloor 5.227\rfloor}=32$$
>---
>Quale è il bit-rate massimo ottenibile con la precedente modulazione?
>$$C_N=2B\log_2(M)=2\cdot (2.2\cdot 10^6)\cdot \log_2(32)=22Mbit/s<C_S$$
>---
>Immaginando di prendere la potenza successiva di $2$ durante la scelta della modulazione, e quindi prendere $2^6$, otterremmo $C_N=26.4Mb/s$, però dalla formula di Shannon sappiamo che il bit-rate massimo è $23Mb/s$, questo vuol dire che in media $3.4Mb/s$ del traffico conterrà errori, dovremmo quindi ritrasmettere questi bit riducendo così il bit-rate utile.

Non ha senso trasmettere ad una velocità maggiore di quella consentita da Shannon, $M$ deve essere scelto in modo tale che il **limite dato da Nyquist** ($C_N$) sia **minore o uguale** a quello imposto da **Shannon** ($C_S$).

