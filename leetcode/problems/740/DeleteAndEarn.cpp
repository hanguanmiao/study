#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int maxval = nums[0];

        for (int i = 1; i < static_cast<int>(nums.size()); ++i) {
            maxval = max(maxval, nums[i]);
        }

        vector<int> sums(maxval+1);
        for(auto val : nums){
            sums[val] += val;
        }

        int earn1 = sums[0], earn2 = sums[1];
        for(int i = 2; i<static_cast<int>(sums.size()); ++i){
            int tmp = earn2;
            earn2 = max(earn2, earn1+sums[i]);
            earn1 = tmp;
        }
        return earn2;
    }
};

int main(void){
    vector<int> input;
    Solution s;

//    input = {3};
//    cout << s.deleteAndEarn(input)<<endl;

//    input = {3,4};
//    cout << s.deleteAndEarn(input)<<endl;

//    input = {3,4,2};
//    cout << s.deleteAndEarn(input)<<endl;

//    input = {2,2,3,3,3,4};
//    cout << s.deleteAndEarn(input)<<endl;

    input = {2,2,3,3,3,4,4,0,5};
    cout << s.deleteAndEarn(input)<<endl;

    return 0;
}
