#include <iostream>

using namespace std;

class Solution {
public:
    int hammingDistance(int x, int y) {
        int count = 0;
        while(x || y){
            if((x&1) ^ (y&1)) ++count;
            x >>= 1;
            y >>= 1;
        }
        return count;
    }
};

int main(void){


    return 0;
}
