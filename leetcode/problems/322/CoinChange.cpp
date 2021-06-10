#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        std::sort(coins.begin(), coins.end());
        int size = coins.size();
        int count = 0;
        queue<int> pq;
        do{
        for(int i=size-1;i>=0; --i){
            while (amount > 0) {
                amount -= coins[i];
                ++count;
            }
            if(!amount) return count;
            amount += coins[i];
            --count;
        }
        }while(!pq.empty());
        return -1;
    }
};

int main(void){
    vector<int> input;
    Solution s;
    int amount;

    input = {1,5,2};
    amount = 11;
    cout << s.coinChange(input, amount) << endl; // 3

    input = {2};
    amount = 3;
    cout << s.coinChange(input, amount) << endl; // -1

    input = {1};
    amount = 0;
    cout << s.coinChange(input, amount) << endl; // 0

    input = {1};
    amount = 1;
    cout << s.coinChange(input, amount) << endl; // 1

    input = {1};
    amount = 2;
    cout << s.coinChange(input, amount) << endl; // 2

    input = {186,419,83,408};
    amount = 6249;
    cout << s.coinChange(input, amount) << endl; // 20

    input = {9,6,1};
    amount = 12;
    cout << s.coinChange(input, amount) << endl; // 2

    return 0;
}
