#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

//gcc -std=c11 -Wall -Wextra -g -O0 main.c -pthread

typedef struct Row
{
    int a;
    int b;
}Row;

typedef struct RowWithIdxs
{
    const Row *rows;
    const Row **expectRows;
    int *expectA;
    int sidx;
    int eidx;
    int nExpectedRows;
    int nExpectA;
}RowWithIdxs;

void task1(const Row *rows, int nrows);
void task2(const Row *rows, int nrows);
void task3(const Row *rows, int nrows);
void task4(const Row *rows, int nrows, int *expectA, int numA, int nthread);

bool findBoundsA(const Row *rows, int leftvalue, int rightvalue,
                int startidx, int endidx, int *leftidx, int *rightidx);
bool findBoundsB(const Row *rows, int leftvalue, int rightvalue,
                int startidx, int endidx, int *leftidx, int *rightidx);
bool findBoundsInternal(const Row *rows, int leftvalue, int rightvalue,
                int startidx, int endidx, bool isA, int *leftidx, int *rightidx);
int rowsCmp(const void *arg1, const void *arg2);
int getCPUCores(void);
void *threadFnFindRow(void *arg);

void task1_test(void);
void task2_test(void);
void task3_test(void);
void task4_test(void);


int main(void){
    task1_test();
    task2_test();
    task3_test();
    task4_test();

    return 0;
}

void task1(const Row *rows, int nrows){
    for(int i=0; i<nrows; ++i){
        if((rows[i].b >= 10 && rows[i].b < 50) &&
                (rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000)){
            printf("%d,%d\n", rows[i].a, rows[i].b);
        }
    }
}

void task2(const Row *rows, int nrows){
    int leftidxA, rightidxA;
    int startidxA = 0;
    int expectedA[] = {1000,2000,3000};

    if(nrows <= 0) return;

    for(int i=0; i<(int)(sizeof(expectedA)/sizeof(int)); ++i){
        if(findBoundsA(rows, expectedA[i], expectedA[i], startidxA, nrows-1, &leftidxA, &rightidxA)){
            int leftidxB, rightidxB;

            // 更新下次寻找a的起始索引
            startidxA = rightidxA + 1;

            if(findBoundsB(rows, 10, 49, leftidxA, rightidxA, &leftidxB, &rightidxB)){
                for (int j = leftidxB; j <= rightidxB; ++j) {
                    printf("%d,%d\n", rows[j].a, rows[j].b);
                }
            }
        }
    }
}

void task3(const Row *rows, int nrows){
    int leftidxA, rightidxA;
    int startidxA = 0;
    int expectedA[] = {1000,2000,3000};
    int expectedStartIdx[] = {-1, -1, -1}; // 保存搜寻结果的起始索引
    int expectedEndIdx[] = {-1, -1, -1};   // 保存搜寻结果的末尾索引
    int sum = 0;
    const Row **expectRowsP;
    int expectRowsIdx = 0;

    if(nrows <= 0) return;

    for(int i=0; i<(int)(sizeof(expectedA)/sizeof(int)); ++i){
        if(findBoundsA(rows, expectedA[i], expectedA[i], startidxA, nrows-1, &leftidxA, &rightidxA)){
            int leftidxB, rightidxB;

            // 更新下次寻找a的起始索引
            startidxA = rightidxA + 1;

            if(findBoundsB(rows, 10, 49, leftidxA, rightidxA, &leftidxB, &rightidxB)){
                expectedStartIdx[i] = leftidxB;
                expectedEndIdx[i] = rightidxB;
                sum += rightidxB - leftidxB + 1;
            }
        }
    }

    // 复制符合条件的rows的指针
    expectRowsP = malloc(sum * sizeof(Row*));
    for(int i=0; i<(int)(sizeof(expectedA)/sizeof(int)); ++i){
        if(expectedStartIdx[i] == -1) continue;
        for(int j=expectedStartIdx[i]; j<=expectedEndIdx[i]; ++j){
            expectRowsP[expectRowsIdx++] = &rows[j];
        }
    }

    // 通过指针进行排序
    qsort(expectRowsP, sum, sizeof(Row*), rowsCmp);

    for(expectRowsIdx=0; expectRowsIdx<sum; ++expectRowsIdx){
        printf("%d,%d\n", expectRowsP[expectRowsIdx]->a, expectRowsP[expectRowsIdx]->b);
    }

    free(expectRowsP);
}


