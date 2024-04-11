#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//gcc -std=c11 -Wall -Wextra -g -O0 main.c -pthread



#define N 2
#define M N+1
#define NUM 2*M+1

int main(void){
    int b=5, c=(5);
    printf("%d %d\n",b,c);

    return 0;
}


