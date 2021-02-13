#include <cstdio>
#include "TestStruct.h"

extern "C" long long CalcStructSum_(const TestStruct *ts);
long long CalcStructSumCpp(const TestStruct *ts){
    return ts->Val8 + ts->Val16 + ts->Val32 + ts->Val64;
}

int main(void){
    TestStruct ts = {-100,0,2000,-300000,40000000000};

    long long sum1 = CalcStructSumCpp(&ts);
    long long sum2 = CalcStructSum_(&ts);

    printf("Input: %d %d %d %lld\n", ts.Val8, ts.Val16, ts.Val32, ts.Val64);
    printf("sum1: %lld\n", sum1);
    printf("sum2: %lld\n", sum2);

    return 0;
}
