#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int total = 0;
        int size = nums.size();
        int times = 30;
        int mask = 1;

        while(times--){
            int count = 0;
            for(int num : nums){
                if(num & mask) ++count;
            }
            total += (size - count) * count;
            mask <<= 1;
        }

        return total;
    }
};


int main(void){
    Solution s;
    vector<int> input;

    input = vector<int>({4,14,2});
    cout << s.totalHammingDistance(input) << endl;

    input = vector<int>({4,14,4});
    cout << s.totalHammingDistance(input) << endl;

    input = vector<int>({4,14,4,14});
    cout << s.totalHammingDistance(input) << endl;
}
