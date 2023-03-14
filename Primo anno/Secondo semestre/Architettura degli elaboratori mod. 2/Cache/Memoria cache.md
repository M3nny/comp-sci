La memoria cache si trova tra la CPU e la RAM, ci riferiamo ad essa come sistema che sfrutta la località degli accessi.

## Cache ad accesso diretto
La funzione di mapping è la seguente: `<address> mod <# blocchi cache>.

Se **#** è il numero di blocchi di cache (potenza di 2) l'operazione modulo è equivalente a prendere i primi $\log_2$ <# blocchi cache> bits dall'indirizzo.

#### Shifting
- **Moltiplicare** per $k=2^n$ equivale a $n$ shift a **sinistra**
- **Dividere** per $k=2^n$ equivale a $n$ shift a **destra**

Gli indirizzi con gli stessi bit meno significativi finiscono nello stesso **cache block**, <u>indirizzamento al blocco invece che al bite</u>:
1. **Block address**: $\frac{\text{address}}{\text{block size}}$
2. **Block index**: $\text{block address}$ % #$\text{cache blocks}$

In pratica se la cache ha _block size_ pari a $1$, e $8$  blocchi, allora dalla memoria indirizziamo al blocco gli indirizzi con gli ultimi $3$ ($8=2^3$) bit significativi con un offset pari a $0$ (avendo _block size_ 1:  $\log_21 = 0$).

Vediamo 2 esempi con lo stesso numero di blocchi di cache, ma che si differenziano nella grandezza di quest'ultimi.

Osserviamo che nel secondo esempio sono raggruppati gli indirizzi che hanno i penultimi $3$ bit significativi, questo è dovuto ad un offset pari a $1$ dato da: $\log_22 = 1$, quindi in questo caso più blocchi di memoria finiscono nella stessa locazione nella cache.

![[Cache accesso diretto.svg]]
### Tag
Per distinguere i valori che finiscono nello stesso blocco di cache **memorizziamo** _i bit più significativi_ del **block address** insieme ai dati, chiamiamo questo tipo di dato **tag**.
- Tag = $\frac{\text{block address}}{\text{n cache blocks}}$
