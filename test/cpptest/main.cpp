#include <iostream>

//g++ -std=c++11 -Wall -Wextra -g -O0 main.cpp

typedef struct Row
{
    int a;
    int b;
}Row;

void task1(const Row *rows, int nrows);
void task2(const Row *rows, int nrows);

void findBounds(const Row *rows, int nrows, int leftvalue, int rightvalue, int startidx, int lastidx,
                bool isA, int *leftidx, int *rightidx);

void task1_test(void);
void task1_test1(void);
void task1_test2(void);
void task1_test3(void);

void task2_test(void);
void task2_test1(void);
void task2_test2(void);
void task2_test3(void);

// 用例
// 不存在
// 700， 800，900

int main(void){
    task1_test();

    return 0;
}

void task1(const Row *rows, int nrows){
    for(int i=0; i<nrows; ++i){
        if((rows[i].b >= 10 && rows[i].b < 50) &&
                (rows[i].a == 1000 || rows[i].a == 2000 || rows[i].a == 3000)){
            std::cout << rows[i].a << ',' << rows[i].b << std::endl;
        }
    }
}

void task2(const Row *rows, int nrows){
    if(nrows <= 0) return;


}

/* parameters:
 *      leftvalue范围查找下边界值
 *      rightvalue范围查找的上边界值
 *      startidx起始查找索引
 *      endidx终止查找索引
 *      isA = true 查找a的边界， isA = false 查找b的边界
 */
void findBounds(const Row *rows, int nrows, int leftvalue, int rightvalue,
                int startidx, int endidx, bool isA, int *leftidx, int *rightidx){
    int sidx = startidx, eidx = endidx;
    int mididx;

    while(sidx <= eidx){
        mididx = (sidx + eidx)/2;
        if(rows[mididx] < leftvalue){

        }else if(rows[mididx] > leftvalue){

        }else{

        }
    }
}


void task1_test(void){
    task1_test1();
    task1_test2();
    task1_test3();

    std::cout << std::endl;
}

void task1_test1(void){
    Row rows[] = {};

    std::cout << "task1_test1" << std::endl;
    task1(rows, sizeof(rows)/sizeof(Row));
}

void task1_test2(void){
    Row rows[] = {{1000, 9}};

    std::cout << "task1_test2" << std::endl;
    task1(rows, sizeof(rows)/sizeof(Row));
}

void task1_test3(void){
    Row rows[] = {{1000, 9}, {1000,10}, {1000,50}, {2000,22}, {3000,33}, {4000,44}};

    std::cout << "task1_test3" << std::endl;
    task1(rows, sizeof(rows)/sizeof(Row));
}

