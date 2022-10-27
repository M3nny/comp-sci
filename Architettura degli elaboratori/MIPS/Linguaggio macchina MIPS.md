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

| **000000** | **10001** | **10010** | **01000** | **00000** | **100000** |
|:----------:|:---------:|:---------:|:---------:|:---------:|:----------:|
|    _op_    |    _rs_   |    _rt_   |    _rd_   |  _shamt_  |   _funct_  |

- **op**: operazione;
- **rs**: registro primo operando;
- **rt**: registro secondo operando;
- **rd**: registro risultato dell'operazione;
- **shamt**: utilizzato per le istruzioni di shift, negli altri caso è posto a 0;
- **funct**: specifica la variante dell'operazione base definita nel campo op.