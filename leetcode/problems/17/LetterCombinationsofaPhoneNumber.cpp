#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::vector<std::string> letterCombinations(std::string digits) {
        int digitsize = static_cast<int>(digits.size());
        std::vector<std::string> res;
        std::string cursave;

        cursave.resize(digitsize);

        internalfun(digits, 0, cursave, res);

        return res;
    }

private:
    void internalfun(std::string &digits, int curidx, std::string &cursave, std::vector<std::string> &res){
        int digitsize = static_cast<int>(digits.size());

        if(digitsize <= curidx) return;

        char ch = digits[curidx];
        int idx = ch - 50;
        std::string letters = m_digitMap[idx];

        if(curidx + 1 != digitsize){
            for(int i=0; i < static_cast<int>(letters.size()); ++i){
                cursave[curidx] = letters[i];
                internalfun(digits, curidx +1, cursave, res);
            }
        }else{
            for(int i=0; i < static_cast<int>(letters.size()); ++i){
                cursave[curidx] = letters[i];
                res.push_back(cursave);
            }
        }
    }

private:
//    static const std::vector<std::string> m_digitMap;

        std::vector<std::string> m_digitMap = {
        ("abc"),
        ("def"),
        ("ghi"),
        ("jkl"),
        ("mno"),
        ("pqrs"),
        ("tuv"),
        ("wxyz")
    };
};

//const std::vector<std::string> m_digitMap = {
//    ("abc"),
//    ("def"),
//    ("ghi"),
//    ("jkl"),
//    ("mno"),
//    ("pqrs"),
//    ("tuv"),
//    ("wxyz")
//};


int main(void){

    return 0;
}
