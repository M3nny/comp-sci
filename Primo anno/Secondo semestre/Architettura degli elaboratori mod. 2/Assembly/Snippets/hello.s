.cpu cortex-a53 // specificare la cpu fa ottimizzare meglio le istruzioni all'assemblatore
.text
.p2align 2 // l'accesso a indirizzi allineati può richiedere meno cicli di clock

.global _start
_start:
    mov x0, #1          // Carichiamo il descrittore file che definisce lo standard output in x0
    adr x1, hellostring // Carichiamo in x1 l'indirizzo di hellostring
    mov x2, #12         // Carichiamo in x2 il numero di bytes (caratteri) da scrivere
    mov x8, #64         // specifichiamo il numero di syscall in x8
    svc #0              // syscall

    // Fine programma
    mov x0, #3          // Carichiamo il valore di ritorno nel registro x0
    mov x8, #93         // Specifichiamo il numero della syscall in x8
    svc #0              // syscall


// Dati del programma
.data
.p2align 2

.global hellostring
    hellostring: .asciz "hello world\n" // .asciz a differenza di .ascii aggiunge uno 0 alla fine della stringa
