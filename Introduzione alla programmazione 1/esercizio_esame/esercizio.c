#include <stdio.h>
float dot (float *A, float *B, int N);
// scanf(" %c", &c) ignora i whitespaces mettendo uno spazio prima di %c
//
/* dot product
 * dati 2 array A e B di float di pari dimenione N
 * dot(A,B) = somma A[i]*B[i] per i da 0 a N-1
 */
int main () {
    float A = [1,0,1];
    float B = [5,10,20];

    printf("%f \n", dot(A, B, 3));

}

float dot (float *A, float *B, int N) {
    float somma = 0.0f;
    for (int i = 0; i < N; i++) {
        somma += A[i]*B[i];
    }
    return somma;
}

// ---
float dot_puntatori (float *A, float *B, int N) {
    float somma = 0.0f;
    for (int i = 0; i < N; i++) {
        somma += (*(A+i)) * (*(B+i));
    }
    return somma;
}

float dot_puntatori2 (float *A, float *B, int N) {
    float somma = 0.0f;
    for (int i = 0; i < N; i++) {
        somma += (*A) * (*B);
        A++; //muovo di 1 il puntatore
        B++;
    }
    return somma;
}

float dot_puntatori3 (float *A, float *B, int N) {
    float somma = 0.0f;
    for (int i = 0; i < N; i++) {
        somma += (*(A++)) * (*(B++));
    }
    return somma;
}
// ---

float dot_puntatori_cpp (float *A, float *B, int N) {
    float somma = 0.0f;
    float *begin = A, *end = A+N; //end -> sentinella
    for (float *A_i=begin; A_i!=end; A_i++) {
        somma += (*(A_i)) * (*(B++));
    }
    return somma;
}
