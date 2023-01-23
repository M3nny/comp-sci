Il termine **Performance** è usato come misura generica della velocità di un computer e come sinonimo di **Throughput**.

Il tempo di esecuzione di un programma può essere diviso in vari modi:
- User CPU time
- System CPU time
- Elapsed time

Noi analizzeremo solo l'user CPU time, ovvero senza considerare eventuali code del OS, momenti morti di I/O da parte dell'utente o altro.

## Performance, Execution time, speedup
- **Performance**: $$\text{Performance} = \frac{1}{Texe_x}$$
- **Speedup**: mettiamo al _numeratore_ il tempo maggiore, e al _denominatore_ il tempo minore, quindi se $X$ è più veloce di $Y$
$$\text{Speedup} = \frac{Texe_y}{Texe_x}$$
## Cicli di clock
Per ottenere **CPU time** devo **moltiplicare** il numero di **cicli di clock** impiegati per eseguire il programma **ed il periodo** $T$ di un ciclo di clock
$$\text{Texe} = n° cicli\cdot T$$
- **Frequenza** (cicli al secondo):
$$\text{Freq} = \frac{1}{T}$$
- **CPI** (cicli per istruzione): ricavati dal rapporto tra $n°cicli$ e $IC$(n° di istruzioni in un programma)
$$\text{CPI} = \frac{n°cicli}{IC}$$
- **MIPS** (milioni di istruzioni per secondo):
$$\text{MIPS} = \frac{IC}{Texe\cdot 10^6}$$
- **Amdahl**:
$$Texe_{after} = \frac{1}{s}\cdot Texe + \frac{(1-\frac{1}{s})\cdot Texe}{n}$$
	$\frac{1}{s}$ = frazione del tempo che usa per fare le cose che non siano da migliorare
	$1-\frac{1}{s}$ = frazione del tempo che usa per fare la cosa che deve migliorare
	$Texe$ = il tempo totale di esecuzione
	$n$ = quanto è più veloce la parte da migliorare
	