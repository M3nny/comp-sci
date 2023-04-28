.cpu cortex-a53
.text
.p2align 2

.global sayhello
sayhello:
    mov x0, #1          // 1 = standard output
    adr x1, hellostr    // x1 = &hellostr
    mov x2, #6          // x2 = 6, ovvero strlen(hellostr)
    mov x8, #64         // specifichiamo il numero di syscall in x8
    svc #0              // syscall
    ret


.global _start
_start:

    mov x10, #3         // x10 = 3
loop:
    bl sayhello         // sayhello()
    subs x10, x10, #1   // x10 -= 1 e setta i flags
    b.ne loop           // branch a loop se x10 != 0

    // Fine programma
    mov x0, #3          // Carichiamo il valore di ritorno nel registro x0
    mov x8, #93         // Specifichiamo il numero della syscall in x8
    svc #0              // syscall


// Dati del programma
.data
.p2align 2

hellostr: .ascii "hello\n"