/*
 * parameters:
 *      expectA 为期望获得的A，前几例中为1000，2000，3000，此次通过指针传入
 *          这里我假设expectA已经从小到达排序且无重复
 *      nthread 启动的线程数，如果 <= 0 则使用核数
 */
void task4(const Row *rows, int nrows, int *expectA, int numA, int nthread){
    int numThread;
    pthread_t *threadIds;
    RowWithIdxs *rowinfo;
    const Row **sortRows;
    int nsortrows = 0;
    int tmpidx;
    int quotient, remainder, step;

    if(numA <= 0 || nrows <=0) {
        return;
    }else{
        // 确定线程数
        if(nthread <= 0){
            numThread = getCPUCores();
        }else{
            numThread = nthread;
        }
        if(numA < numThread){
            numThread = numA;
        }
    }

    // 初始化参数
    quotient = numA/numThread;
    remainder = numA%numThread;
    step = 0;
    rowinfo = malloc(numThread * sizeof(RowWithIdxs));
    for(int i=0; i<numThread; ++i){
        rowinfo[i].rows = rows;
        rowinfo[i].sidx = 0;
        rowinfo[i].eidx = nrows - 1;
        if(remainder){
            rowinfo[i].expectA = expectA + step;
            rowinfo[i].nExpectA = quotient + 1;
            step += quotient + 1;
            --remainder;
        }else{
            rowinfo[i].expectA = expectA + step;
            rowinfo[i].nExpectA = quotient;
            step += quotient;
        }
    }

    threadIds = malloc(numThread * sizeof(pthread_t));

    // 创建线程
    for(int i=0; i<numThread; ++i){
        pthread_create(&threadIds[i], NULL, &threadFnFindRow, &rowinfo[i]);
    }

    for(int i=0; i<numThread; ++i){
        pthread_join(threadIds[i], NULL);
    }

    // 复制row指针，以便后面进行merge排序
    for(int i=0; i<numThread; ++i){
        nsortrows += rowinfo[i].nExpectedRows;
    }
    sortRows = malloc(nsortrows * sizeof(Row*));
    tmpidx = 0;
    for(int i=0; i<numThread; ++i){
        memcpy(sortRows + tmpidx, rowinfo[i].expectRows, rowinfo[i].nExpectedRows * sizeof(Row*));
        tmpidx += rowinfo[i].nExpectedRows;
    }

    free(threadIds);
    for(int i=0; i<numThread; ++i){
        free(rowinfo[i].expectRows);
    }
    free(rowinfo);

    // 通过指针进行排序
    qsort(sortRows, nsortrows, sizeof(Row*), rowsCmp);

    for(int i=0; i<nsortrows; ++i){
        printf("%d,%d\n", sortRows[i]->a, sortRows[i]->b);
    }

    free(sortRows);
}


bool findBoundsA(const Row *rows, int leftvalue, int rightvalue,
                int startidx, int endidx, int *leftidx, int *rightidx){
    return findBoundsInternal(rows, leftvalue, rightvalue, startidx, endidx,
                              true, leftidx, rightidx);
}

bool findBoundsB(const Row *rows, int leftvalue, int rightvalue,
                 int startidx, int endidx, int *leftidx, int *rightidx){
    return findBoundsInternal(rows, leftvalue, rightvalue, startidx, endidx,
                              false, leftidx, rightidx);
}

