#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if(numRows<=1 || numRows>=static_cast<int>(s.length())) return s;

        vector<string> strVec(numRows);
        int dir = -1;
        int vidx = 0;

        for(int i=0; i<static_cast<int>(s.length()); ++i){
            if(vidx==0 || vidx==numRows-1) dir *= -1;

            strVec[vidx] += s[i];
            if(1==dir) ++vidx;
            else --vidx;

        }

        string ans;
        for(auto &tmp : strVec){
            ans += tmp;
        }

        return ans;
    }
};

int main(void){
    Solution sol;

    string s1="PAYPALISHIRING";
    int num1 = 3;
    cout << sol.convert(s1,num1) << endl;

    string s2="PAYPALISHIRING";
    int num2 = 4;
    cout << sol.convert(s2,num2) << endl;

    string s3="PAYPALISHIRING";
    int num3 = 1;
    cout << sol.convert(s3,num3) << endl;

    string s4="PAYPALISHIRING";
    int num4 = 14;
    cout << sol.convert(s4,num4) << endl;

    return 0;
}
