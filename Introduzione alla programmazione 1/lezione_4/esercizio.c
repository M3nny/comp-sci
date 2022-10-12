#include <stdio.h>
#include <math.h>
#include <stdbool.h>

float f3 (float z);

/* dato N stampare tutti i numeri multipli di 3 e minori dii N*/
void f (int N) {
    for (intì^^^ i = 1; i < N; i++) {
        if (i%3 == 0) {
            printf("%d è divisibile per 3\n",i);
        }
    }
}

/*dato n stampi tutte le coppie di numeri a e b interi strettamente
positivi minori di N, tali per cui a^2 + b^2 = 25*/
void f2 (int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((pow(i,2) + pow(j,2)) == 25) {
                printf("%d^2 + %d^2 = 25\n",i,j);
            }
        }
    }
}

/* dato z apllicando il metodo di Erone per 10 iterazioni trova la sua
radice quadrata*/

float f3 (float z) {
    float stima = z/2.0;
    float x_finale;
    x_finale = (stima + z/stima)/2.0;

    for (int i = 0; i < 10; i++) {
        stima = x_finale;
        x_finale = (stima + z/stima) / 2.0;

        if (stima - x_finale < 0.1) {
            return x_finale;
        }
    }
    return x_finale;
}


int main() {
    float z = 144.0f;
    float radice = f3(z);
    printf("la radice di %f è: %f\n", z, radice);

    return 0;
}
