#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool pari(x) {
    return x%2==0;
}
bool tutti_pari(int *v, size_t v_size) {
    if (v_size == 0) exit(EXIT_FAILURE);
    bool accum = pari(v[0]);
    for (size_t i=1; i<v_size; i++) {
        accum = accum && pari(v[i]);
        if (!accum) {
            break;
        }
    }
    return accum;
}

// verifica se la matrice è tirangolare inferiore
bool tri_inf(int *M, int lato) {
    bool all_zeros = true;
    for (int r = 0; r < lato; r++) {
        for (int c = 0; c < lato; c++) {
            if (M[c+r*lato] != 0) {
                all_zeros = false;
            }
        }
    }
    return all_zeros;
}

int main () {
    int M1[3][3] = { {1,1,1}, {1,0,0}, {1,1,1} }; // false
    int M2[4][4] = { {1,0,0,0}, {1,0,0,0}, {1,1,1,0}, {1,2,3,4}}; // true

    printf("M1 %d \n", tri_inf(M1, 3));
    printf("M2 %d \n", tri_inf(M2, 4));

    int x[] = {2,4,6,8,10}; // ture
    int s = tutti_pari(x,5);
    printf("%d\n", s);
}
