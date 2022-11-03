L'**Arithmetic Logic Unit** all'interno del processore esegue istruzioni macchina aritmetico/logiche, quindi è in grado di eseguire:
- Somme (add);
- Sottrazioni (sub);
- Istruzioni di confronto (slt, beq, bne);
- Funzioni logiche (and, or);

## Addizionatore
Per evitare un'arietà delle porte elevata utiliziamo una serie di **1-bit adder**, dove il segnale deve attraversare più livelli di logica.
![[Addizionatore.png|400]]
- **A e B**: i due operandi;
- **Rip**: il riporto già presente in memoria (da una possibile somma precedente);
- **Sum**: il risultato;
- **Rip_out**: il possibile resto generato dalla somma di A,B e Rip.

L'addizionatore <u>non può essere semplificato</u>, dovremmo usare 4 porte AND.
Andiamo quindi a sostituire le porte AND con delle porte **XOR**

>[!Info]
>Tabella di verità della funzione XOR
>
>| **A** | **B** | **XOR** |
|:-----:|:-----:|:-------:|
|  _0_  |  _0_  |   _0_   |
|  _0_  |  _1_  |   _1_   |
|  _1_  |  _0_  |   _1_   |
|  _1_  |  _1_  |   _0_   |

Come possiamo notare il risultato dello **XOR** è anche il risultato della funzione **add**, andiamo quindi a calcolare con questa porta logica Sum e Rip_out:
- **Sum** = (A _xor_ B) _xor_ Rip
- **Rip_out** = AB + (A _xor_ B) Rip
![[1-bit adder.png|300]]
## 1-bit ALU
È utilizzata per eseguire le seguenti istruzioni:
- and
- or
- add
Funziona grazie ad un multiplexer **Operation** che è un segnale di controllo a 2 bit (vengono usati 2 bit perchè le operazioni in questione tra cui scegliere sono 3), usato per selezionare quale delle tre istruzioni vogliamo eseguire.
![[1-bit ALU.png|300]]

### 32-bit ALU
Formata da una catena di **1-bit ALU** con propagazione del riporto all'ALU successiva, il segnale **Operation** è necessariamente uguale per tutte le ALU da 1 bit, appunto perchè vogliamo eseguire sempre la stessa operazione.

### Inversione e sottrazione
La 1-bit ALU precedente può essere resa può complessa aggiungendo anche l'istruzione **sub**, la quale verrà trasformata in una somma: 
``` r
$2 = $3 + $(-$4)
```
Quindi per eseguire la sottrazione, sapendo che il calcolatore userà il complemento a 2, dovremmo seguire quest'ordine:
1. Ottengo l'opposto:
	1. Complemento a 1;
	2. Sommo 1;
2. Eseguo la somma.
La sottrazione nel circuito avverà quando il segnale **Binvert** sarà uguale a **1**, e dopo aver invertito il segno avverà nello stesso modo della somma.
![[Sottrazione 1-bit ALU.png|300]]


