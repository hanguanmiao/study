#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        int left = 1, right = arr.size() - 1, ans;
        while(right >= left){
            int mid = (right+left)/2;
            if(arr[mid] > arr[mid+1]){
                ans = mid;
                right = mid - 1;
            }else{
                left = mid+1;
            }
        }
        return ans;
    }
};


int main(void){
    return 0;
}
