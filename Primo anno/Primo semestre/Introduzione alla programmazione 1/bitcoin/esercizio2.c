#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void my_print(char *s) {
    for (int i = 0; s[i] != '\0' ; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
}

int lunghezza (char *s) {
    return 123;
}

// data una stringa restituisce la stringa senza minuscole
char* f(char *s) {
    char *new_s = (char*) malloc(strlen(s)+1); // alloco 1 in più per lo '\0'
    if (!new_s) exit(EXIT_FAILURE);

    int j = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if(!(s[i] >= 'a' && s[i] <= 'z')) {
            new_s[j] = s[i];
            j++;
        }
    }
    new_s[j] = '\0'; // indico che la stringa è finita
    new_s = (char*) realloc(new_s, j+1);
    return new_s;

}

int main() {
    //ES 1
    char *a = "hello!"; // 6 caratteri + '\0'
    char b [] = "world";
    b[2] = 'x';
    printf("%c \n", a[2]);
    printf("%s %s\n", a, b);
    my_print(a);

    //ES 2
    char *s = "BuoN GiOrno a TUTTI";
    char *new_s = f(s);
    printf("%s \n", new_s);
    free(new_s);
    return 0;
}
