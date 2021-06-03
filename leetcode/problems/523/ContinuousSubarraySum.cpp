#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int size = nums.size();
        if(size < 2) return false;
        unordered_map<int,int> remaindermap;
        remaindermap[0] = -1;
        int remainder = 0;
        for(int i=0; i<size; ++i){
            remainder = (remainder + nums[i])%k;
            if(remaindermap.count(remainder)){
                if(i - remaindermap[remainder] >= 2) return true;
            }else{
                remaindermap[remainder] = i;
            }
        }
        return false;
    }
};


int main(void){
    Solution s;
    vector<int> input;
    int k;

    input = {23,2,4,6,7};
    k = 6;
    cout << s.checkSubarraySum(input, k) << endl;

    input = {23,2,6,4,7};
    k = 6;
    cout << s.checkSubarraySum(input, k) << endl;

    input = {23};
    k = 1;
    cout << s.checkSubarraySum(input, k) << endl;

    input = {23,0};
    k = 2;
    cout << s.checkSubarraySum(input, k) << endl;

    input = {23,0};
    k = 1;
    cout << s.checkSubarraySum(input, k) << endl;

    return 0;
}
