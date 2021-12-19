#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

class Solution {
public:
    int threeSumClosest(std::vector<int>& nums, int target) {
        int size = static_cast<int>(nums.size());
        int ressum = 0;
        int curdiff = INT_MAX;

        sort(nums.begin(), nums.end());

        for(int i=0; i<size-2; ++i){
            if(i>0 && nums[i-1] == nums[i]) continue;

            int curtarget = target - nums[i];

            for(int j=i+1, k = size-1; j<k; ++j){
                while(curtarget < nums[j] + nums[k] && j<k){
                    --k;
                }

                int tmpdiff;

                if(k != size-1){
                    if((tmpdiff = nums[j] + nums[k+1] - curtarget) < curdiff){
                        curdiff = tmpdiff;
                        ressum = nums[i] + nums[j] + nums[k+1];
                    }
                }

                if(j<k && (tmpdiff = curtarget - nums[j] - nums[k]) < curdiff){
                    curdiff = tmpdiff;
                    ressum = nums[i] + nums[j] + nums[k];
                }

                if(!curdiff) break;
            }

            if(!curdiff) break;
        }

        return ressum;
    }
};


void test(void);
void test1(void);
void test2(void);
void test3(void);
void test4(void);

int main(void){
    test();
    return 0;
}


void test(void){
//    test1();
//    test2();
//    test3();
    test4();
}

void test1(void){
    Solution s;
    std::vector<int> input({-1,2,1,-4});
    int target = 1;

    std::cout << s.threeSumClosest(input, target) << std::endl;
}

void test2(void){
    Solution s;
    std::vector<int> input({0,0,0});
    int target = 1;

    std::cout << s.threeSumClosest(input, target) << std::endl;
}

void test3(void){
    Solution s;
    std::vector<int> input({0,1,2});
    int target = 0;

    std::cout << s.threeSumClosest(input, target) << std::endl;
}

void test4(void){
    Solution s;
    std::vector<int> input({1,1,1,0});
    int target = 100;

    std::cout << s.threeSumClosest(input, target) << std::endl;
}
