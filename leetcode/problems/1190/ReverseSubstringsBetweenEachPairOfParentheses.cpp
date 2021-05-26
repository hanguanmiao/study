#include <iostream>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> pair(n);
        stack<int> stk;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                int j = stk.top();
                stk.pop();
                pair[i] = j, pair[j] = i;
            }
        }

        string ret;
        int index = 0, step = 1;
        while (index < n) {
            if (s[index] == '(' || s[index] == ')') {
                index = pair[index];
                step = -step;
            } else {
                ret.push_back(s[index]);
            }
            index += step;
        }
        return ret;
    }
};




int main(void){
    Solution s;
    string input;

//    input = "(abcd)";
//    cout << s.reverseParentheses(input) << endl;

//    input = "(u(love)i)";
//    cout << s.reverseParentheses(input) << endl;

    input = "(ed(et(oc))el)";
    cout << s.reverseParentheses(input) << endl;

    input = "a(bcdefghijkl(mno)p)q";
    cout << s.reverseParentheses(input) << endl;

    return 0;
}
