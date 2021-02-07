#include <cstdio>

extern "C" {
extern bool SignedEq_(int a, int b);
}


int main(void){
    int a,b;
    bool t;

    a=0, b=3;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=1, b=3;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=3, b=1;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=0, b=-3;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=-1, b=-3;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=-3, b=-1;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=1, b=-3;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    a=-3, b=-3;
    t=SignedEq_(a,b);
    printf("%d\n", t);

    return 0;
}
