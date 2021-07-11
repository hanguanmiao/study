#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    int numSquares(int n) {

    }
};

int main(void){
    int input;
    Solution s;

    input = 1;
    cout << s.numSquares(input) << endl; // 1

    input = 2;
    cout << s.numSquares(input) << endl; // 2

    input = 3;
    cout << s.numSquares(input) << endl; // 3

    input = 4;
    cout << s.numSquares(input) << endl; // 1

    input = 5;
    cout << s.numSquares(input) << endl; // 2

    input = 6;
    cout << s.numSquares(input) << endl; // 3

    input = 7;
    cout << s.numSquares(input) << endl; // 4

    input = 8;
    cout << s.numSquares(input) << endl; // 2

    input = 9;
    cout << s.numSquares(input) << endl; // 1

    input = 10;
    cout << s.numSquares(input) << endl; // 2

    input = 11;
    cout << s.numSquares(input) << endl; // 3

    input = 12;
    cout << s.numSquares(input) << endl; // 3

    input = 10000;
    cout << s.numSquares(input) << endl; // 1

    input = 9999;
    cout << s.numSquares(input) << endl; // 4

    return 0;
}
