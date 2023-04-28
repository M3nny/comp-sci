.cpu cortex-a53
.text
.p2align 2

.global _start
_start:

    // Il programma calcola il numero di zeri contenuti
    // nell'array A e ritorna il risultato nella variabile r.
    // La variabile n contiene il numero di elementi di A.

    adr x0, A // x0 = &A
    adr x1, n // x1 = &n
    ldr x1, [x1] // x1 < mem[x1] (x1 = 13)

    mov x3, #0 // x3 = 0 (tiene il conto delgi zeri presenti)

    // Inizializzazione for
    mov x2, #0 // x2 = 0 (int i = 0)
    cmp x2,x1
    b.ge exitfor // if (x2 >= x1) { non eseguo il ciclo }

initfor:
    add x4, x0, x2, LSL #2  // x4 = A[x2]
    ldr w5, [x4]            // w5 = A[x2]
    cmp w5, #0
    b.ne forinc             // if (w5 != 0) { goto forinc }
    add x3,x3,#1            // x3++ (zero trovato)
forinc:
    add x2,x2,#1            // x2++ (incremento l'indice)
    cmp x2,x1
    b.lt initfor            // if(x2 < x1) { goto initfor }
exitfor:
    adr x4, r               // x4 = &r
    str x3, [x4]            // r = x3

    // Fine programma
    mov x0, #3          // Carichiamo il valore di ritorno nel registro x0
    mov x8, #93         // Specifichiamo il numero della syscall in x8
    svc #0              // syscall


// Dati del programma
.data
.p2align 2

A:  .word 0,2,3,0,0,6,7,0,9,10,0,0,0     // int A[13]
n:  .dword 13                            // numero di elementi di A
r:  .dword 0                             // variabile utilizzata per memorizzare il risultato
