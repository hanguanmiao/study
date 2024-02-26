#include <iostream>
#include <string>

using namespace std;


class Solution {
public:
    int strStr(string haystack, string needle) {
        int ans = -1;

        for(int i=0; i<=static_cast<int>(haystack.length()-needle.length()); ++i){
            int find = true;
            for(int j=0;j<static_cast<int>(needle.length());++j){
                if(needle[j] != haystack[j+i]) {
                    find = false;
                    break;
                }
            }

            if(find) {
                ans = i;
                break;
            }
        }

        return ans;
    }
};

int main(void){
    Solution sol;

    string haystack1 = "sadbutsad";
    string needle1 = "sad";
    cout << sol.strStr(haystack1, needle1) << endl;

    string haystack2 = "leetcode";
    string needle2 = "leeto";
    cout << sol.strStr(haystack2, needle2) << endl;

    string haystack3 = "hello";
    string needle3 = "ll";
    cout << sol.strStr(haystack3, needle3) << endl;

    string haystack4 = "a";
    string needle4 = "a";
    cout << sol.strStr(haystack4, needle4) << endl;

    return 0;
}
