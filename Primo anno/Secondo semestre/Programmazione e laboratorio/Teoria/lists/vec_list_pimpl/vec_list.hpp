// supponiamo di memorizzare liste di interi con MAX elementi memorizzabili, ogni blocco contiene:
/*
 * indice del vettore che contiene il blocco precedente
 * informazione memorizzata nel blocco
 * indice del vettore che contiene il blocco successivo
*/

// Per marcare i blocchi liberi metto prev e next a -2 (per differenziare dalla lista con 1 blocco, se vuoto p,n = -2 se pieno p,n = -1)
// all'inizio saranno tutti inizializzati con il marcatore -2

// Vantaggi
/*
    * Possiamo fare una prepend trovando il primo blocco vuoto
    * Allocazioni e deallocazioni sono più veloci
    * Carichiamo la lista una sola volta nell'heap poi non interagiamo più con l'OS (dato che ha dimensione MAX)
*/

// Alla fine saremo in grado di decidere in fase di linking quale implementazione è meglio dell'altra

// Abbiamo quindi 2 tipi di liste dentro la lsita principale
/*
    * DL list contenente le infomazioni
    * SL list contenente le celle vuote
*/

// Usiamo 3 indicatori per capire su quale lista siamo
/*
    * head: indica blocco inizio lista
    * tail: blocco fine
    * free: prima cella libera
*/

class ListDL {
public:
    ListDL();
    ListDL(const ListDL& l);
    ~ListDL();

    void size() const;
    void print() const; // non modifica lo stato della classe

    void prepend (int e);
    void append(int e);
    int& at(int pos);

    const ListDL& operator=(const ListDL& l); // ritorno const ref. per efficienza
    bool operator==(const ListDL& l) const;
    ListDL operator+(const ListDL& l);
private:
    struct impl;
    impl* pimpl;
};
