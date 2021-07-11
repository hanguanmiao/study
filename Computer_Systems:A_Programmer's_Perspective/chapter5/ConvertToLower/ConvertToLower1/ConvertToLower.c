#include <string.h>

void lower1(char *s){
    long i;

    for(i=0; i<strlen(s); ++i){
        if(s[i] >= 'A' && s[i] <= 'Z') s[i] -= ('A' - 'a');
    }
}

int main(void){
    char str[] = {'A','B','C','D','E','F','G'};

    for(int i=0; i<10000000; ++i){
        lower1(str);
    }

    return 0;
}
