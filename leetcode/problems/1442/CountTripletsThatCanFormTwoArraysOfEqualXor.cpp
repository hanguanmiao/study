#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int countTriplets(vector<int> &arr) {
        int n = arr.size();
        vector<int> s(n + 1);
        for (int i = 0; i < n; ++i) {
            s[i + 1] = s[i] ^ arr[i];
        }
        unordered_map<int, int> cnt, total;
        int ans = 0;
        for (int k = 0; k < n; ++k) {
            if (cnt.count(s[k + 1])) {
                ans += cnt[s[k + 1]] * k - total[s[k + 1]];
            }
            ++cnt[s[k]];
            total[s[k]] += k;
        }
        return ans;
    }
};



int main(void){
    Solution s;
    std::vector<int> input;

    input = std::vector<int>({2,3,1,6,7});
    std::cout << s.countTriplets(input) << std::endl;

    return 0;
}
