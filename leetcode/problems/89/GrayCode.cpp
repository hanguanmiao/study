#include <vector>



//class Solution {
//public:
//    std::vector<int> grayCode(int n) {
//        std::vector<int> res;

//        res.push_back(0);

//        for(int i=0; i<n; ++i){
//            int size = static_cast<int>(res.size());

//            for(int j=size-1; j>=0; --j){
//                res.push_back(res[j] | (1 << i));
//            }
//        }

//        return res;
//    }
//};

class Solution {
public:
    std::vector<int> grayCode(int n) {
        std::vector<int> res;

        for(int i=0; i<(1<<n);++i){
            res.push_back(i^(i>>1));
        }

        return res;
    }
};



void test(void);

void test1(void);


int main(void){
    test();

    return 0;
}


void test(void){
    test1();
}

void test1(void){
    Solution s;
    int n = 2;

    auto res = s.grayCode(n);
}
