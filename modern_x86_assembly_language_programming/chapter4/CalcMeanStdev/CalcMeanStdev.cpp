#include <cstdio>
#include <cmath>

extern "C" {
extern bool CalcMeanStdev_(const double *a, int n, double *mean, double *stdev);
}

bool CalcMeanStdevCpp(const double *a, int n, double *mean, double *stdev){
    if(n <= 1){
        return  false;
    }

    double sum = 0.0;
    for(int i=0; i<n; ++i){
        sum += a[i];
    }
    *mean = sum/n;

    sum = 0.0;
    for(int i=0; i<n; ++i){
        double temp = a[i] - *mean;
        sum += temp * temp;
    }
    *stdev = sqrt(sum/(n-1));
    return true;
}

int main(void){
    double a[] = {10, 2, 33, 15, 41, 24, 75, 37, 18, 97};
    const int n = sizeof(a)/sizeof (double);
    double mean1, stdev1;
    double mean2, stdev2;

    CalcMeanStdevCpp(a, n, &mean1, &stdev1);
//    CalcMeanStdev_(a, n, &mean2, &stdev2);

    for(int i=0; i<n; ++i){
        printf("a[%d] = %g\n", i, a[i]);
    }
    printf("\n");
    printf("mean1: %g stdev1: %g\n", mean1, stdev1);
}
