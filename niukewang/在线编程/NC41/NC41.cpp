#include <map>
#include <vector>
#include <iostream>

// g++ -std=c++11 -Wall -Wextra -g -O0 NC41.cpp

class Solution {
public:
    /**
     *
     * @param arr int整型vector the array
     * @return int整型
     */
    int maxLength(std::vector<int>& arr) {
        std::map<int, int> subarr;
        int size = static_cast<int>(arr.size());
        int maxlen = 0;
        int subsize;
        int leftidx = 0;

        for(int i=0; i<size; ++i){
            std::map<int, int>::iterator it = subarr.find(arr[i]);
            if(it != subarr.end()){
                subsize = static_cast<int>(subarr.size());
                if(maxlen < subsize){
                    maxlen = subsize;
                }

                for(;leftidx <= it->second; ++leftidx){
                    subarr.erase(arr[leftidx]);
                }
            }
            subarr.insert(std::pair<int,int>{arr[i],i});
        }

        subsize = static_cast<int>(subarr.size());
        if(maxlen < subsize){
            maxlen = subsize;
        }

        return maxlen;
    }
};


void test(void);
void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void test8(void);
void test9(void);
void test10(void);



int main(void){
    test();

    return 0;
}


void test(void){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
}

// 4
void test1(void){
    Solution s;
    std::vector<int> arr = {2,3,4,5};

    std::cout << s.maxLength(arr) << std::endl;
}

// 3
void test2(void){
    Solution s;
    std::vector<int> arr = {2,2,3,4,3};

    std::cout << s.maxLength(arr) << std::endl;
}

// 1
void test3(void){
    Solution s;
    std::vector<int> arr = {9};

    std::cout << s.maxLength(arr) << std::endl;
}

// 3
void test4(void){
    Solution s;
    std::vector<int> arr = {1,2,3,1,2,3,2,2};

    std::cout << s.maxLength(arr) << std::endl;
}

// 5
void test5(void){
    Solution s;
    std::vector<int> arr = {2,2,3,4,8,99,3};

    std::cout << s.maxLength(arr) << std::endl;
}

// 0
void test6(void){
    Solution s;
    std::vector<int> arr = {};

    std::cout << s.maxLength(arr) << std::endl;
}

// 1
void test7(void){
    Solution s;
    std::vector<int> arr = {2,2};

    std::cout << s.maxLength(arr) << std::endl;
}

// 1
void test8(void){
    Solution s;
    std::vector<int> arr = {2,2,2};

    std::cout << s.maxLength(arr) << std::endl;
}

// 4
void test9(void){
    Solution s;
    std::vector<int> arr = {2,3,4,5,3};

    std::cout << s.maxLength(arr) << std::endl;
}


// 5
void test10(void){
    Solution s;
    std::vector<int> arr = {4,3,2,1,2,3,4,5};

    std::cout << s.maxLength(arr) << std::endl;
}

