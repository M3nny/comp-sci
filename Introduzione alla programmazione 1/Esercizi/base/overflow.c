#include <stdio.h>

int main(void) {
    unsigned int i = 0;
    unsigned int j = i-1;
    printf("j %d\n", j);

    unsigned char x = 255+1;
    printf("x %c\n", x);

    unsigned char h = 255;
    int k = h+1;
    printf("k %d\n", k);

    return 0;
}
