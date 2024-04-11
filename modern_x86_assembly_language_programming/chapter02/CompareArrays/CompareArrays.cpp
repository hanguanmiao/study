#include <cstdio>
#include <cstdlib>

extern "C" int CompareArrays_(const int *x, const int *y, int n);

int main(void){
    const int n = 21;
    int x[n], y[n];
    int result;

    srand(11);
    for(int i=0; i<n; ++i){
        x[i] = y[i] = rand()%1000;
    }
    printf("\nResults for CompareArrays\n");

    result = CompareArrays_(x, y, -n);
    printf("  Test #1 - expecte: %3d  actual: %3d\n", -1, result);

    x[0] += 1;
    result = CompareArrays_(x, y, n);
    x[0] -= 1;
    printf("  Test #2 - expecte: %3d  actual: %3d\n", 0, result);

    x[n/2] -= 2;
    result = CompareArrays_(x, y, n);
    x[n/2] += 2;
    printf("  Test #3 - expecte: %3d  actual: %3d\n", n/2, result);

    x[n-1] *= 3;
    result = CompareArrays_(x, y, n);
    x[n-1] /= 3;
    printf("  Test #4 - expecte: %3d  actual: %3d\n", n-1, result);

    result = CompareArrays_(x, y, n);
    printf("  Test #5 - expecte: %3d  actual: %3d\n", n, result);

    return 0;
}
