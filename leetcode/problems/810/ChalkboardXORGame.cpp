#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool xorGame(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        int xorsum = 0;
        for(int i=0; i<size; ++i){
            xorsum ^= nums[i];
        }
        if(!xorsum) return true;
        if(size%2) return false;
        return true;
    }

};


int main (void){
    Solution s;
    vector<int> input;

    input = vector<int>({0});
    cout<<s.xorGame(input)<<endl; // 1

    input = vector<int>({1,1,2});
    cout<<s.xorGame(input)<<endl; // 0

    input = vector<int>({0,2,2,1});
    cout<<s.xorGame(input)<<endl; // 1

    input = vector<int>({1,0,2,2});
    cout<<s.xorGame(input)<<endl; // 1

    input = vector<int>({1,1,2,3,4});
    cout<<s.xorGame(input)<<endl; // 0

    return 0;
}
