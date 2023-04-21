.cpu cortex-a53
.text
.p2align 2

.global _start
_start:
    adr x0, a       // x0 = &a
    ldr w1, [x0]    // w1 < mem[x0] (w1 = a)
    adr x0, b       // x0 = &b
    ldr w2, [x0]    // w2 < mem[x0] (w2 = b)

    cmp w1,w2
    b.ge else // signed Greater or Equal: if (w1 >= w2)

    // I branch sono "invertiti", dobbiamo andare ad else se è vero che w1 >= w2
    // altrimenti continuiamo

    // ramo then (w1 < w2)
    mov x0, #1      // #1=standard output
    adr x1, str2    // x1=&str2
    mov x2, #7      // x2=len(str2)
    mov x8, #64     // 64 = syscall WRITE
    svc #0          // syscall
    b exit          // ignoro else

else:
    // ramo else (w1 >= w2)
    mov x0, #1      // #1=standard output
    adr x1, str1    // x1=&str1
    mov x2, #7      // x2=len(str1)
    mov x8, #64     // 64 = syscall WRITE
    svc #0          // syscall

exit:
    // Fine programma
    mov x0, #3          // Carichiamo il valore di ritorno nel registro x0
    mov x8, #93         // Specifichiamo il numero della syscall in x8
    svc #0              // syscall


// Dati del programma
.data
.p2align 2

a:  .word -10
b:  .word 10
str1: .ascii "a >= b\n"
str2: .ascii "b >= a\n"
