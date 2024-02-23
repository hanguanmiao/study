#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int leftidx = 0;
        int rightidx = 0;
        int curlen = 0;
        int maxlen = 0;
        unordered_set<int> chset;

        for(;rightidx < static_cast<int>(s.length()); ++rightidx){
            if(chset.count(s[rightidx])){
                maxlen = curlen > maxlen ? curlen : maxlen;
                while(s[leftidx] != s[rightidx]){
                    chset.erase(s[leftidx]);
                    ++leftidx;
                    --curlen;
                }
                ++leftidx;
            }else{
                chset.insert(s[rightidx]);
                ++curlen;
            }
        }

        maxlen = curlen > maxlen ? curlen : maxlen;

        return maxlen;
    }
};



int main(void){
    Solution s;
    string str1 = "abcabcbb";
    string str2 = "bbbbb";
    string str3 = "pwwkew";
    string str4 = "";
    string str5 = "a";
    string str6 = "ab";
    string str7 = "abcdefc";
    string str8 = "abcabcd";
    string str9 = "abba";

    cout << s.lengthOfLongestSubstring(str1) << endl;//3
    cout << s.lengthOfLongestSubstring(str2) << endl;//1
    cout << s.lengthOfLongestSubstring(str3) << endl;//3
    cout << s.lengthOfLongestSubstring(str4) << endl;//0
    cout << s.lengthOfLongestSubstring(str5) << endl;//1
    cout << s.lengthOfLongestSubstring(str6) << endl;//2
    cout << s.lengthOfLongestSubstring(str7) << endl;//6
    cout << s.lengthOfLongestSubstring(str8) << endl;//4
    cout << s.lengthOfLongestSubstring(str9) << endl;//2

    return 0;
}
