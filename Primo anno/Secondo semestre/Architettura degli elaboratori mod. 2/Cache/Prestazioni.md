$$\text{CPU time} = \text{(execution cycle + stall cycles)} \cdot  \text{cycle time}$$$$\text{Stall cycles} = \text{IC} \cdot \text{miss ratio} \cdot  \text{miss penalty}$$

Dove (IC $\cdot$  miss ratio) è il numero di istruzioni che provocano miss.
Nel nostro caso ipotizziamo che la miss penalty sia applicata la massimo una volta per `lw/sw`, cosa che nella realtà non è vera perchè potrebbero esserci miss sia nel `fetch` e sia nella lettura/scrittura.

Dividiamo appunto il miss ratio in:
- **Instruction miss ratio** dovuto al `fetch`
- **Data miss ratio** dovuto a `sw/lw`

Per aumentare le prestazioni possiamo:
- Ridurre il miss ratio e/o ridurre il miss penalty

>[!Example]
>Assumiamo di avere un programma che ha:
>- Instruction miss ratio = 2%
>- Data miss ratio = 4%
>- Numero `lw/sw` = 36% IC
>- CPI ideale = 2
>- Miss penalty = 40 cicli di clock
>
>**Stall cycles**:
>- Istruzioni: IC $\cdot$ 0.02 $\cdot$ 40 = 0.8 $\cdot$ IC
>- Dati: (IC $\cdot$ 0.36) $\cdot$ 0.04 $\cdot$ 40 = 0.58 $\cdot$ IC
>- Totali: 0.8 + 0.58 = 1.38 $\cdot$ IC
>
>I cicli di stallo medi per istruzione sono dati da: $\frac{1.38 \text{IC}}{\text{IC}} = 1.38$
>Il **CPI reale** è dato dal CPI ideale + cicli di stallo medi per istruzione: 2 + 1.38 = 3.38, mentre lo **speedup** della CPU ideale è pari a $\frac{3.38}{2}=1.69$


Con una CPU più veloce il tempo assoluto della penalty, il miss ratio e l'IC rimarrebbero invariati, mentre dipenderebbe dalla CPU il miss penalty ed il CPI ideale.

**Conclusione**: la memoria ha un forte impatto sulle prestazioni di un sistema.