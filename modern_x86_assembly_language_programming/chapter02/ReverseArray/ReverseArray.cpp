#include <cstdio>
#include <cstdlib>


extern "C" void ReverseArray_(int *y, const int *x, int n);

int main(void){
    const int n = 21;
    int x[n], y[n];

    srand(31);
    for(int i=0; i<n; ++i){
        x[i] = rand()%1000;
    }

    ReverseArray_(y, x, n);

    printf("\nResults for ReverseArray\n");
    for(int i=0; i<n; ++i){
        printf("  i: %5d  y: %5d  x: %5d\n", i, y[i], x[i]);
        if(x[i] != y[n-1-i]) {
            printf("  Compare failed!\n");
            return -1;
        }
    }

    return 0;
}
