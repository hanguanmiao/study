#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int count = 0;
        findTargetSumWaysInternal(nums, 0, target, 0, count);
        return count;
    }
private:
    void findTargetSumWaysInternal(vector<int>& nums, int idx, int target, int sum, int &count){
        int sum1 = sum + nums[idx];
        int sum2 = sum - nums[idx++];
        if(idx == static_cast<int>(nums.size())){
            if(sum1 == target){
                ++count;
            }
            if(sum2 == target){
                ++count;
            }
        }else{
            findTargetSumWaysInternal(nums, idx, target, sum1, count);
            findTargetSumWaysInternal(nums, idx, target, sum2, count);
        }
    }
};


int main(void){
    vector<int> input;
    Solution s;

    input = {1};
    cout << s.findTargetSumWays(input, 1) << endl; // 1

    input = {1};
    cout << s.findTargetSumWays(input, 2) << endl; // 0

    input = {1,1,1,1,1};
    cout << s.findTargetSumWays(input, 3) << endl; // 5

    input = {1,1,1,1,1,1};
    cout << s.findTargetSumWays(input, 3) << endl; // 0

    input = {1,2,3,4,5,6,7};
    cout << s.findTargetSumWays(input, 12) << endl; // 5

    return 0;
}
