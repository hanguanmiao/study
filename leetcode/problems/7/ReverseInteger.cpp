#include <iostream>
#include <climits>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        bool minus = false;
        int ret = 0;

        if(x == INT32_MIN) return 0;

        if(x < 0) {
            x = -x;
            minus = true;
        }
        while(x){
            int y = x%10;
            x /= 10;

            if(ret > INT32_MAX/10 || (ret == INT32_MAX/10 && y >= 7)) return 0;
            ret *= 10;
            ret += y;
        }

        if(minus) return -ret;
        return ret;
    }
};

int main(void){
    Solution s;
    int input;

//    input = 123;
//    cout << s.reverse(input) << endl;

//    input = -123;
//    cout << s.reverse(input) << endl;

//    input = 120;
//    cout << s.reverse(input) << endl;

//    input = 0;
//    cout << s.reverse(input) << endl;

//    input = INT32_MAX;
//    cout << s.reverse(input) << endl;

    input = INT32_MIN;
    cout << s.reverse(input) << endl;

    return 0;

}
