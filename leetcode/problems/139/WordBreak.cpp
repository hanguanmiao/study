#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int size = s.size() + 1;
        int wordsize = wordDict.size();
        vector<bool> targets(size, false);
        targets[0] = true;

        for(int i=1; i<size; ++i){
            for(int j=0; j<wordsize; ++j){
                string &str = wordDict[j];
                int strsize = str.size();
                if(i>=strsize && s.substr(i-strsize, strsize) == str){
                    targets[i] = targets[i] | targets[i-strsize];
                }
            }
        }

        return targets[size-1];
    }
};


int main(void){
    Solution solu;
    string s;
    vector<string> wordDict;

    s = "leetcode";
    wordDict = {"leet","code"};
    cout << solu.wordBreak(s, wordDict) << endl;

    s = "applepenapple";
    wordDict = {"apple","pen"};
    cout << solu.wordBreak(s, wordDict) << endl;

    s = "catsandog";
    wordDict = {"cats","dog","sand","and","cat"};
    cout << solu.wordBreak(s, wordDict) << endl;


    return 0;
}
