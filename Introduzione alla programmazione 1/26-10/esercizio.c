#include <stdio.h>

int ones (int *A, int N) {
    int max_len = 0, cur_len = 0;
    for (int i = 0; i < N; i++) {
        if (A[i] == 1) {
            cur_len++;
            if (cur_len > max_len) {
                max_len = cur_len;
            }
        }
    }
}

int main() {

}
