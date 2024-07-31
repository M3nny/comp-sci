**sed** - stream editor for filtering and transforming text.

I comandi di sed seguono il formato: `[addr]X[options]`, in particolare l'opzione `d` non considera le linee specificate, `p` stampa le linee specificate, `-n` stampa le linee solo se specificate.

Immaginando di avere un file: `test.txt`
```txt
123456789
Not a number
hello
```

```bash
sed '1d' test.txt #  Not a number | hello
sed '1,3d' test.txt # 
sed '1p' test.txt # 123456789 | 123456789 | Not a number | hello
sed -n '1p' test.txt # 123456789
```

La **sostituzione** avviene <u>una volta per riga</u> normalmente usando il formato: 
`s/da_sostituire/sostituto`, è possibile aggiungere alla fine:
- `/2`: per specificare la istanza da sostituire per ogni riga è la seconda
- `/g`: per una sostituzione di tutte le istanze di `da_sostituire`
- `/i`: per rendere la ricerca case insensitive
```bash
# sostituisce "hello" con "world"
sed 's/hello/world/' input.txt # output in stdout
sed -i 's/hello/world/' input.txt # modifica input.txt (in-place)
```

Per **cancellare** delle righe: `/hello/d`.

È possibile anche applicare un **mapping** del tipo: `y/abc/ABC` dove ogni lettera `a,b,c` viene sostituita rispettivamente con `A,B,C`.

### Espressioni regolari
Le espressioni regolari (regex), sono dei **pattern** che rappresentano un insieme di stringhe.

| Simbolo           | Significato                                       |
| ----------------- | ------------------------------------------------- |
| `^`               | Inizio riga                                       |
| `$`               | Fine riga                                         |
| `.`               | Un carattere qualsiasi                            |
| `c*`              | Numero arbitrario (anche nullo) di istanze di `c` |
| `c\+`             | Una o più occorrenze di `c`                       |
| `c\?`             | Zero o una occorrenza di `c`                      |
| `[012]` o `[0-2]` | Rappresenta le cifre da `0` a `2`                 |
| `[^0-9]`          | Rappresenta tutto ciò che non è una cifra         |
| `[[:alnum:]]`     | Alfanumerici: `[a-z A-Z 0-9]`                     |
| `[[:alpha:]]`     | Alfabetici: `[a-z A-Z]`                           |
| `[[:blank:]]`     | Spazi o tabs                                      |
| `[[:cntrl:]]`     | Caratteri di controllo                            |
| `[[:digit:]]`     | Numeri: `[0-9]`                                   |
| `[[:graph:]]`     | Caratteri stampabili (spazi esclusi)              |
| `[[:lower:]]`     | Caratteri lowercase: `[a-z]`                      |
| `[[:print:]]`     | Caratteri stampabili (spazi inclusi)              |
| `[[:punct:]]`     | Caratteri di punteggiatura                        |
| `[[:space:]]`     | Spazi (`\t` e `\n` inclusi)                       |
| `[[:upper:]]`     | Caratteri uppercase: `[A-Z]`                      |
| `[[:xdigit:]]`    | Cifre esadecimali: `[0-9 a-f A-F]`                |
È possibile fare delle **aggiunte** dopo il l'espressione desiderata tramite `&`:
>`sed 's/hello/& world/g'` aggiunge `world` dopo `hello`.

L'espressione: `s/Dear \([^ ]*\) .*$/Name = \1/g` estrae il nome da una mail, il pattern di riferimento è racchiuso da `\( \)` e la sua reference è `\1`, per futuri pattern sarà necessario usare `\2, \3...`.

**Estensioni GNU**:

| Simbolo  | Significato           |
| -------- | --------------------- |
| `c\{n\}` | Ripete `c`, `n` volte |
| `\U`     | Converte in uppercase |
| `\L`     | Converte in lowercase |
