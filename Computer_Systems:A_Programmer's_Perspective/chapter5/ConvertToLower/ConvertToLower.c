#include <string.h>
#include <sys/time.h>
#include <stdio.h>

void lower1(char *s){
    long i;

    for(i=0; i<strlen(s); ++i){
        if(s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
    }
}

void lower2(char *s){
    long i;
    int len = strlen(s);

    for(i=0; i<len; ++i){
        if(s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
    }
}

int main(void){
    struct timeval tstart, tend;
    char str1[] = {'A','B','C','D','E','F','G'};
    char str2[] = {'A','B','C','D','E','F','G'};



    gettimeofday(&tstart, NULL);
    for(int i=0; i<10000000; ++i){
        lower1(str1);
    }
    gettimeofday(&tend, NULL);
    printf("%ld\n", (tend.tv_sec - tstart.tv_sec)*1000000L + tend.tv_usec - tstart.tv_usec);

    gettimeofday(&tstart, NULL);
    for(int i=0; i<10000000; ++i){
        lower2(str2);
    }
    gettimeofday(&tend, NULL);
    printf("%ld\n", (tend.tv_sec - tstart.tv_sec)*1000000L + tend.tv_usec - tstart.tv_usec);

    return 0;
}
