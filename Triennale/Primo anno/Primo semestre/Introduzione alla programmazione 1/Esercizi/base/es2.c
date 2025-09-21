#include <stdio.h>

int main(){
    int record_h=11, record_m=21, record_s=17;
    int record = record_h*3600 + record_m*60 + record_s;
    float distanza = 42.195f;

    printf("Il record è %d\n", record);

    float tempo_min = (float)record_h*60.0f + (float)record_m + (float)record_s/60.0f;
    float passo = tempo_min / distanza;

    printf("Il passo record è di %f min/km \n", passo);

    float pass_rec = (tempo_min-1.0f/60.0f) / distanza;
    printf("Devi fare %f per battere il record", pass_rec);

    return 0;
}
