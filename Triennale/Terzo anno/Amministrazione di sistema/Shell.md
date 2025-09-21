La **shell** è un'interfaccia tra l'utente ed il sistema operativo, ed interprete di comandi.

### Bash
All'avvio di **bash (bourne again shell)** caricherà la configurazione da vari file, in particolare, quelli che vengono letti solo all'avvio della shell:
- `.profile`: contiene la definizione delle variabili d'ambiente
- `/etc/profile`, `.bash_profile`: altri file di configurazione al login
e quelli che vengono letti ogni volta:
- `.bashrc`: contiene comandi e alias

| Carattere speciale | Definizione                                                |
| ------------------ | ---------------------------------------------------------- |
| `;`                | Separatore comandi.                                        |
| `&`                | Esecuzione in background.                                  |
| `()`               | Raggruppa i comandi.                                       |
| `{}`               | Blocco di comandi.                                         |
| `\|`               | Pipe: output di un programma come input di un altro.       |
| `<`                | lettura da file a input programma.                         |
| `>`                | scrittura a file (con sovrascrittura) da output programma. |
| `<< txt`           | lettura da `stdin` fino a trovare una riga uguale a `txt`. |
| `>>`               | scrittura a file (con append) da output programma.         |
| `<&n`              | Duplica lo standard input nel file descriptor `n`.         |
| `>&n`              | Duplica lo standard output nel file descriptor `n`.        |
| `&>file`           | Dirige `stdout` e `stderr` in un file.                     |
| `&&`               | And logico.                                                |
| `\|\|`             | Or logico.                                                 |

Le **variabili** vengono usate come segue:
```bash
# senza spazi
VAR="HELLO"

# stampa HELLO
echo $VAR
```

| Variabile speciale | Definizione                                    |
| ------------------ | ---------------------------------------------- |
| `$0`               | Nome del programma                             |
| `${n}`             | Singoli argomenti passati in input             |
| `$#`               | Numero di argomenti passati in input           |
| `$*`               | Tutti gli argomenti passati in input           |
| `$$`               | PID del processo che esegue lo script          |
| `$?`               | Status code dell'ultimo comando eseguito       |
| `$!`               | PID dell'ultimo processo mandato in background |

Si possono anche definire **array**:
```bash
A=(0 1 2)
echo ${A[0]} # 0
```

Control flow:
```bash
if [ -f /etc/hosts ]; then
	echo "Esiste";
fi

###########################

for i in $(ls -1);
do
	du -hs $i 2> log.txt
done

###########################

# finchè a > 0
a=$1
while [ $a -gt 0 ]
do
	echo $a;
	a=$a-1;
done

###########################

# finchè a non è > 0
a=$1
until [ $a -gt 0 ]
do
	echo $a;
	a=$a-1;
done

###########################

var=5
case $var in
1)
	echo "x=1"
	;;
5)
	echo "x=5"
	;;
*)
	echo "x=$x"
esac
```

Il comando `select` viene usato per far selezionare interattivamente all'utente un elemento da una lista:
```bash
select v [ in items; ] do comandi; done
```

Il comando `seq` stampa una sequenza di numeri secondo un certo incremento:
```bash
# seq [OPTION]... FIRST INCREMENT LAST
seq 1 4 # 1 2 3 4
```

La variabile di sistema `$IFS`, ovvero **Internal Field Separator** rappresenta i caratteri usati per separare i parametri in input , di default è uguale a `' \t\n`.

### Powershell
In Windows viene utilizzata **powershell** la quale al posto di creare una pipeline basata su input e output testuali come in bash, fa passare i dati da una **cmdlet** all'altra come oggetti.

Le _cmdlet_ sono classi del framework **.NET** di Microsoft.

### Batch
Prima dell'avvento della powershell, venivano usati **script batch** i quali usavano comandi del **prompt dei comandi**.

Vediamo di seguito alcune **istruzioni batch**:
- `@echo on`: stampa il percorso in cui si sta lavorando
- `@echo off`: non stampa il percorso in cui si sta lavorando
- `echo <messaggio>`: stampa un messaggio
- `pause`: mette in pausa il programma visualizzando premere un tasto per continuare
- `type <file>`: stampa il contenuto di un file
- `[not] exist <file>`: ritorna $1$ se il file esiste

Gli argomenti passati in input sono identificati da `%1`, ad esempio:
```
rem i commenti iniziano con rem
echo Hai inserito '%1' dalla riga di comando.

if %1==hello echo world
```

Si possono impostare le variabili come segue:
```
set var=1
echo %var%
```

Un esempio completo con `goto` e `for`:
```
@echo off
if not exist %1 exit
for %%f in (%1) do goto dsfiles
:dsfiles
echo File %%f :
echo.
type %%f
echo.
```

### VB Script
**Microsoft's Visual Basic Scripting Edition (VBScript)** è un sottoinsieme di **Visual Basic**.

Segue un esempio con dichiarazione di variabili e stampe varie:
```vb
Option Explicit 'obbliga la dichiatazione delle variabili
Dim a,b ' Dim viene usato per dichiarare le variabili
Dim c(3) 'array
a=”ciao”
b=1
c(0)=1
c(1)=2
c(3)=3
wscript.echo a
wscript.echo b
wscript.echo c(2)

> ciao
> 1
> 2
```