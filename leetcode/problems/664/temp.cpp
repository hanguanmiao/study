#include <iostream>
#include <string>
#include <map>

using namespace std;


class Solution{
public:
    int printer(string s){
        std::map<char,int> charCounter;
        char pre = s[0];
        charCounter[pre] = 1;
        for(int i=1; i<static_cast<int>(s.size()); ++i){
            char ch = s[i];
            if(pre==ch){
                continue;
            }
            if(charCounter.count(ch)){
                ++charCounter[ch];
            }else{
                charCounter[ch] = 1;
            }
            pre = ch;
        }

        int sum = 0, maxcount = 0;
        for(std::map<char,int>::const_iterator it=charCounter.begin();
            it!=charCounter.end(); ++it){
            sum += it->second;
            if(maxcount < it->second) maxcount = it->second;
        }
        return sum - maxcount + 1;
    }
};

int main(){
    Solution s;
    string input;

    input = "aaabbb";
    cout << s.printer(input) << endl;

    input = "aba";
    cout << s.printer(input) << endl;

    input = "bbaaaabc";
    cout << s.printer(input) << endl;

    return(0);
}
