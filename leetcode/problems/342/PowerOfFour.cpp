#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    bool isPowerOfFour(int n) {
        if(!isPowerOfTwo(n)) return false;
        while (n) {
            if(n == 1) return true;
            n >>= 2;
        }
        return false;
    }

private:
    bool isPowerOfTwo(int n){
        return (n>0 && (n & (n-1)) == 0);
    }
};

int main(void){
    Solution s;
    int input;

    input = 16;
    cout << s.isPowerOfFour(input) << endl; // 1

    input = 5;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = 1;
    cout << s.isPowerOfFour(input) << endl; // 1

    input = -128;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = 0;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = 2;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = 3;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = 4;
    cout << s.isPowerOfFour(input) << endl; // 1

    input = 5;
    cout << s.isPowerOfFour(input) << endl; // 0


    input = -1;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = INT_MAX;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = INT_MIN;
    cout << s.isPowerOfFour(input) << endl; // 0

    input = -5;
    cout << s.isPowerOfFour(input) << endl; // 0

    return 0;
}
