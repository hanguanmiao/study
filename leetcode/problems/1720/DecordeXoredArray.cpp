#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> decode(vector<int>& encoded, int first) {
        vector<int> res;
        res.push_back(first);
        for(auto val : encoded){
            first ^= val;
            res.push_back(first);
        }
        return res;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    vector<int> input, res;

    input = {1,2,3};
    res = s.decode(input, 1);
    for(auto val:res){
        cout << val << ' ';
    }
    cout << endl;

    input = {6,2,7,3};
    res = s.decode(input, 4);
    for(auto val:res){
        cout << val << ' ';
    }
    cout << endl;


    return 0;
}
