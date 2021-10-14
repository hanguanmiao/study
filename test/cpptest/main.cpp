#include <iostream>

//g++ -std=c++11 -Wall -Wextra -g -O0 main.cpp

typedef struct Row
{
    int a;
    int b;
}Row;

void task1(const Row *rows, int nrows);
void task2(const Row *rows, int nrows);

bool findBounds(const Row *rows, int leftvalue, int rightvalue,
                int startidx, int lastidx, int *leftidx, int *rightidx);
//bool findLeftBoundA(const Row *rows, int leftvalue, int startidx, int endidx, int *leftidx);
//bool findRightBoundA(const Row *rows, int rightvalue, int startidx, int endidx, int *rightidx);

void task1_test(void);
void task1_test1(void);
void task1_test2(void);
void task1_test3(void);

void task2_test(void);
void task2_test1(void);
void task2_test2(void);
void task2_test3(void);
void task2_test4(void);
void task2_test5(void);
void task2_test6(void);



int main(void){
    task1_test();
    task2_test();

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
    int leftidxA, rightidxA;

    if(nrows <= 0) return;

    if(findBounds(rows, 1000, 1000, 0, nrows-1, &leftidxA, &rightidxA)){
        std::cout << leftidxA << ',' <<rightidxA;
    }
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
bool findBounds(const Row *rows, int leftvalue, int rightvalue,
                int startidx, int endidx, int *leftidx, int *rightidx){
    int sidx = startidx, eidx = endidx;
    int mididx;
    int lidx, ridx;

    // 寻找左边界
    while(sidx <= eidx){
        mididx = (sidx+eidx)/2;
        if(rows[mididx].a < leftvalue){
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
        if(rows[mididx].a <= rightvalue){
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


/* parameters:
 *      leftvalue范围查找下边界值
 *      rightvalue范围查找的上边界值
 *      startidx起始查找索引
 *      endidx终止查找索引
 *      isA = true 查找a的边界， isA = false 查找b的边界
 */
//bool findBounds(const Row *rows, int leftvalue, int rightvalue,
//                int startidx, int endidx, bool isA, int *leftidx, int *rightidx){
//    assert(leftvalue <= rightvalue);
//    if(findLeftBoundA(rows, leftvalue, startidx, endidx, leftidx) &&
//            findRightBoundA(rows, rightvalue, *leftidx, endidx, rightidx)){
//        return true;
//    }

//    return false;
//}

//bool findLeftBoundA(const Row *rows, int leftvalue, int startidx, int endidx,
//                    int *leftidx){
//    int sidx = startidx, eidx = endidx;
//    int mididx;
//    bool found = false;

//    while(sidx <= eidx){
//        mididx = (sidx + eidx)/2;
//        if(rows[mididx].a < leftvalue){
//            sidx = mididx + 1;
//        }else if(rows[mididx].a > leftvalue){
//            eidx = mididx - 1;
//        }else{
//            found = true;
//            eidx = mididx;
//            while (sidx < eidx) {
//                mididx = (sidx + eidx)/2;
//                if(rows[mididx].a < leftvalue){
//                    sidx = mididx + 1;
//                }else if(rows[mididx].a == leftvalue){
//                    eidx = mididx - 1;
//                }else{ // it's not possible
//                    std::cout << "wrong order. idx:" << mididx << ",value:"
//                              << rows[mididx].a << ", idx:" << eidx << ",value:"
//                              << rows[eidx].a << std::endl;
//                    exit(1);
//                }
//            }
//            *leftidx = sidx;
//        }
//    }

//    return found;
//}

//bool findRightBoundA(const Row *rows, int rightvalue, int startidx, int endidx, int *rightidx){
//    int sidx = startidx, eidx = endidx;
//    int mididx;
//    bool found = false;

//    while(sidx <= eidx){
//        mididx = (sidx + eidx)/2;
//        if(rows[mididx].a < leftvalue){
//            sidx = mididx + 1;
//        }else if(rows[mididx].a > leftvalue){
//            eidx = mididx - 1;
//        }else{
//            found = true;
//            eidx = mididx;
//            while (sidx < eidx) {
//                mididx = (sidx + eidx)/2;
//                if(rows[mididx].a < leftvalue){
//                    sidx = mididx + 1;
//                }else if(rows[mididx].a == leftvalue){
//                    eidx = mididx - 1;
//                }else{ // it's not possible
//                    std::cout << "wrong order. idx:" << mididx << ",value:"
//                              << rows[mididx].a << ", idx:" << eidx << ",value:"
//                              << rows[eidx].a << std::endl;
//                    exit(1);
//                }
//            }
//            *leftidx = sidx;
//        }
//    }

//    return found;
//}


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

    std::cout << std::endl;
}

void task2_test1(void){
    Row rows[] = {};

    std::cout << "task2_test1" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test2(void){
    Row rows[] = {{50,1}};

    std::cout << "task2_test2" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test3(void){
    Row rows[] = {{1100,1}};

    std::cout << "task2_test3" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test4(void){
    Row rows[] = {{50,1}, {500,3}};

    std::cout << "task2_test4" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test5(void){
    Row rows[] = {{1100,1}, {1200,1}};

    std::cout << "task2_test5" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test6(void){
    Row rows[] = {{50,1}, {1200,1}};

    std::cout << "task2_test6" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test7(void){
    Row rows[] = {{1000, 9}};

    std::cout << "task2_test7" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test8(void){
    Row rows[] = {{50,1}, {1200,1}};

    std::cout << "task2_test8" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test9(void){
    Row rows[] = {{50,1}, {1200,1}};

    std::cout << "task2_test9" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}

void task2_test10(void){
    Row rows[] = {{1000,31}, {1000,72}, {1500, 12}, {1500, 34}, {2000, 22}, {2000, 33}};

    std::cout << "task2_test10" << std::endl;
    task2(rows, sizeof(rows)/sizeof(Row));
}
