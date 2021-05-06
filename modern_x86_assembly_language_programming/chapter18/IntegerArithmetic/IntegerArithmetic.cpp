#include <stdio.h>
//#include "../../modern-x86-sourcecode/978-1-4842-0065-0_SourceCode/CommonFiles/MiscDefs.h"

typedef __int8_t Int8;
typedef __int16_t Int16;
typedef __int32_t Int32;
typedef __int64_t Int64;

//typedef __int64_t  Int64;


extern "C" {
    extern Int64 IntegerAdd_(Int64 a, Int64 b, Int64 c, Int64 d, Int64 e, Int64 f);
    extern Int64 IntegerMul_(Int8 a, Int16 b, Int32 c, Int64 d, Int8 e, Int16 f, Int32 g, Int64 h);
    extern Int64 IntegerDiv_(Int64 a, Int64 b, Int64 quo_rem_ab[2], Int64 c, Int64 d, Int64 quo_rem_cd[2]);
}

void IntegerAdd(void){
    Int64 a = 100;
    Int64 b = 200;
    Int64 c = -300;
    Int64 d = 400;
    Int64 e = -500;
    Int64 f = 600;

    Int64 sum = IntegerAdd_(a, b, c, d, e, f);

    printf("\nResults for IntegerAdd\n");
    printf("a: %5ld b: %5ld c: %5ld\n", a, b, c);
    printf("d: %5ld e: %5ld f: %5ld\n", d, e, f);
    printf("sum: %ld\n", sum);
}

void IntegerMul(void){
    Int8 a = 2;
    Int16 b = -3;
    Int32 c = 8;
    Int64 d = 4;
    Int8 e = 3;
    Int16 f = -7;
    Int32 g = -5;
    Int64 h = 10;

    Int64 sum = IntegerMul_(a, b, c, d, e, f, g, h);

    printf("\nResults for IntegerMul\n");
    printf("a: %5d b: %5d c: %5d d: %5ld\n", a, b, c, d);
    printf("e: %5d f: %5d g: %5d h: %5ld\n", e, f, g, h);
    printf("result: %ld\n", sum);
}

void IntegerDiv(void){
    Int64 a = 102;
    Int64 b = 7;
    Int64 quo_rem_ab[2];
    Int64 c = 61;
    Int64 d = 9;
    Int64 quo_rem_cd[2];

    IntegerDiv_(a, b, quo_rem_ab, c, d, quo_rem_cd);

    printf("\nResults for IntegerDiv\n");
    printf("a: %5ld b: %5ld ", a, b);
    printf("quo: %5ld rem: %5ld\n", quo_rem_ab[0], quo_rem_ab[1]);
    printf("c: %5ld d: %5ld ", c, d);
    printf("quo: %5ld rem: %5ld\n", quo_rem_cd[0], quo_rem_cd[1]);
}

int main(int argc, char *argv[])
{
    IntegerAdd();
    IntegerMul();
    IntegerDiv();

    return 0;
}
