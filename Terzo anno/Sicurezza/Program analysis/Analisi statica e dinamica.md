L'**analisi statica** consiste nel capire la logica del programma osservando il codice assembly generato, mentre in quella **dinamica** il programma è eseguito con un debugger per osservarne il comportamento, solitamente sono una il complemento dell'altra.

### GNU Debugger
**gdb** - The GNU Debugger.

È possibile aggiungere informazioni di debug nel codice sorgente attraverso l'opzione `-g` nella fase di compilazione:
```bash
gcc count.c -o count -g
gdb -q count
```

- **list**: mostra il codice
- **set disassembly intel**: utilizza la sintassi intel per disassemblare il programma
- **dissassemble main**: mostra il codice assembly della sezione main
- **break main**: aggiunge un _breakpoint_ in cui fermare l'esecuzione nella sezione `main` è possibile anche specificare un indirizzo specifico con `break *<addr>`
- **run** esegue il programma facendolo fermare nei vari _breakpoint_
- **info registers**: fornisce i valori memorizzati nei registri, è anche possibile specificare un registro dopo il comando
- **nexti**: esegue la prossima istruzione nella sezione corrente
- **stepi**: nel caso venissero chiamate funzioni nella sezione corrente questo comando ne seguirebbe l'esecuzione passo passo
- **c**: itera tra i vari _breakpoint_
- **delete 1**: cancella il _breakpoint_ numero 1

>È possibile accorciare i comandi se non ce ne sono che iniziano con lo stesso prefisso inserito (e.g. `disas main`).

