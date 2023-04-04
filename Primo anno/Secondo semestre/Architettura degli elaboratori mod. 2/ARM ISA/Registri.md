L'ARMv8 supporta 3 ISA:
- **A32**: versione a 32 bit
- **T32**: modalità thumb usa istruzioni di A32 più corte codificate a 16 bit permettendo così un CPI < 1
- **A64**: versione a 64 bit (useremo questa)

A64 viene usato quando la CPU si trova nell'**AArch64 execution state**, può passare anche ad **AArch32** dinamicamente.

### Simple Sequential Execution
La CPU si comporta come se le istruzioni venissero caricate ed eseguite una dietro l'altra, ma nella realtà, vengono caricate 2 istruzioni alla volta e (quando è possibile) vengono eseguite in parallelo (non necessariamente in-order).

---
## Registri in AArch64
- _31_ registri **general purpose**
```armasm
add w0,w1,w2 // somma a 32 bit 
add x0,x1,x2 // somma a 64 bit
```

- _32_ registri per **operazioni floating point e vettorizzate**
```armasm
fadd s0,s1,s2 // somma fp a 32 bit 
fadd d0,d1,d2 // somma fp a 64 bit
```
N.B. quando usati col nome `v` essi rappresentano vettori di numeri con i quali è possibile eseguire operazioni contemporaneamente (come somma tra più numeri).

### Registri speciali
Non possono essere usati direttamente nelle istruzioni.
| **Nome** | **Significato**                                                |
| -------- | -------------------------------------------------------------- |
| XZR      | viene sempre letto col valore 0, non può essere scritto        |
| SP(X28)  | stack pointer                                                  |
| FP(X29)  | frame pointer                                                  |
| LR(X30)  | link register, contiene l'indirizzo di ritorno di una funzione |
| PC       | Program Counter                                                |

### Registri di sistema
Utilizzati per configurare CPU o sistema di memoria, possono essere letti o scritti dalle istruzioni `MRS` e `MSR`.

### Application Program Status Register (ASPR)
Contiene una copia dei codici di controllo generati dall'ALU:
| **31** | **30** | **29** | **28** | **27** | **26-24** | **23-20** | **19-16** | **15-0** |
| ------ | ------ | ------ | ------ | ------ | --------- | --------- | --------- | -------- |
| N      | Z      | C      | V      | Q      | RAZ/SBZP  | Reserved  | GE        | Reserved         |

I codici compresi tra i bit 31-27 (quelli che ci interessano), se _asserted_ significano:
- **N**: il risultato dell'ultima operazione è <u>negativo</u>
- **Z**: il risultato dell'ultima operazione è <u>zero</u>
- **V**: c'è stato un <u>overflow</u> nell'ultima operazione
- **C**: c'è stato un <u>riporto</u> nell'ultima operazione
