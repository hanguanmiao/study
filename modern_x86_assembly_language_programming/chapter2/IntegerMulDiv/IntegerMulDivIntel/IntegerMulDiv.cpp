#include <cstdio>

extern "C" int IntergerMulDiv_(int a, int b, int *prod, int *quo, int *rem);

int main(void){
    int a=21,b=9;
    int prod=0,quo=0,rem=0;
    int rc;

    rc = IntergerMulDiv_(a,b, &prod, &quo, &rem);
    printf("a:   %4d  b:    %4d\n", a, b);
    printf("rc:  %4d  prod: %4d\n", rc, prod);
    printf("quo: %4d  rem:  %4d\n", quo, rem);

    a=-29;
    prod = quo = rem =0;
    rc = IntergerMulDiv_(a,b, &prod, &quo, &rem);
    printf("a:   %4d  b:    %4d\n", a, b);
    printf("rc:  %4d  prod: %4d\n", rc, prod);
    printf("quo: %4d  rem:  %4d\n", quo, rem);

    b=0;
    prod = quo = rem =0;
    rc = IntergerMulDiv_(a,b, &prod, &quo, &rem);
    printf("a:   %4d  b:    %4d\n", a, b);
    printf("rc:  %4d  prod: %4d\n", rc, prod);
    printf("quo: %4d  rem:  %4d\n", quo, rem);

    return 0;
}
