#include <iostream>

using namespace std;

class Solution {
public:
    bool isPowerOfTwo(int n) {
        unsigned int m = n;
        int count = 0;
        while(m){
            if(m & 1) ++count;
        }
        if(m <= 1U) return true;
        return false;
    }
};


