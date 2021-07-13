#include <vector>
#include <iostream>
#include <numeric>

using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.cbegin(), nums.cend(), 0);
        int abstarget = abs(target);
        if(abstarget > sum){
            return 0;
        }

        if(((abstarget&1) ^ (sum&1))) return 0; // 判断同奇同偶

        int size = nums.size();
        int indeed = (sum + target)/2;
        vector<int> ret(indeed+1, 0);
        ret[0] = 1;
        for(int i=0; i<size; ++i){
            int num = nums[i];
            for(int j=indeed; j>=num; --j){
                ret[j] += ret[j-num];
            }
        }
        return ret[indeed];
    }
};


int main(void){
    vector<int> input;
    Solution s;

    input = {1};
    cout << s.findTargetSumWays(input, 1) << endl; // 1

    input = {1};
    cout << s.findTargetSumWays(input, 2) << endl; // 0

    input = {1, 0};
    cout << s.findTargetSumWays(input, 1) << endl; // 2

    input = {2,2,4};
    cout << s.findTargetSumWays(input, 4) << endl; // 2

    input = {2,2,0,4};
    cout << s.findTargetSumWays(input, 4) << endl; // 4

    input = {1,1,1,1,1};
    cout << s.findTargetSumWays(input, 3) << endl; // 5

    input = {1,1,1,1,1,1};
    cout << s.findTargetSumWays(input, 3) << endl; // 0

    input = {1,2,3,4,5,6,7};
    cout << s.findTargetSumWays(input, 12) << endl; // 5

    return 0;
}
