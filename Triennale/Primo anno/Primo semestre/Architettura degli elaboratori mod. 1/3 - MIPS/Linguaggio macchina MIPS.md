I **linguaggi macchina** hanno una corrispondenza 1 a 1 con le codifiche in binario, sono nati per dare all'uomo un'interfaccia minima con cui approcciarsi al processore.
Non esistono controlli di flusso sofisticati e le istruzioni aritmetiche hanno un numero fisso di operandi.

## Stored program
I programmi sono memorizzati in memoria, bisogna quindi seguire il seguente ciclo per eseguire un'applicazione:
- **Fetch**: la cpu legge l'istruzione indirizzata dal <u>program counter</u>;
- **Decode**: decodifica le azioni da svolgere;
- **Execute**: esegue l'istruzione e ripete il ciclo.

## Istruzioni e linguaggio macchina
- L'**instruction set** del MIPS è simile a quello di altre architetture RISC;
- Le istruzioni aritmetiche del MIPS permettono solo **operazioni elementari** tra coppie di operandi da 32 bit: add, sub, mult, div;
- Le istruzioni operano su registri lunghi 32 bit = 1 word

Con le istruzioni **sw**/**lw** carico in/dalla memoria registri.

### Formato R-type
Il formato Register type per istruzioni aritmetico-logiche è rappresentato come segue:

`add $8, $17, $18`

| **000000** | **10001** | **10010** | **01000** | **00000** | **100000** |
|:----------:|:---------:|:---------:|:---------:|:---------:|:----------:|
|    _op_    |    _rs_   |    _rt_   |    _rd_   |  _shamt_  |   _funct_  |

- **op**: operazione;
- **rs**: registro primo operando;
- **rt**: registro secondo operando;
- **rd**: registro risultato dell'operazione;
- **shamt**: utilizzato per le istruzioni di shift, negli altri caso è posto a 0;
- **funct**: specifica la variante dell'operazione base definita nel campo op.

### Formato I-type
Il formato Immediate type è diverso dal formato precedente in quanto non utilizza tre registri per le operazioni, bensì due + un valore costante, viene utilizzato per diverse istruzioni, ad esempio lw e sw.

` lw $9, 32($18)`

| **35** | **18** | **9** |      **32**     |
|:------:|:------:|:-----:|:---------------:|
|  _op_  |  _rs_  |  _rt_ | _16 bit number_ |

- In questo caso **rt** è il registro destinazione.

## Control flow
Le istruzioni MIPS ci danno una versione scarna delle istruzioni if/else.

- **Salto condizionato** (I-type):  
``` r
beq $4, $5, Label   # Branch if equal
					# if(i == j)
					
bne $6, $5, Label   # Branch if not equal 
					# if(i != j)
```

- **Salto non condizionato** (J-type - Jump type):
``` r
j Label
```

- **Flag minore** (R-type):
``` r
slt $10, $4, $5     # Set if less than
					# if($4 < $5) then $10 = 1 else $10 = 0
```

- **Operazioni logiche bit a bit** (R-type):
``` r
and $29, $28, $6    # Eseguo l'and dei 32 bit nel registro
or $27, $8, $16     # Eseguo l'or bit a bit
```

Esistono poi operazioni come **addi, andi, ori, slti** che funzionano allo stesso modo delle loro versioni senza **i** alla fine, solo che in questo caso useremo il formato I-type, appunto useremo una costante e non un registro per eseguire l'operazione.



