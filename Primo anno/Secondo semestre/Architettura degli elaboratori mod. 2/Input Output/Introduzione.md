I sistemi di I/O sono usati per collegare il computer alle periferiche.
Questo collegamento è solitamente realizzato mediante un **bus**, il quale implementa un canale di comunicazione condiviso da più sottosistemi.

**Vantaggi**:
- Versatilità: facile aggiungere/ rimuovere dispositivi.
- Basso costo: un collegamento per più esigenze.
**Svantaggi**:
- Può rappresentare un bottleneck in quanto limita la massima frequenza di I/O.

### Esempi di bus
- **System bus**: Connette CPU e RAM, sono corti e molto veloci.
- **Backplane**: connettono dispositivi diversi con bande diverse, mediamente lunghi e veloci (PCIe).
- **I/O**: gestisce catene di dischi, molto lunghi ma lenti.