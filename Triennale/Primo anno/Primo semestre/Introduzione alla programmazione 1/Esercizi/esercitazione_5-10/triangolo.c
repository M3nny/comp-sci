#include <stdio.h>
#include <stdbool.h>

bool isTriangle(int l1, int l2, int l3);
int somma(int a, int b);

int main () {
    int l1 = 1, l2 = 2, l3 = 3;
    int a = 3, b = 2;

    if (isTriangle(l1, l2, l3)) {
        printf("è un triangolo\n");
    } else {
        printf("non è un triangolo\n");
    }

    printf("%d\n",somma(a,b));


}

bool isTriangle(int l1, int l2, int l3) {
    if ((l3 < l1 + l2) && (l2 < l1 + l2) && (l1 < l2 + l3)) {
        return true;
    } else {
        return false;
    }
}

int somma(int a, int b) {
    return (a + b);
}
