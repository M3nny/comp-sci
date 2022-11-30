#include <stdio.h>
#include <stdlib.h>


struct carta {
    int valore;
    char seme;
};

struct carta f(struct carta c) {
    c.valore++;
    return c;
}

struct prova {
    int *array;
};

int main () {
    struct prova q;
    q.array = (int*) malloc(3*sizeof(int));
    q.array[0]= 66;
    struct prova p = q; // shadow copy, le modifiche sono condivise
    p.array[1] = 99; // ora anche q[1] ha 99
    printf("%d \n", p.array[0]); // 66
    printf("%d \n", q.array[1]); // 99
    printf("-------------------------\n");




    struct carta x;
    x.valore= 7;
    x.seme = 's';

    struct carta y = f(x);
    struct carta *z = &x;
    (*z).valore--;
    z->valore--;

    struct carta mazzo[2] = {x, y};

    printf("%d %c \n", x.valore, x.seme);
    printf("%d %c \n", y.valore, y.seme);
    printf("%d %c \n", mazzo[0].valore, mazzo[0].seme);

    return 0;
}
