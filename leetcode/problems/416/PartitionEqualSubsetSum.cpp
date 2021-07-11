#include <iostream>
#include <vector>
#include <numeric>

using namespace std;


class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.cbegin(), nums.cend(), 0);
        if(sum%2) return false;
        sum /= 2;

        vector<bool> targts(sum + 1);
        targts[0] = true;
        for (auto &num : nums) {
            for(int i = static_cast<int>(targts.size()) - 1; i>=num; --i){
                targts[i] = targts[i] | targts[i-num];
            }
        }
        return targts[sum];
    }
};



int main(void){
    Solution s;
    vector<int> input;

    input = {1};
    cout << s.canPartition(input) << endl; // false

    input = {11,4}; // odd
    cout << s.canPartition(input) << endl; // false

    input = {1,5}; // even
    cout << s.canPartition(input) << endl; // false

    input = {5,5};
    cout << s.canPartition(input) << endl; // true

    input = {1,5,11};
    cout << s.canPartition(input) << endl; // flase

    input = {1,5,12};
    cout << s.canPartition(input) << endl; // false

    input = {10,1,11};
    cout << s.canPartition(input) << endl; // true

    input = {1,5,11,5};
    cout << s.canPartition(input) << endl; // true

    input = {1,5,11,5};
    cout << s.canPartition(input) << endl; // true

    input = {1,2,3,5};
    cout << s.canPartition(input) << endl; // false;


    return 0;
}
