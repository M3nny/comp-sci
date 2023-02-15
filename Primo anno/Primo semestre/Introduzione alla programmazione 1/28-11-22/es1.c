#include <stdio.h>

/* Dobbiamo dare un resto di i fiorini al nostro cliente.
 * Dato un insieme di divers otaglio, dire quanti possibili modi ci sono per scegliere un sotto-insieme di monete la cui somma sia pari al resto.
 * Siano dati un array c con ivalori delle diverse monete e un array q con la quantità di monete per ciascun taglio.
*/

int count (int *c, int *q, size_t c_size, int t) {
    if (t==0)
        return 1;
    if (c_size == 0 && t > 0)
        return 0;

    int tot = 0;
    for (int n = 0; n <= q[0] && t-n*c[0] >= 0; n++)
        tot += count(c+1, q+1, c_size-1, t-n*c[0]);
    return tot;
}

int main (int arg, char *argv[]) {
    int c[] = {1, 3 , 7, 12}; // monete da 1,3,7 e 12 fiorini
    int q[] = {7, 1, 1, 1}; // 7 monete da 1 fiorino e 1 moneta da 3, 1 moneta da 7, 1 moneta da 12

    int t = 7;
    printf("%d\n", count(c, q, 4, t));

}

/* Caso base: casella = uscita
 * Passo induttivo: N -> score(player + movimento in su)
