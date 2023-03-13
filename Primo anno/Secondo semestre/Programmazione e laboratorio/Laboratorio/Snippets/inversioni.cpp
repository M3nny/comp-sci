#include <iostream>


using std::cout;
using std::endl;

// restituisce gli elementi in A tali che A[i] < x
int smaller(int x, int* A, int n) {
    if (n == 0) {
        return 0;
    }
    return smaller(x, A+1, n-1) + (x > A[0]);
}

int inversions(int* A, int n) {
    if (n <= 1)  {
        return 0;
    }
    return inversions(A+1, n-1 ) + smaller(A[0], A+1, n-1);
}

int main() {
    int A[] = {3, -1, 0, 2, 5, -3, 2, -1};
    cout << inversions(A, sizeof(A)/sizeof(int)) << endl;
    return 0;
}
