#include <iostream>
#include "test_class/test_class.h"

int main(void){
    solution s;
    std::vector<int> v;

    for(int i=-5; i<5; ++i){
        v.push_back(i);
    }

    s.RandomInPlace(v);

    for(auto &a:v){
        std::cout << a << ' ';
    }
    std::cout << std::endl;

    return 0;
}
