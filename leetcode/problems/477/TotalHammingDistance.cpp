#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int totalHammingDistance(vector<int>& nums) {
        int total = 0;
        int size = nums.size();

        for(int i=0; i< size-1;++i){
            for(int j=i+1;j<size;++j){
                total += HammingDistance(nums[i], nums[j]);
            }
        }
        return total;
    }

private:
    int HammingDistance(int num1, int num2){
        int xornum = num1 ^ num2;
        int count = 0;
        while(xornum){
            if(xornum & 1) ++count;
            xornum >>= 1;
        }
        return count;
    }
};


int main(void){
    Solution s;
    vector<int> input;

//    input = vector<int>({4,14,2});
//    cout << s.totalHammingDistance(input) << endl;

//    input = vector<int>({4,14,4});
//    cout << s.totalHammingDistance(input) << endl;

    input = vector<int>({4,14,4,14});
    cout << s.totalHammingDistance(input) << endl;
}
