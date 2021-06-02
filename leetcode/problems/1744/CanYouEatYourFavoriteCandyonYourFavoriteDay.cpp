#include <vector>
#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        int candysize = candiesCount.size();
        vector<long long> sumarr(candysize+1);
        long sum =0;
        for(int i=0; i<candysize; ++i){
            sum += candiesCount[i];
            sumarr[i+1] = sum;
        }

        int queriessize = queries.size();
        vector<bool> eatarr(queriessize);
        for(int i=0; i< queriessize; ++i){
            vector<int> &query  = queries[i];
            long long min = query[1]+1;
            long long max = (long long)(query[1]+1) * query[2];
            if(min > sumarr[query[0]+1] || max <= sumarr[query[0]]){
                eatarr[i] = false;
            }else{
                eatarr[i] = true;
            }
        }

        return eatarr;
    }
};



int main(void){
    Solution s;
    vector<int> candies;
    vector<vector<int>> input;
    vector<bool> res;

    candies = {7,4,5,3,8};
    input = {{0,2,2},{4,2,4},{2,13,1000000000}};
    res = s.canEat(candies, input);
    for(auto val : res){
        cout << val << ' ';
    }
    cout << endl;

    candies = {5,2,6,4,1};
    input = {{3,1,2},{4,10,3},{3,10,100},{4,100,30},{1,3,1}};
    res = s.canEat(candies, input);
    for(auto val : res){
        cout << val << ' ';
    }
    cout << endl;


    return 0;
}
