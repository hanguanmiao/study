#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        int openparnum = n;
        int closeparnum = n;
        string parstr;
        vector<string> ans;
        solve(parstr, openparnum, closeparnum, ans);

        return ans;
    }

private:
    void solve(string parstr, int openparnum, int closeparnum, vector<string> &ans){
        if(0 == openparnum && 0 == closeparnum){
            return;
        }else if(0 == openparnum){
            while(closeparnum--){
                parstr.push_back(')');
            }
            ans.push_back(parstr);
            return;
        }else if(openparnum == closeparnum){
            parstr.push_back('(');
            solve(parstr, openparnum-1, closeparnum, ans);
        }else{
            string parstr1 = parstr;
            string parstr2 = parstr;
            parstr1.push_back('(');
            parstr2.push_back(')');
            solve(parstr1, openparnum-1, closeparnum, ans);
            solve(parstr2, openparnum, closeparnum-1, ans);
        }
    }
};

int main(void){
    Solution sol;
    vector<string> ans;

    ans = sol.generateParenthesis(1);
    for(auto str : ans){
        cout << str << '\t';
    }
    cout << endl;

    ans = sol.generateParenthesis(2);
    for(auto str : ans){
        cout << str << '\t';
    }
    cout << endl;

    ans = sol.generateParenthesis(3);
    for(auto str : ans){
        cout << str << '\t';
    }
    cout << endl;

    ans = sol.generateParenthesis(4);
    for(auto str : ans){
        cout << str << '\t';
    }
    cout << endl;

    return 0;
}
