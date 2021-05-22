#include <vector>
#include <iostream>


using namespace std;


class Solution {
public:
    int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
        int size1 = static_cast<int>(nums1.size());
        int size2 = static_cast<int>(nums2.size());
        std::vector<std::vector<int>> cntarr(size1+1, std::vector<int>(size2+1, 0));


        for(int i=size1-1; i>=0; --i){
            for(int j=size2-1; j>=0; --j){
                if(nums1[i] ^ nums2[j]) {
                    cntarr[i][j] = std::max(cntarr[i][j+1], cntarr[i+1][j]);
                 }else{
                    cntarr[i][j] = cntarr[i+1][j+1] + 1;
                }
            }
        }
        return cntarr[0][0];
    }
};


int main()
{
    Solution s;
    std::vector<int> nums1, nums2;


    nums1 = std::vector<int>({1,4,2});
    nums2 = std::vector<int>({1,2,4});
    std::cout << s.maxUncrossedLines(nums1,nums2) << std::endl;


    nums1 = std::vector<int>({2,5,1,2,5});
    nums2 = std::vector<int>({10,5,2,1,5,2});
    std::cout << s.maxUncrossedLines(nums1,nums2) << std::endl;


    nums1 = std::vector<int>({1,3,7,1,7,5});
    nums2 = std::vector<int>({1,9,2,5,1});
    std::cout << s.maxUncrossedLines(nums1,nums2) << std::endl;


    return(0);
}
