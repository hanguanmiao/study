#include <cstdio>

extern "C" {
    extern char GlChar;
    extern short GlShort;
    extern int GlInt;
    extern long long GlLongLong;
}
char GlChar = 10;
short GlShort = 20;
int GlInt = 30;
long long GlLongLong = 0x00000000FFFFFFFE;

extern "C" void IntergerAdd_(char a, short b, int c, long long d);

int main(void){
    printf("before GlChar:     %d\n", GlChar);
    printf("       GlShort:    %d\n", GlShort);
    printf("       GlInt:      %d\n", GlInt);
    printf("       GlLongLong: %lld\n", GlLongLong);

    IntergerAdd_(3, 5, -37, 11);

    printf("after  GlChar:     %d\n", GlChar);
    printf("       GlShort:    %d\n", GlShort);
    printf("       GlInt:      %d\n", GlInt);
    printf("       GlLongLong: %lld\n", GlLongLong);

    return 0;
}