/* parameters:
 *      leftvalue范围查找下边界值
 *      rightvalue范围查找的上边界值
 *      startidx起始查找索引
 *      endidx终止查找索引
 *      isA = true 查找a的边界， isA = false 查找b的边界
 *      leftidx, rightidx用于输出
 * return value:
 *      查找成功返回true, 否则返回false
 */
bool findBoundsInternal(const Row *rows, int leftvalue, int rightvalue,
                        int startidx, int endidx, bool isA, int *leftidx, int *rightidx){
    int sidx = startidx, eidx = endidx;
    int mididx;
    int lidx, ridx;
    int cmpval, offsize;

    if(isA){
        offsize = offsetof(Row, a);
    }else{
        offsize = offsetof(Row, b);
    }

    // 寻找左边界
    while(sidx <= eidx){
        mididx = (sidx+eidx)/2;
        cmpval = *(int *)((char *)&rows[mididx].a + offsize);
        if(cmpval < leftvalue){
            sidx = mididx + 1;
        }else{
            eidx = mididx - 1;
        }
    }
    lidx = sidx;

    // 寻找右边界
    sidx = lidx;
    eidx = endidx;
    while(sidx <= eidx){
        mididx = (sidx+eidx)/2;
        cmpval = *(int *)((char *)&rows[mididx].a + offsize);
        if(cmpval <= rightvalue){
            sidx = mididx + 1;
        }else{
            eidx = mididx - 1;
        }
    }
    ridx = eidx;

    if(ridx < lidx) return false;

    *leftidx = lidx;
    *rightidx = ridx;
    return true;
}

int rowsCmp(const void *arg1, const void *arg2){
    const Row *lhs = *(const Row **) arg1;
    const Row *rhs = *(const Row **) arg2;
    int res;

    if(lhs->b != rhs->b){
        res = lhs->b - rhs->b;
    }else{
        res = lhs->a - rhs->a;
    }

    return res;
}

int getCPUCores(void){
    return sysconf(_SC_NPROCESSORS_ONLN);
}

void *threadFnFindRow(void *arg){
    RowWithIdxs *rowinfo = (RowWithIdxs *)arg;
    const Row *rows = rowinfo->rows;
    int nrows = rowinfo->eidx - rowinfo->sidx + 1;
    int leftidxA, rightidxA;
    int startidxA = rowinfo->sidx;
    int endidxA = rowinfo->eidx;
    int *expectedA = rowinfo->expectA;
    int numA = rowinfo->nExpectA;
    int *expectedStartIdx;  // 保存搜寻结果的起始索引
    int *expectedEndIdx;   // 保存搜寻结果的末尾索引
    int sum = 0;
    const Row **expectRowsP;
    int expectRowsIdx = 0;

    if(nrows <= 0) return (void *)NULL;

    expectedStartIdx = malloc(numA * sizeof(int));
    expectedEndIdx = malloc(numA * sizeof(int));
    memset(expectedStartIdx, -1, numA * sizeof(int));
    memset(expectedEndIdx, -1, numA * sizeof(int));

    for(int i=0; i<numA; ++i){
        if(findBoundsA(rows, expectedA[i], expectedA[i], startidxA, endidxA, &leftidxA, &rightidxA)){
            int leftidxB, rightidxB;

            // 更新下次寻找a的起始索引
            startidxA = rightidxA + 1;

            if(findBoundsB(rows, 10, 49, leftidxA, rightidxA, &leftidxB, &rightidxB)){
                expectedStartIdx[i] = leftidxB;
                expectedEndIdx[i] = rightidxB;
                sum += rightidxB - leftidxB + 1;
            }
        }
    }

    // 复制符合条件的rows的指针
    expectRowsP = malloc(sum * sizeof(Row*));
    for(int i=0; i<numA; ++i){
        if(expectedStartIdx[i] == -1) continue;
        for(int j=expectedStartIdx[i]; j<=expectedEndIdx[i]; ++j){
            expectRowsP[expectRowsIdx++] = &rows[j];
        }
    }

    rowinfo->expectRows = expectRowsP;
    rowinfo->nExpectedRows = sum;

    free(expectedStartIdx);
    free(expectedEndIdx);
    return (void*) NULL;
}


