## Variabili
Non esiste il concetto di variabile.
La memoria si distingue in:
- **Interna**: registri
- **Esterna**: RAM

Ma <u>i registri sono limitati</u>, quindi la scelta naturale è di mettere queste "variabili" in memoria, non direttamente nei registri.
Occorre specificare la dimensione di ogni tipo di dato prima di allocarlo correttamente in memoria.

Per usare delle variabili è quindi necessario operare sugli indirizzi, dato che non è sempre possibile conoscere l'indirizzo di quest'ultime, vengono usate delle **labels** associate a punti specifici del programma o dati, sarà poi l'assemblatore a convertirle nel loro corrispettivo valore.

### Direttive dell'assemblatore
Le **direttive** sono "comandi" da dare all'assemblatore durante la compilazione, alcune di esse permettono di riservare e inizializzare dello spazio per le variabili.
e.g.: `.word 10, 20, 30` alloca una sequenza di 3 numeri a 4 bit e ci scrive il valore 10, 20, 30

| .float num                  | .ascii str            | .asciiz str                          | .byte n            | .word num                 | .dword num                | .space n |
| --------------------------- | --------------------- | ------------------------------------ | ------------------ | ------------------------- | ------------------------- | -------- |
| inserisce un numero float32 | inserisce una stringa | inserisce una stringa terminata da 0 | inserisce `n` byte | inserisce un numero int32 | inserisce un numero int64 | riserva `n` bytes non inizializzati         |

Grazie all'istruzione [[Istruzioni logico-aritmetiche#Operazioni logico-aritmetiche immediate|adr]] (che usa solo registri da 8 byte `x<n>`) non serve conoscere l'indirizzo che avranno le variabili dopo il linking.

>[!Example]
>**C**
>```c
>int a = 10;
>int b = 20;
>int c = 0;
>c = a + b;
>```
>**ARM**
>```armasm
>.text
>adr x0, a // carica nel registro x0 l'indirizzo di a
>ldr w1, [x0] // carica nel registro w1 il valore di a contenuto all'indirizzo in x0
>adr x0, b // carica in x0 l'indirizzo di b
>ldr w2, [x0] // carica nel registro w2 il valore di b contenuto all'indirizzo in x0
>add w2, w1, w2 // mette dentro al registro w2 il risultato di w1 + w2 (10+20)
>adr x0, c // carica in x0 l'indirizzo di c
>str w2, [x0] // mette il valore dentro al registro w2 nell'indirizzo (c) contenuto dentro il registro x0 
>
>.data 
>a: word 10 // alloco memoria per un int a 32 bit con valore 10 
>b: word 20 // ... 
>c: word 0 // ...
>```

Nel caso di espressioni complesse come
```c
a = b + d + a*3;
b = a * 2;
c = a + a*a;
```

Si può approcciare la soluzioni in 2 modi:
- **Approccio modulare**: si traduce ogni accesso alla variabile con una load e ogni scrittura con una store, semplice ma poco efficiente.
- **Approccio ottimizzato**: si massimizza il numero di variabili mantenute nei registri e si minimizza l'accesso alla memoria/cache.

### Ottimizzazioni del compilatore
Il compilatore evita di copiare dati (variabili) da registri alla memoria se non è necessario, inoltre tiene occupati più registri possibili per memorizzare le variabili.
