#include <iostream>
#include <vector>


using namespace std;


class Solution {
public:
    int maxArea(vector<int>& height) {
        int lidx=0, ridx=static_cast<int>(height.size()) - 1;
        int ans=0;

        while(lidx < ridx){
            int ht = height[lidx] <= height[ridx] ? height[lidx] : height[ridx];
            int area = ht * (ridx - lidx);

            ans = ans < area ? area : ans;

            if(height[lidx] < height[ridx])
                ++lidx;
            else
                --ridx;
        }

        return ans;
    }
};


int main(void){
    Solution sol;

    vector<int> height1{1,8,6,2,5,4,8,3,7};
    cout<<sol.maxArea(height1)<<endl;

    vector<int> height2{1,1};
    cout<<sol.maxArea(height2)<<endl;

    return 0;
}
