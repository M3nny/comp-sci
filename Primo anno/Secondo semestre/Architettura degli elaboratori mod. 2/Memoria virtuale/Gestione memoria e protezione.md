Il **sistema operativo** viene invocato per due tipi di eccezioni:
- TLB miss
- Page fault
Ed in risposta la CPU salterà alla routine di gestione dell'OS oppure cambia la modalità di esecuzione da **user mode** a **supervisor mode**.

Un programma in **user mode**:
- Non può modificare il page table register
- Non può modificare le entry della TLB
- Non può cambiare l'execution mode (user / supervisor)
Mentre in **supervisor mode** non ci sono restrizioni.