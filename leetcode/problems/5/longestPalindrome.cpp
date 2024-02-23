#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.length() <= 1) return s;

        string maxpalistr;

        auto max_palin = [&](int leftidx, int rightidx, string &s){
            while(leftidx>=0 && rightidx<static_cast<int>(s.length()) && s[leftidx] == s[rightidx]){
                --leftidx;
                ++rightidx;
            }
            return s.substr(leftidx+1, rightidx-leftidx-1);
        };

        for(int i=0; i<static_cast<int>(s.length()); ++i){
            auto oddstr = max_palin(i,i,s);
            if(maxpalistr.length() < oddstr.length()){
                maxpalistr = oddstr;
            }

            if(i<static_cast<int>(s.length())-1){
                auto evenstr = max_palin(i,i+1,s);
                if(maxpalistr.length() < evenstr.length()){
                    maxpalistr = evenstr;
                }
            }
        }

        return maxpalistr;
    }
};


int main(void){
    Solution slo;


    string s1 = "babad";
    cout << slo.longestPalindrome(s1) << endl;

    string s2 = "cbbd";
    cout << slo.longestPalindrome(s2) << endl;

    string s3 = "a";
    cout << slo.longestPalindrome(s3) << endl;

    string s4 = "ab";
    cout << slo.longestPalindrome(s4) << endl;

    string s5 = "aa";
    cout << slo.longestPalindrome(s5) << endl;

    string s6 = "abc";
    cout << slo.longestPalindrome(s6) << endl;

    string s7 = "aba";
    cout << slo.longestPalindrome(s7) << endl;

    string s8 = "aab";
    cout << slo.longestPalindrome(s8) << endl;

    string s9 = "abb";
    cout << slo.longestPalindrome(s9) << endl;

    string s10 = "bbaa";
    cout << slo.longestPalindrome(s10) << endl;


    return 0;
}
