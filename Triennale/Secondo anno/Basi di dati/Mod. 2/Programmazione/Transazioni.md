Operazioni **concorrenti** su una base dati possono creare problemi e quindi danneggiarne l'**integrità**.

Una **transazione** deve rispettare le seguenti **tre proprietà**:
- **Serializzabilità**: : l’esecuzione concorrente di più transazioni è equivalente ad una loro esecuzione seriale in un qualche ordine
- **Atomicità**: la transazione deve accadere in una volta e se termina prematuramente tutti i suoi effetti parziali sono annullati
- **Persistenza**: le modifiche effettuate da una transazione terminata correttamente sono permanenti

Se avviene un **fallimento** in un certo punto della transazione, il risultato viene scartato e le istruzioni successive (se presenti) non vengono eseguite.

Normalmente ogni operazione singola SQL è atomica, quando ce ne sono molteplici che devono essere eseguite di fila bisogna usare una transazione, la quale generalmente è strutturata come:
1. `START TRANSACTION`: comincia la transazione
2. `COMMIT`: scrive sul disco le operazioni svolte
3. `ROLLBACK`: viene riportato il database allo stato prima della transazione

### Controllo dei vincoli
È possibile specificare quando verificare un vincolo in una transazione, in particolare un vincolo può appartenere ad una delle seguenti categorie:
- `NOT DEFERRABLE`: viene sempre controllato dopo ogni operazione
- `DEFERRABLE INITIALLY IMMEDIATE`: viene controllato dopo ogni operazione della transazione, ma è possibile rilassarlo per farlo controllare solo prima del commit
- `DEFERRABLE INITIALLY DEFERRED`: viene controllato solo prima del commit, ma è possibile rafforzarlo per farlo controllare dopo ogni operazione

Il controllo dei vincoli può essere configurato tramite:
```sql
SET CONSTRAINTS [OPTION]
```

### Prestazioni
Le transazioni possono essere implementate con i seguenti metodi:
- **Lock globale** sul database, rilasciato dopo commit o rollback
- **Lock locali** su porzioni del database e gestione rilassata delle transazioni **read only**
- [MVCC](https://en.wikipedia.org/wiki/Multiversion_concurrency_control) (MultiVersion Concurrency Control) usa diverse copie del database per diverse transazioni (vedi `VACUUM FREEZE` in postgres)

>I DBMS generalmente offrono diversi **livelli di isolamento** fra transazioni, rilassare il livello di isolamento ideale può aumentare le prestazioni ma è rischioso.

---
### Read only
Una transazione potrebbe essere definita per leggere atomicamente (con più `SELECT`) dei dati, in postgres si definisce come segue:
```sql
SET TRANSACTION [livello di isolamento]
```
- Può solo leggere dati (`SELECT`)
- Vengono lette solo le scritture eseguite prima dell'inizio della transazione
- Più transazioni read only possono essere eseguite contemporaneamente senza rischio di compromettere vincoli

## Livelli di isolamento
Seguono dei livelli di isolamento meno restrittivi che possono aumentare le performance, ma allo stesso tempo introdurre problemi.
### Read uncommited
Consente di leggere **dirty data**, ovvero dati scritti da altre transazioni che non hanno ancora eseguito commit:
- Si parla di **dirty read**
- Nel caso la transazione che ha scritto i dirty data dovesse abortire, bisognerebbe tenerne conto se si sta leggendo dirty data, in quanto tali valori verrebbero riportati allo stato precedente e quindi potrebbero venire scritti valori non desiderati (se oltre a leggere si scrive)
>SQL di default limita l'uso di questo livello di isolamento alle transazioni read only.

### Read commited
Consente di leggere i dati scritti da altre transazioni solo dopo che hanno eseguito un commit (impedisce: dirty read).
- Una scrittura acquisisce un lock rilasciato solo dopo la sua terminazione
- Leggere lo stesso dato dopo che un'altra transazione ha eseguito un commit può comportare una lettura differente e portare a **unrepeatable read**
	1. A somma i voti di tutti gli studenti
	2. B cancella uno studente ed esegue il commit
	3. A calcola il numero degli studenti e calcola la media (sbagliata)
- Si può perdere l'aggiornamento dei dati da parte di un'altra transazione incorrendo in dei **lost update**
	1. A legge dato(12)
	2. B legge dato(12)
	3. A esegue dato(12)-3 = dato(9) ed esegue il commit
	4. B esegue dato(12)-4 =  dato(8), errato in quanto dato è stato aggiornato

### Repeatable read
A differenza dei livelli precedenti, viene acquisito il <u>lock anche in read oltre che in write</u> (impedisce: dirty read, unrepeatable read, lost update).

Prevenzione di _unrepeatable read_:
1. A somma i voti di tutti gli studenti
2. A calcola il numero degli studenti e calcola la media
3. B cancella un studente

Prevenzione di _lost update_:
1. A legge dato(12)
2. A esegue dato(12)-3 = dato(9) ed esegue il commit
3. B legge dato(9)
4. B esegue dato(9)-4 =  dato(5)

>[!Attention]
>I lock vengono implementati a livello di **righe**.

- Un'altra transazione può aggiungere dati ad una tabella prima che la transazione in corso corso sia stata completata, portando a **phantom reads**
	1. A somma i voti di tutti gli studenti (lock su voti)
	2. B inserisce uno studente (lock su studenti)
	3. A cerca di calcolare il numero di studenti ma non può a causa del lock di B
	4. B esegue il commit e rilascia il lock
	5. A calcola il numero di studenti e calcola la media (sbagliata)

#### Riassunto
- **Dirty read**: vengono letti dati da altre transazioni non concluse (che potrebbero eseguire un rollback)
- **Unrepeatable read**: vengono letti gli stessi dati più volte e si  ottengono risultati diversi perché un'altra transazione ha modificato i dati e fatto il commit tra le letture
- **Lost update**: quando due o più transazioni leggono lo stesso dato e poi lo aggiornano in base alla lettura fatta, ma l'aggiornamento di una transazione sovrascrive l'aggiornamento dell'altra senza alcuna sincronizzazione
- **Phantom read**: quando una transazione esegue una query che rispetta una condizione, ma poi eseguendola successivamente ottiene righe diverse in quanto un'altra transazione ha modificato (cancellando o inserendo altre righe) la tabella in questione


| Isolamento      | Dirty read | Unrepeatable read | Lost update | Phantom read |
| --------------- | :--------: | :---------------: | :---------: | :----------: |
| Read uncommited |     ✅      |         ✅         |      ✅      |      ✅       |
| Read committed  |     ❌      |         ✅         |      ✅      |      ✅       |
| Repeatable read |     ❌      |         ❌         |      ❌      |      ✅       |
| Serializable    |     ❌      |         ❌         |      ❌      |      ❌       |

>Il livello di isolamento di default in postgres è `READ COMMITED`.

