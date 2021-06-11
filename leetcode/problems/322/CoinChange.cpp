#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

//class Solution {
//public:
//    int coinChange(vector<int>& coins, int amount) {
//        vector<int> dp(amount + 1);
//        return coinChangeRecursive(coins, amount , dp);
//    }

//private:
//    int coinChangeRecursive(vector<int>& coins, int amount, vector<int> &dp){
//        if(amount < 0) return -1;
//        if(!amount) return 0;
//        int size = coins.size();
//        int count = INT_MAX;
//        for(int i=0; i<size; ++i){
//            if(amount >= coins[i]){
//                int diff = amount - coins[i];
//                if(dp[diff] == -1) continue;
//                if(!dp[diff]){
//                    int tmp = coinChangeRecursive(coins, diff, dp);
//                    if(tmp != -1 && tmp < count) count = tmp + 1;
//                }else{
//                    if(dp[diff] + 1 < count) count = dp[diff] + 1;
//                }
//            }else{
//                continue;
//            }
//        }
//        dp[amount] = (count==INT_MAX) ? -1 : count;
//        return dp[amount];
//    }
//};

//class Solution {
//public:
//    int coinChange(vector<int>& coins, int amount) {
//        vector<int> dp(amount+1);
//        for(int i=1; i<=amount; ++i){
//            int mincount = INT_MAX;
//            for(int j=0; j<static_cast<int>(coins.size()); ++j){
//                int diff = i - coins[j];
//                if(diff >= 0) {
//                    int tmp = dp[diff] + 1;
//                    if(dp[diff] >=0 && tmp < mincount) mincount = tmp;
//                }
//            }
//            dp[i] = (mincount == INT_MAX) ? -1 : mincount;
//        }
//        return dp[amount];
//    }
//};

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int Max = amount + 1;
        vector<int> dp(amount + 1, Max);
        dp[0] = 0;
        for (int i = 1; i <= amount; ++i) {
            for (int j = 0; j < (int)coins.size(); ++j) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};


int main(void){
    vector<int> input;
    Solution s;
    int amount;

//    input = {1,5,2};
//    amount = 11;
//    cout << s.coinChange(input, amount) << endl; // 3

//    input = {2};
//    amount = 3;
//    cout << s.coinChange(input, amount) << endl; // -1

//    input = {1};
//    amount = 0;
//    cout << s.coinChange(input, amount) << endl; // 0

//    input = {1};
//    amount = 1;
//    cout << s.coinChange(input, amount) << endl; // 1

//    input = {1};
//    amount = 2;
//    cout << s.coinChange(input, amount) << endl; // 2

//    input = {186,419,83,408};
//    amount = 6249;
//    cout << s.coinChange(input, amount) << endl; // 20

//    input = {9,6,1};
//    amount = 12;
//    cout << s.coinChange(input, amount) << endl; // 2

    input = {2,4,5};
    amount = 9;
    cout << s.coinChange(input, amount) << endl; // 3

    return 0;
}
