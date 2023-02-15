#include <stdio.h>

int main(){
    int ore=11, minuti=21, secondi=17;
    int sec_from_begin = ore*3600 + minuti*60 + secondi;
    printf("%d\n",sec_from_begin);

    return 0;
}
