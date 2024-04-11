#include <cstdio>
#include "TestStruct.h"

void PrintTestStruct(const char *msg, const TestStruct *ts){
    printf("%s\n", msg);
    printf("  ts->Val8:  %d\n", ts->Val8);
    printf("  ts->Val16: %d\n", ts->Val16);
    printf("  ts->Val32: %d\n", ts->Val32);
    printf("  ts->Val64: %lld\n", ts->Val64);
}

extern "C" {
extern TestStruct *CreateStruct_(signed char val8, short val16, int val32, long long val64);
extern void ReleaseTestStruct_(TestStruct *p);
}


int main(void){
    TestStruct *ts = CreateStruct_(40, -401, 400002, -4000000003LL);
    PrintTestStruct("Contests of TestStruct 'ts'", ts);
    ReleaseTestStruct_(ts);

    return 0;
}
