#include <string.h>

void lower1(char *s){
    long i;
    int len = strlen(s);

    for(i=0; i<len; ++i){
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
