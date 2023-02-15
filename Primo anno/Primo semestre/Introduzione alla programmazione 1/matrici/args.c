#include <stdio.h>

//riceve labirinto in stdinput

/*
 * numero righe 3
 * numero colonne 7
 * #######
 * #     _
 * #######
 */

void challenge (void) {
    int rows, cols;
    scanf("%d", &rows);
    scanf("%d", &cols);
    printf("Sfida");
}

int main ( int argc, char *argv[] ) {
    for (int i = 0; i < argc; i++) {
        printf("%s \n", argv[i]);
    }

    if ( argc == 2 && strcmp(argv[1],"--challenge") == 0 ) {
        challenge();
        return 0;
    }

    return 0;

}
