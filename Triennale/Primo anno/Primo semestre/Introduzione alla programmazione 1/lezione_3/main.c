#include <stdio.h>

int main() {
    int x;
    scanf("%d\n", &x);

    if  (x%2 == 0) {
        printf("x è pari\n");
    } else {
        printf("x è dispari\n");
    }

    return 0;
}
