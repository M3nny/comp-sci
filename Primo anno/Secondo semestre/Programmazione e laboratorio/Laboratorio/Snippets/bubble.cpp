#include <iostream>

using namespace std;

// sposta A[0] nella posizione corretta
void swap(int* A, int n) {
    if (n <= 1) {
        return;
    }
    if (A[0] > A[1]) {
        int tmp = A[1];
        A[1] = A[0];
        A[0] = tmp;

        swap(A+1, n-1);
    }
}

void bubble_sort(int* A, int n) {
    if (n <= 1) {
        return;
    }
    bubble_sort(A+1, n-1);
    swap(A, n);
}

int main() {
    int A[] = {3, 1, 7, 2, -1, 9};
    int n = sizeof(A)/sizeof(int);

    bubble_sort(A, n);

    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    return 0;
}
