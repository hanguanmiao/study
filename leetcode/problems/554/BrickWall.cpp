#include <vector>
#include <iostream>
//#include <iomanip>
#include <unordered_map>

using namespace  std;

class Solution {
public:
    int leastBricks(vector<vector<int>>& wall) {
        unordered_map<int, int> cnts;
        for(auto &widths : wall){
            int sum =0;
            for(int i=0; i<(int)widths.size()-1;++i){
                sum += widths[i];
                ++cnts[sum];
            }
        }
        int maxcnt = 0;
        for(auto &cnt : cnts){
            maxcnt = max(maxcnt, cnt.second);
        }
        return wall.size() - maxcnt;
    }
};

int main(void){
    vector<vector<int>> wall;
    Solution s;

    wall = {{1,2,2,1},{3,1,2},{1,3,2},{2,4},{3,1,2},{1,3,1,1}};
    cout << s.leastBricks(wall) << endl;
    wall = {{1},{1},{1}};
    cout << s.leastBricks(wall) << endl;

    wall = {{100000000}};
    cout << s.leastBricks(wall) << endl;


    return 0;
}
