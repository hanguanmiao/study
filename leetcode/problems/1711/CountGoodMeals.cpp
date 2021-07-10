#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:

    int countPairs(vector<int>& deliciousness) {
        vector<int>::const_iterator maxDeliciIt = max_element(deliciousness.cbegin(), deliciousness.cend());
        int maxSum = (*maxDeliciIt) << 1;
        unordered_map<int,int> delicmap;
        int count = 0;

        for(int i =0, size = deliciousness.size(); i<size; ++i){
            for(int power2 = 1; power2 <= maxSum; power2 <<= 1){
                if(deliciousness[i] <= power2 && delicmap.count(power2-deliciousness[i])) {
                    count = (count + delicmap[power2-deliciousness[i]])%(1000000007);
                }
            }
            ++delicmap[deliciousness[i]];
        }
        return count;
    }
};


int main(void){
    vector<int> input;
    Solution s;

    input = {1};
    cout << s.countPairs(input) << endl; // 0

    input = {1,3};
    cout << s.countPairs(input) << endl; // 1

    input = {8,8};
    cout << s.countPairs(input) << endl; // 1

    input = {1048576,1048576};
    cout << s.countPairs(input) << endl; // 1

    input = {8,8, 8};
    cout << s.countPairs(input) << endl; // 3

    input = {1,3,5,7,9};
    cout << s.countPairs(input) << endl; // 4

    input = {1,1,1,3,3,3,7};
    cout << s.countPairs(input) << endl; // 15

    input = {1,1,1,3,3,3,7,0};
    cout << s.countPairs(input) << endl; // 18

    input = {1,1,1,3,3,3,8,8};
    cout << s.countPairs(input) << endl; // 15

    return 0;
}

