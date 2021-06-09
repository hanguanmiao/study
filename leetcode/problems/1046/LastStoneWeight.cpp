#include <vector>
#include <set>
#include <iostream>

using namespace std;

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        multiset<int> stonesset(stones.begin(), stones.end());

        while(stonesset.size() >= 2){
            multiset<int>::iterator it1 = stonesset.end();
            --it1;
            multiset<int>::iterator  it2 = stonesset.end();
            --it2;--it2;

            int i1 = *it1, i2 = *it2;

            stonesset.erase(it2, stonesset.end());
            if(i1 > i2) swap(i1, i2);
            if(i2 != i1)stonesset.insert(i2 - i1);
        }

        return stonesset.empty() ? 0 : (*stonesset.begin());
    }
};


int main(void){
    Solution s;
    vector<int> input;

    input = {2,7,4,1,8,1};
     cout << s.lastStoneWeight(input) << endl;

     return 0;
}
