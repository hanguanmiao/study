#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    bool stoneGame(vector<int>& piles) {

    }
};

int main(void){
    vector<int> piles;
    Solution s;

    piles = {5,3};
    cout << s.stoneGame(piles) << endl; // true;

    piles = {5,3,4,5};
    cout << s.stoneGame(piles) << endl; // true;

    piles = {5,8,2,4};
    cout << s.stoneGame(piles) << endl; // true;

//    piles = {5,3,4,5};
//    cout << s.stoneGame(piles) << endl; // true;


    return 0;
}
