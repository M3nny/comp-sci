Il **sistema operativo** viene invocato per due tipi di eccezioni:
- TLB miss
- Page fault
Ed in risposta la CPU salterà alla routine di gestione dell'OS oppure cambia la modalità di esecuzione da **user mode** a **supervisor mode**.

Un programma in **user mode**:
- Non può modificare il page table register
- Non può modificare le entry della TLB
- Non può cambiare l'execution mode (user / supervisor)
Mentre in **supervisor mode** non ci sono restrizioni.

Un programma può passare volontariamente in supervisor mode solo tramite **system call**, in ARM questa _system call_ è rappresentata da `svc`.

### Eccezioni
- **TLB miss** (pagina presente in memoria ma non nella TLB):
	risolvibile tramite _lookup_ nella RAM avrà _penalty_ simile al _cache miss_, l'istruzione che ha causato l'eccezione (`lw` o `sw`) dovrà essere rieseguita.
- **TLB miss + page fault** (pagina non presente nè nella TLB nè in memoria):
	risolvibile tramite _lookup_ nella memoria secondaria, avviene il _context switch_ e quando il _page fault_ è risolto il programma riprende l'esecuzione.
- **Page fault con rimpiazzamento pagina**:
	se la memoria fisica è piena si rimpiazza la pagina (deve essere scritta anche in memoria secondaria se il bit dirty = 1), bisogna pulire anche la TLB se l'entry corrispondente era presente.

### Context switch
Usato nel caso ci siano operazioni che richiedono molto tempo, il **context switch** salva lo stato del processo (compreso puntatore alla PT) in esecuzione e carica lo stato di un altro processo per poi eseguirlo.

Questa è un'operazione costosa in quanto dato che la TLB è una sola dovremmo cancellare da essa tutte le entry del processo precedente per <u>far spazio</u> e <u>garantire la protezione dei dati</u>.

In alcune CPU (ARM compresa) estendiamo con l'**Address Space ID (ASID)** l'indirizzo virtuale per contenere l'ID del processo a cui appartiene quel blocco di memoria in questo modo un _hit_ (cache o TLB) avviene solo se _page number_ e _PID_ combaciano, così facendo non serve svuotare la cache in caso di _context switch_.

>[!Tip]
>ARMv8 supporta la virtualizzazione, un indirizzo virtuale di una VM passa varie trasformazioni prima di diventare effettivamente un indirizzo fisico per l'host.


### Page table multilivello
ARM usa un <u>approccio gerarchico a 4 livelli</u> che consiste nel dividere in 4 livelli la PT dove ogni livello punta a quello successivo, in questo modo stiamo dando un'importanza ai dati della PT, lasciando in RAM quelli che servono di più e lasciando in memoria secondaria quelli meno acceduti.

Se dovessimo contenere in RAM le PT di ogni processo ci sarebbe un grande spreco di memoria.