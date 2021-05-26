#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <climits>

using namespace std;


class Solution {
public:
    int strangePrinter(string s) {
        int n = s.length();
        vector<vector<int>> fill(n, vector<int>(n));

        for(int i=n-1;i>=0;--i){
            fill[i][i] = 1;
            for (int j = i+1; j < n; ++j) {
                if(s[i] == s[j]){
                    fill[i][j] = fill[i][j-1];
                }else{
                    int minpt = INT_MAX;
                    for(int k=i; k<j;++k){
                        minpt = min(minpt, fill[i][k]+fill[k+1][j]);
                    }
                    fill[i][j] = minpt;
                }
            }
        }
        return fill[0][n-1];
    }
};


int main(){
    Solution s;
    string input;

    input = "aaabbb";
    cout << s.strangePrinter(input) << endl;

    input = "aba";
    cout << s.strangePrinter(input) << endl;

    input = "bbaaaabc";
    cout << s.strangePrinter(input) << endl;

    input = "bbabc";
    cout << s.strangePrinter(input) << endl;

    input = "tbgtgb";
    cout << s.strangePrinter(input) << endl;

    return(0);
}