/* --------------  以下为测试   ------------- */
void task1_test1(void);
void task1_test2(void);
void task1_test3(void);

void task2_test1(void);
void task2_test2(void);
void task2_test3(void);
void task2_test4(void);
void task2_test5(void);
void task2_test6(void);
void task2_test7(void);
void task2_test8(void);
void task2_test9(void);
void task2_test10(void);
void task2_test11(void);
void task2_test12(void);
void task2_test13(void);
void task2_test14(void);
void task2_test15(void);
void task2_test16(void);
void task2_test17(void);

void task3_test1(void);
void task3_test2(void);
void task3_test3(void);
void task3_test4(void);
void task3_test5(void);
void task3_test6(void);
void task3_test7(void);
void task3_test8(void);
void task3_test9(void);
void task3_test10(void);
void task3_test11(void);
void task3_test12(void);
void task3_test13(void);
void task3_test14(void);
void task3_test15(void);
void task3_test16(void);
void task3_test17(void);

void task4_test1(void);
void task4_test2(void);
void task4_test3(void);
void task4_test4(void);
void task4_test5(void);
void task4_test6(void);
void task4_test7(void);
void task4_test8(void);
void task4_test9(void);
void task4_test10(void);
void task4_test11(void);
void task4_test12(void);
void task4_test13(void);
void task4_test14(void);
void task4_test15(void);
void task4_test16(void);
void task4_test17(void);

void task1_test(void){
    task1_test1();
    task1_test2();
    task1_test3();

    printf("\n");
}

