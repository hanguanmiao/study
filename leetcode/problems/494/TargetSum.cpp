#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) {
        int sum = 0;
        for (int& num : nums) {
            sum += num;
        }
        int diff = sum - target;
        if (diff < 0 || diff % 2 != 0) {
            return 0;
        }
        int neg = diff / 2;
        vector<int> dp(neg + 1);
        dp[0] = 1;
        for (int& num : nums) {
            for (int j = neg; j >= num; j--) {
                dp[j] += dp[j - num];
            }
        }
        return dp[neg];
    }
};


int main(void){
    vector<int> input;
    Solution s;

    input = {1,2,3,4,5,6,7};
    cout << s.findTargetSumWays(input, 12) << endl;

    return 0;
}
