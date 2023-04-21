.cpu cortex-a53
.text
.p2align 2

.global _start
_start:


    // Il programma calcola il fattoriale di 'a' e scrive il
    // risultato nella variabile 'c'.

    /* Codice C equivalente
        double x1 = 5;
        int x2 = 1;
        while(x1 > 1) {
            x2 *= x1;
            x1--;
        }
        return x2;
    */

    adr x0, a       // x0 = &a
    ldr x1, [x0]    // x1 < mem[x0] (x1 = 5)
    mov x2, #1      // x2 = 1

    cmp x1, #1
    b.le exit         // signed Less or Equal: if (x1 <= 1)

while:
    mul x2,x2,x1    // x2 *= x1
    sub x1, x1, #1  // x1--
    cmp x1, #1
    b.gt while         // signed Greater Than: if (x1 > 1) { rifaccio il ciclo }

exit:
    adr x0, c       // x0 = &c
    str x2, [x0]    // x1 > mem[x0] (c = x2)

    // Fine programma
    mov x0, #3          // Carichiamo il valore di ritorno nel registro x0
    mov x8, #93         // Specifichiamo il numero della syscall in x8
    svc #0              // syscall


// Dati del programma
.data
.p2align 2

a:  .dword 5
c:  .dword 0
