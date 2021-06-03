#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        for(auto &num : nums){
            if(!num) num = -1;
        }

        unordered_map<int,int> prefixmap;
        prefixmap[0] = -1;
        int presum = 0;
        int ret = 0;
        for(int i=0; i<static_cast<int>(nums.size()); ++i){
            presum += nums[i];
            if(prefixmap.count(presum)){
                int diff = i - prefixmap[presum];
                if(diff > ret) ret = diff;
            }else{
                prefixmap[presum] = i;
            }
        }

        return ret;
    }
};


int main(void){
    vector<int> input;
    Solution s;

    input = {0};
    cout << s.findMaxLength(input) << endl; // 0

    input = {0,1};
    cout << s.findMaxLength(input) << endl; // 2

    input = {0,0};
    cout << s.findMaxLength(input) << endl; // 0

    input = {0,1,0};
    cout << s.findMaxLength(input) << endl; // 2

    input = {0,1,0,0,1,1};
    cout << s.findMaxLength(input) << endl; // 6

    input = {0,0,1,0,0,0,1,1};
    cout << s.findMaxLength(input) << endl; // 6

    return 0;
}