// nil
void task1_test1(void){
    Row rows[] = {};

    printf("task1_test1\n");
    task1(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task1_test2(void){
    Row rows[] = {{1000, 9}};

    printf("task1_test2\n");
    task1(rows, sizeof(rows)/sizeof(Row));
}

// 1000,10  2000,22, 3000,33
void task1_test3(void){
    Row rows[] = {{1000, 9}, {1000,10}, {1000,50}, {2000,22}, {3000,33}, {4000,44}};

    printf("task1_test3\n");
    task1(rows, sizeof(rows)/sizeof(Row));
}


void task2_test(void){
    task2_test1();
    task2_test2();
    task2_test3();
    task2_test4();
    task2_test5();
    task2_test6();
    task2_test7();
    task2_test8();
    task2_test9();
    task2_test10();
    task2_test11();
    task2_test12();
    task2_test13();
    task2_test14();
    task2_test15();
    task2_test16();
    task2_test17();

    printf("\n");
}

// nil
void task2_test1(void){
    Row rows[] = {};

    printf("task2_test1\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test2(void){
    Row rows[] = {{50,1}};

    printf("task2_test2\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test3(void){
    Row rows[] = {{1100,1}};

    printf("task2_test3\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test4(void){
    Row rows[] = {{1000, 9}};

    printf("task2_test4\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test5(void){
    Row rows[] = {{1000, 50}};

    printf("task2_test5\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// 1000,10
void task2_test6(void){
    Row rows[] = {{1000, 10}};

    printf("task2_test6\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test7(void){
    Row rows[] = {{50,1}, {500,3}};

    printf("task2_test7\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test8(void){
    Row rows[] = {{1100,1}, {1200,1}};

    printf("task2_test8\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test9(void){
    Row rows[] = {{50,1}, {1200,1}};

    printf("task2_test9\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test10(void){
    Row rows[] = {{1100,1}, {1200,1}};

    printf("task2_test10\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// 1000,49
void task2_test11(void){
    Row rows[] = {{1000,49}, {1200,1}};

    printf("task2_test11\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// 1000,49  1000,49
void task2_test12(void){
    Row rows[] = {{1000,49}, {1000,49}};

    printf("task2_test12\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test13(void){
    Row rows[] = {{700,49}, {800,49}, {900,49}};

    printf("task2_test13\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task2_test14(void){
    Row rows[] = {{1700,49}, {1800,49}, {1900,49}};

    printf("task2_test14\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// 1000,49  1000,49 1000,49
void task2_test15(void){
    Row rows[] = {{1000,49}, {1000,49}, {1000,49}};

    printf("task2_test15\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

// 1000,31  2000,22 2000,33
void task2_test16(void){
    Row rows[] = {{1000,31}, {1000,72}, {1500, 12}, {1500, 34}, {2000, 22}, {2000, 33}};

    printf("task2_test16\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}

/* 1000,10  1000,31  1000,31  1000,49  2000,10  2000,22  2000,22  2000,33
 * 2000,49  3000,10  3000,33  3000,49
 */
void task2_test17(void){
    Row rows[] = {{900,31}, {1000,10}, {1000,31}, {1000,31}, {1000,49}, {1000,72},
                  {1500, 12}, {1500, 34}, {2000, 10}, {2000, 22}, {2000, 22},
                  {2000, 33}, {2000, 49}, {3000, 9}, {3000, 10}, {3000, 33},
                  {3000, 49}, {3000, 50}};

    printf("task2_test17\n");
    task2(rows, sizeof(rows)/sizeof(Row));
}


void task3_test(void){
    task3_test1();
    task3_test2();
    task3_test3();
    task3_test4();
    task3_test5();
    task3_test6();
    task3_test7();
    task3_test8();
    task3_test9();
    task3_test10();
    task3_test11();
    task3_test12();
    task3_test13();
    task3_test14();
    task3_test15();
    task3_test16();
    task3_test17();

    printf("\n");
}

// nil
void task3_test1(void){
    Row rows[] = {};

    printf("task3_test1\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test2(void){
    Row rows[] = {{50,1}};

    printf("task3_test2\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test3(void){
    Row rows[] = {{1100,1}};

    printf("task3_test3\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test4(void){
    Row rows[] = {{1000, 9}};

    printf("task3_test4\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test5(void){
    Row rows[] = {{1000, 50}};

    printf("task3_test5\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// 1000,10
void task3_test6(void){
    Row rows[] = {{1000, 10}};

    printf("task3_test6\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test7(void){
    Row rows[] = {{50,1}, {500,3}};

    printf("task3_test7\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test8(void){
    Row rows[] = {{1100,1}, {1200,1}};

    printf("task3_test8\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test9(void){
    Row rows[] = {{50,1}, {1200,1}};

    printf("task3_test9\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test10(void){
    Row rows[] = {{1100,1}, {1200,1}};

    printf("task3_test10\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// 1000,49
void task3_test11(void){
    Row rows[] = {{1000,49}, {1200,1}};

    printf("task3_test11\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// 1000,49  1000,49
void task3_test12(void){
    Row rows[] = {{1000,49}, {1000,49}};

    printf("task3_test12\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test13(void){
    Row rows[] = {{700,49}, {800,49}, {900,49}};

    printf("task3_test13\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// nil
void task3_test14(void){
    Row rows[] = {{1700,49}, {1800,49}, {1900,49}};

    printf("task3_test14\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// 1000,49  1000,49 1000,49
void task3_test15(void){
    Row rows[] = {{1000,49}, {1000,49}, {1000,49}};

    printf("task3_test15\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

// 2000,22  1000,31  2000,33
void task3_test16(void){
    Row rows[] = {{1000,31}, {1000,72}, {1500, 12}, {1500, 34}, {2000, 22}, {2000, 33}};

    printf("task3_test16\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

/* 1000,10  2000,10  3000,10  2000,22  2000,22  1000,31  1000,31  2000,33
 * 3000,33  1000,49  2000,49  3000,49
 */
void task3_test17(void){
    Row rows[] = {{900,31}, {1000,10}, {1000,31}, {1000,31}, {1000,49}, {1000,72},
                  {1500, 12}, {1500, 34}, {2000, 10}, {2000, 22}, {2000, 22},
                  {2000, 33}, {2000, 49}, {3000, 9}, {3000, 10}, {3000, 33},
                  {3000, 49}, {3000, 50}};

    printf("task3_test17\n");
    task3(rows, sizeof(rows)/sizeof(Row));
}

void task4_test(void){
    task4_test1();
    task4_test2();
    task4_test3();
    task4_test4();
    task4_test5();
    task4_test6();
    task4_test7();
    task4_test8();
    task4_test9();
    task4_test10();
    task4_test11();
    task4_test12();
    task4_test13();
    task4_test14();
    task4_test15();
    task4_test16();
    task4_test17();

    printf("\n");
}

// nil
void task4_test1(void){
    Row rows[] = {};
    int expectA[] = {1000,2000,3000};

    printf("task4_test1 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test1 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test1 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test1 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test1 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test2(void){
    Row rows[] = {{50,1}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test2 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test2 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test2 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test2 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test2 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test3(void){
    Row rows[] = {{1100,1}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test3 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test3 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test3 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test3 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test3 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test4(void){
    Row rows[] = {{1000, 9}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test4 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test4 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test4 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test4 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test4 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test5(void){
    Row rows[] = {{1000, 50}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test5 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test5 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test5 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test5 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test5 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// 1000,10
void task4_test6(void){
    Row rows[] = {{1000, 10}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test6 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test6 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test6 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test6 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test6 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test7(void){
    Row rows[] = {{50,1}, {500,3}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test7 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test7 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test7 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test7 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test7 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test8(void){
    Row rows[] = {{1100,1}, {1200,1}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test8 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test8 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test8 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test8 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test8 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test9(void){
    Row rows[] = {{50,1}, {1200,1}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test9 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test9 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test9 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test9 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test9 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test10(void){
    Row rows[] = {{1100,1}, {1200,1}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test10 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test10 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test10 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test10 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test10 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// 1000,49
void task4_test11(void){
    Row rows[] = {{1000,49}, {1200,1}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test11 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test11 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test11 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test11 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test11 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// 1000,49  1000,49
void task4_test12(void){
    Row rows[] = {{1000,49}, {1000,49}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test12 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test12 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test12 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test12 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test12 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test13(void){
    Row rows[] = {{700,49}, {800,49}, {900,49}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test13 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test13 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test13 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test13 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test13 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// nil
void task4_test14(void){
    Row rows[] = {{1700,49}, {1800,49}, {1900,49}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test14 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test14 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test14 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test14 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test14 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// 1000,49  1000,49 1000,49
void task4_test15(void){
    Row rows[] = {{1000,49}, {1000,49}, {1000,49}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test15 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test15 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test15 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test15 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test15 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

// 2000,22  1000,31  2000,33
void task4_test16(void){
    Row rows[] = {{1000,31}, {1000,72}, {1500, 12}, {1500, 34}, {2000, 22}, {2000, 33}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test16 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test16 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test16 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test16 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test16 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

/* 1000,10  2000,10  3000,10  2000,22  2000,22  1000,31  1000,31  2000,33
 * 3000,33  1000,49  2000,49  3000,49
 */
void task4_test17(void){
    Row rows[] = {{900,31}, {1000,10}, {1000,31}, {1000,31}, {1000,49}, {1000,72},
                  {1500, 12}, {1500, 34}, {2000, 10}, {2000, 22}, {2000, 22},
                  {2000, 33}, {2000, 49}, {3000, 9}, {3000, 10}, {3000, 33},
                  {3000, 49}, {3000, 50}};
    int expectA[] = {1000,2000,3000};

    printf("task4_test17 thread num 1\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 1);

    printf("task4_test17 thread num 2\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 2);

    printf("task4_test17 thread num 3\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 3);

    printf("task4_test17 thread num 5\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 5);

    printf("task4_test17 thread num default\n");
    task4(rows, sizeof(rows)/sizeof(Row), expectA, sizeof(expectA)/sizeof(int), 0);
}

