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
| $a_{31}$ | $a_{30}$ | ... | $a_0$ |
| -------- | -------- | --- | ----- |

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
### Implementazione del NOR
Per implementare la porta NOR, utilizziamo le leggi di de Morgan in modo tale da sfruttare al meglio gli ingressi che abbiamo di già, senza dover aggiungere una porta NOR a sè stante, per farlo aggiungiamo un **Ainvert** come nel caso di B, quindi:
- a NOR b diventerà NOT (a + b) che a sua volta sarà (NOT a) AND (NOT b)

Otteniamo quindi una tabella con il NOR aggiunto:
| **Ainvert** | **Binvert** | **Operation** | **Istruzione** |
|:-------:|:-------:|:---------:|:----------:|
|    0    |    0    |    00     |    and     |
|    0    |    0    |    01     |     or     |
|    0    |    0    |    10     |    sum     |
|    0    |    1    |    10     |    sub     |
|    1    |    1    |    00     |    nor     |

### Istruzioni di confronto
Nella nostra ALU, l'operatore **slt** (set less than) viene realizzato tramite i seguenti passaggi:
1. Sottraggo l'ingresso **a** a **b**
2. Se non è presente overflow durante la sottrazione:
	- Il valore del **bit di segno** del risultato è **assegnato al bit meno significativo** (dei 32 bit del registro), tutti **gli altri sono posti a 0**.
3. Il risultato sarà quindi **1** se **a** è <u>minore</u>, mentre sarà **0** se **a** è <u>maggiore</u>. 

Questo comporta un ingresso in più da parte di tutte le 1 bit ALU, ovvero l'input **Less** che è un flag che viene posto a 0 o 1 in base al risultato dell'istruzione **slt**.

### 1 bit ALU per il bit più significativo
Questo tipo di ALU che determina la cifra più significativa è più complessa dato che:
- Controlla **overflow**, eseguito sulla base di:
	- Tipo di operazione
	- Segni degli operandi
	- Segno del risultato
- Fornisce come ulteriore output il segno del risultato della sottrazione (**Set**) che permetterà l'implementazione di **slt**
- **Set** deve essere ridiretto verso la 1 bit ALU che fornirà in output il bit meno significativo del risultato

### ALU complessiva
Otteniamo quindi una tabella di verità complessiva come segue:
![[ALU complessiva.svg|400]]

![[Tabella ALU complessiva.png|500]]
Il circuito proposto però, utilizzato nell'ultima 1 bit ALU della catena potrebbe non funzionare per **slt** nel caso di **overflow** (avvenuto nella sottrazione per eseguire slt stesso).
Dobbiamo quindi realizzare un circuito apposito per l'istruzione **slt**, per cui il valore **Set** deve essere determinato evitando overflow, quindi:
- Se $a \geq b$ e $b < 0$ allora di sicuro $a>b$ e possiamo porre direttamente **Set = 0**
- Se $a<b$ e $b\geq 0$ allora di sicuro $a<b$ e possiamo porre direttamente **Set=1**
- Se $a>0$ e $b>0$ oppure se $a<0$ e $b<0$ allora possiamo considerare il risultato della sottrazione perchè non potrà andare in overflow e possiamo quindi porre **Set=$res_{31}$** , dove $res_{31}$ è il bit meno significativo che conterrà il bit di segno.
| $a_{31}$ | $b_{31}$ | $res_{31}$ | **Set** |
| -------- | -------- | ---------- | ------- |
| 0        | 0        | 0          | 0       |
| 0        | 0        | 1          | 1       |
| 1        | 1        | 0          | 0       |
| 1        | 1        | 1          | 1       |
| 0        | 1        | X          | 0       |
| 1        | 0        | X          | 1       |

## ALU finale
Nell'ALU finalizzata, non terremo più **Binvert** e _CarryIn_ in quanto avevano sempre lo stesso valore assieme, li sostituiamo con **Bnegate**.

L'ALU è anche stata migliorata ulteriormente in modo tale da consentire le operazioni:
- **beq**
- **bne**
Questo grazie allo **Zero** prodotto dall'ALU, che è in grado di capire se **A** e **B** sono uguali o meno.
Otteniamo alla fine una tabella di verità come segue:
| **Anegate** | **Bnegate** | **Operation** | **Istruzione** |
| ----------- | ----------- | ------------- | -------------- |
| 0           | 0           | 00            | AND            |
| 0           | 0           | 01            | OR             |
| 0           | 0           | 10            | ADD            |
| 0           | 1           | 10            | SUB            |
| 0           | 1           | 11            | SLT            |
| 1           | 1           | 00            | NOR

### Approfondimento: ALU e somma veloce
- L'ingresso _CarryIn_ di ogni 1-bit adder dipende dal valore calcolato precedentemente
- Il bit più significativo della somma deve attendere che tutta la somma sia eseguita (lento)

Si usa il metodo del **Carry Lookahead** per fare passare il segnale per un numero minore di porte per anticipare il riporto.

>[!Tip] Domande esame
>- Come viene realizzaata l'operazione **slt** dall'ALU?
>- Come viene eseguita una somma?
>- Come funziona un sommatore? (sapere il circuito che è l'unico che può chiedere)
>- Come è composta una 32-bit ALU?

