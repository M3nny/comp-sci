.cpu cortex-a53
.text
.p2align 2

.global _start
_start:
    adr x0, a                // x0 = &a
    ldr w1, [x0]             // w1 < mem[x0] (w1 = a)

    adr x0, b                // x0 = &b
    ldr w2, [x0]             // w2 < mem[x0] (w2 = b)

    add w2,w1,w2             // w2 = w1 + w2

    adr x0, c                // x0 = &c
    str w2, [x0]             // w2 > mem[x0] (c = w2)

    // Fine programma
    mov x0, #3
    mov x8, #93
    svc #0


// Dati del programma
.data
.p2align 2

a:  .word -5
b:  .word 20
c:  .word 0
