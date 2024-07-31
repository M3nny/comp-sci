I bug giusti possono essere usati per alterare l'esecuzione del codice, è importante quindi capire come i programmi vengono compilati.
In questo corso prendiamo in considerazione **assembly x86-64** (conosciuto anche come: _x64, AMD64 e Intel 64_).

### Registri
- **General purpose**: `rax, ..., rdx` `r8, ... r15`
	usati per memorizzare temporaneamente valori e indirizzi utili alla computazione.

- **Stack**: `rsp, rbp`
	corrispondono rispettivamente allo **stack pointer** e **base pointer**, usati per delimitare lo stack.

- **Instruction pointer**: `rip`
	punta all'istruzione che deve essere eseguita.

- **Indexes**: `rsi, rdi`
	corrispondono rispettivamente al **source index** e **destination index**, usati per gli array, la copia delle stringhe e parametri.

- **Single Instruction Multiple Data (SIMD)**: `xmm0, ..., xmm15`
	usate per computare più valori in una volta sola, utilizzano da 128 bit a 512 bit in [AVX-512](https://en.wikipedia.org/wiki/AVX-512).

- **Flag register**: `rFlag`
	usato per lo stato, simile all'[[Registri#Application Program Status Register (APSR)|APSR]] per architettura ARM.
	- `ZF`: _zero_ flag, quando il risultato è zero
	- `CF`: _carry_ flag, quando il risultato è troppo grande o piccolo
	- `SF`: _sign_ flag, quando il risultato è negativo

![[Porzioni dei registri.png]]
La **sintassi per processori Intel** (useremo questa) è composta da:
`command <destination> <source>`.
>Da notare come in altri sistemi (e.g. **AT&T**), essa possa cambiare:
>`command <source> <destination>`.

L'**organizzazione della memoria** è la seguente:

![[Layout memoria.png|600]]
#### Stack
Nello **stack** vengono memorizzate le **variabili locali**, inoltre supporta le operazioni [[Funzioni e stack#Stack|push e pop]], cresce verso indirizzi più bassi e quando una funzione viene chiamata viene allocato uno **stack frame**:
- `rbp`: contiene l'indirizzo della base dello stack frame attuale
- `rsp`: contiene l'indirizzo del tetto dello stack frame attuale

Secondo le **convenzioni di chiamata a funzione** [System V AMD64 ABI](https://en.wikipedia.org/wiki/X86_calling_conventions), ogni chiamata memorizza i **primi 6 argomenti** in: `rdi, rsi, rdx, rcx, r8, r9` e mette ulteriori argomenti nello stack, mentre memorizza il valore di ritorno (fino a 128 bits) nei registri `rax` e `rdx`.
>Per le chiamate con architettura ARM vedi [[Funzioni e stack#Passaggio di parametri e valori di ritorno|chiamata a funzione nelle architetture ARM]].

---
### Istruzioni principali
- `mov <dst>, <src>`: assegna il valore di `src` a `dst`
- `add <dst>, <src>`: somma il valore di `src` a `dst`
- `sub <dst>, <src>`: sottrae `<src>` a `<dst>`
- `and <dst>, <src>`: esegue un _and logico_ tra `src` e `dst` mettendo il risultato in `<dst>`
- `push <target>`: inserisce il valore di `<target>` nello stack
- `pop <target>`: estrae dallo stack un valore e lo mette in `<targer>`
- `cmp <dst>, <src>`: compara `<src>` con `<dst>` sottraendo `<src>` a `<dst>` e aggiornando le flag dell'APSR

- `call <address>`: chiama la funzione all'indirizzo `<address>`, prima di saltare alla funzione però, l'indirizzo della prossima istruzione è inserito nello stack in modo da poter continuare l'istruzione dal quel punto al termine della funzione
- `ret`: esegue il pop dell'indirizzo di ritorno e gli ritorna il controllo, inoltre assegna `rip` all'indirizzo di `ret`
- `leave`: ripristina lo stack frame, quindi `rsp <- rbp` ed il vecchio `rbp` è stato rimosso dallo stack

- `jle <target>`: salta all'indirizzo di `target` se l'`<src>` precedentemente confrontato (tramite `cmp`) era **minore o uguale** di `<dst>`
- `jge <target>`: salta all'indirizzo di `target` se l'`<src>` precedentemente confrontato (tramite `cmp`) era **maggiore o uguale** di `<dst>`
- `jmp <target>`: salta all'indirizzo in `<target>`, inoltre copia il suo indirizzo in `rip`
- `lea <dst>, <src>`: carica l'indirizzo effettivo (load effective address) di `<src>` in `<dst>`
- `int <value>`: genera un interrupt per invocare una **chiamata a sistema**

Ci sono varie metodi di indirizzamento:
- **Indiretto**: `mov DWORD PTR [rbp - 4], eax`
	copia il contenuto del registro `eax` nello stack  all'indirizzo calcolato come `rbp - 4`.
- **Immediato**: `mov eax, 3`
	copia il valore $3$ nel registro `eax`.

### Esecuzione di una funzione

#### Chiamata
```c
int main() {
	func(10)
}
```
```asm
mov edi, 0xa # assegna 10 al primo parametro
call <func>  # chiama func
```
>I primi 32 bit di `rdi` saranno zeri in quanto, `edi` rappresenta i 32 bit meno significativi.


| **Stack**          | **Delimitatori** |
| ------------------ | ---------------- |
| `return <address>` | `rsp`            |
| `...`              | `rbp`            |

```c
long func(long x) {
	long a = 0;
	long b = x;
	return b;
}
```
```asm
push rbp      # call salva l'indirizzo della prossima istruzione
mov rbp, rsp  # la base dello stack assume il valore del tetto
sub rsp, 0x18 # viene spostato il tetto
```

| **Stack**          | **Delimitatori** |
| ------------------ | ---------------- |
|                    | `rsp`            |
|                    |                  |
|                    | `rbp`            |
| `<old rbp>`        |                  |
| `return <address>` |                  |
| `...`              |                  |

#### Esecuzione codice funzione
```c
long func(long x) {
	long a = 0;
	long b = x;
	return b;
}
```
```asm
mov QWORD PTR [rbp-0x18], rdi # mette in [rbp-0x18] il valore di rdi
							  # ovvero (x) il valore passato a func
mov QWORD PTR [rbp-0x10], 0x0 # esegue "a = 0" e lo mette sotto a x
mov rax, QWORD PTR [rbp-0x18] # assegna a rax il valore x
mov QWORD PTR [rbp-0x8], rax  # esegue "b = x" e lo mette sotto ad a
```

| **Stack**          | **Delimitatori** |
| ------------------ | ---------------- |
| `10 (0xa)`         | rsp``            |
| `0 (0x0`           |                  |
| `10 (0xa)`         | `rbp`            |
| `<old rbp>`        |                  |
| `return <address>` |                  |
| `...`              |                  |

#### Return
```c
long func(long x) {
	long a = 0;
	long b = x;
	return b;
}
```
```asm
mov rax, DWORD PTR [rbp-0x8] # ritorna b posizionandolo
							 # nel registro di ritorno
leave                        # rsp = rbp, rbp = old rbp
ret                          # rip viene assegnato alla prossima
							 # istruzione
```

| **Stack**          | **Delimitatori** |
| ------------------ | ---------------- |
| `10 (0xa)`         |                  |
| `0 (0x0`           |                  |
| `10 (0xa)`         |                  |
| `<old rbp>`        |                  |
| `return <address>` | `rsp`            |
| `...`              | `rbp`            |

---
### Leggere codice macchina
Con **objdump** possiamo produrre il codice assembly (-d) di un eseguibile e mostrarne le sezioni (-s) nella sintassi Intel (-M intel).

```bash
objdump -M intel -ds count > count.s
```

```c
#include <stdio.h>

int main() {
    int i;
    for (i=0; i<10; i++)
        printf("%d ", i);
    printf("\n");
}
```
```asm
0000000000001169 <main>:
    1169:	f3 0f 1e fa          	endbr64 
    116d:	55                   	push   rbp
    116e:	48 89 e5             	mov    rbp,rsp
    1171:	48 83 ec 10          	sub    rsp,0x10
    1175:	c7 45 fc 00 00 00 00 	mov    DWORD PTR [rbp-0x4],0x0
    117c:	eb 1d                	jmp    119b <main+0x32>
    117e:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
    1181:	89 c6                	mov    esi,eax
    1183:	48 8d 05 7a 0e 00 00 	lea    rax,[rip+0xe7a]
    118a:	48 89 c7             	mov    rdi,rax
    118d:	b8 00 00 00 00       	mov    eax,0x0
    1192:	e8 d9 fe ff ff       	call   1070 <printf@plt>
    1197:	83 45 fc 01          	add    DWORD PTR [rbp-0x4],0x1
    119b:	83 7d fc 09          	cmp    DWORD PTR [rbp-0x4],0x9
    119f:	7e dd                	jle    117e <main+0x15>
    11a1:	bf 0a 00 00 00       	mov    edi,0xa
    11a6:	e8 b5 fe ff ff       	call   1060 <putchar@plt>
    11ab:	b8 00 00 00 00       	mov    eax,0x0
    11b0:	c9                   	leave  
    11b1:	c3                   	ret    
```

Possiamo seguire l'esecuzione del programma osservando gli indirizzi a sinistra, da notare l'istruzione `lea    rax,[rip+0xe7a]`, la quale assegna a `rax` la stringa `"%d "`, in python è possibile calcolare l'indirizzo con:
```python
>>> hex(0x118a + 0xe7a)
'0x2004'
```

cercando nel dump un indirizzo vicino a quello calcolato troviamo:
```asm
Contents of section .rodata:
 2000 01000200 25642000                    ....%d .        
```

### Patching executables
**xxd** - make a hexdump or do the reverse.

Con xxd è possibile editare l'hexdump e poi riconvertirlo in codice macchina:
```bash
xxd -g 1 count > count.txt
xxd -r count.txt > count2
```

1. Ricavare l'objectdump
2. Trovare l'opcode dell'istruzione interessata
3. Andare a trovarla nell'hexdump

>Vedi [x86 opcodes](http://ref.x86asm.net/coder32.html).

