#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        std::sort(nums.begin(), nums.end());
        int size = static_cast<int>(nums.size());

        for(int i=0; i<size; ++i){
            if(i > 0 && nums[i] == nums[i-1]) continue;

            int k = size-1;
            int target = -nums[i];
            for(int j=i+1; j<size; ++j){
                if(j > i+1 && nums[j] == nums[j-1]) continue;

                while(k > j && nums[j] + nums[k] > target){
                    --k;
                }

                if(j >= k) break;

                if(nums[j] + nums[k] == target){
                    ans.push_back({nums[i], nums[j], nums[k]});
                }
            }
        }
        return ans;
    }
};



void test(void);
void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);

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
}


void test1(void){
    std::vector<int> input = {-1,0,1,2,-1,-4};
    std::vector<std::vector<int>> res;
    Solution s;

    res = s.threeSum(input);

    for(auto &vals : res) {
        for(auto num : vals){
            std::cout << num << ',';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test2(void){
    std::vector<int> input;
    std::vector<std::vector<int>> res;
    Solution s;

    res = s.threeSum(input);

    for(auto &vals : res) {
        for(auto num : vals){
            std::cout << num << ',';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


void test3(void){
    std::vector<int> input(0);
    std::vector<std::vector<int>> res;
    Solution s;

    res = s.threeSum(input);

    for(auto &vals : res) {
        for(auto num : vals){
            std::cout << num << ',';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test4(void){
    std::vector<int> input = {-1,0,1,0,0,2,-1,-4};
    std::vector<std::vector<int>> res;
    Solution s;

    res = s.threeSum(input);

    for(auto &vals : res) {
        for(auto num : vals){
            std::cout << num << ',';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void test5(void){
    std::vector<int> input = {0,0,0,0};
    std::vector<std::vector<int>> res;
    Solution s;

    res = s.threeSum(input);

    for(auto &vals : res) {
        for(auto num : vals){
            std::cout << num << ',';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
