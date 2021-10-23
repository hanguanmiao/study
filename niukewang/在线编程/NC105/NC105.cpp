#include <vector>
#include <iostream>

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 如果目标值存在返回下标，否则返回 -1
     * @param nums int整型vector
     * @param target int整型
     * @return int整型
     */
    int search(std::vector<int>& nums, int target) {
        if(nums.empty()) return -1;

        int numsize = static_cast<int>(nums.size());
        int leftidx = 0, rightidx = numsize - 1;

        while (leftidx <= rightidx) {
            int mididx = (leftidx + rightidx)/2;
            if(nums[mididx] < target){
                leftidx = mididx + 1;
            }else {
                rightidx = mididx - 1;
            }
        }

        if(leftidx == numsize || nums[leftidx] != target) return -1;

        return leftidx;
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

int main(void){
    test();
}


void test(void){
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
}

void test1(void){
    Solution s;
    std::vector<int> nums;
    int target = 10;

    std::cout<< s.search(nums, target) << std::endl;
}

void test2(void){
    Solution s;
    std::vector<int> nums{5};
    int target = 1;

    std::cout<< s.search(nums, target) << std::endl;
}

void test3(void){
    Solution s;
    std::vector<int> nums{5};
    int target = 5;

    std::cout<< s.search(nums, target) << std::endl;
}

void test4(void){
    Solution s;
    std::vector<int> nums{5};
    int target = 10;

    std::cout<< s.search(nums, target) << std::endl;
}

void test5(void){
    Solution s;
    std::vector<int> nums{1,2,4,4,5};
    int target = 4;

    std::cout<< s.search(nums, target) << std::endl;
}

void test6(void){
    Solution s;
    std::vector<int> nums{1,2,4,4,5};
    int target = 3;

    std::cout<< s.search(nums, target) << std::endl;
}

void test7(void){
    Solution s;
    std::vector<int> nums{1,1,1,1,1};
    int target = 1;

    std::cout<< s.search(nums, target) << std::endl;
}
