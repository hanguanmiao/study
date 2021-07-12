#include <sys/time.h>
#include <stdio.h>


void combine3(int len, int *vec_ptr,  int*dest){
    *dest = 1;
    for(int i=0; i<len; ++i){
        *dest = *dest * vec_ptr[i];
    }
}


void combine4(int len, int *vec_ptr,  int*dest){
    int ret = 1;
    for(int i=0; i<len; ++i){
        ret = ret * vec_ptr[i];
    }
    *dest = ret;
}

int main(void){
    int ptr1[] = {2,3,5};
//    int ptr2[] = {2,3,5};
    int res;
//    struct timeval tstart, tend;

//    combine3(sizeof(ptr1)/sizeof(int), ptr1, ptr1+2);
//    printf("%d\n", *(ptr1+2));
//    combine4(sizeof(ptr2)/sizeof(int), ptr2, ptr2+2);
//    printf("%d\n", *(ptr2+2));

//    ptr1[2] = ptr2[2] = 5;
//    gettimeofday(&tstart, NULL);
    for(int i=0; i<10; ++i){
        for(int j =0; j<1000000; ++j){
            combine3(sizeof(ptr1)/sizeof(int), ptr1, &res);
        }
    }
    printf("%d\n", res);
//    gettimeofday(&tend, NULL);
//    printf("%ld\n", (tend.tv_sec - tstart.tv_sec)*1000000L + tend.tv_usec - tstart.tv_usec);

//    gettimeofday(&tstart, NULL);
//    for(int i=0; i<1; ++i){
//        for(int j =0; j<100000000; ++j){
//            combine4(sizeof(ptr2)/sizeof(int), ptr2, &res);
//        }
//    }
//    gettimeofday(&tend, NULL);
//    printf("%ld\n", (tend.tv_sec - tstart.tv_sec)*1000000L + tend.tv_usec - tstart.tv_usec);

    return 0;
}
