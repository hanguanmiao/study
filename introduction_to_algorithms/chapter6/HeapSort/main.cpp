#include <iostream>
#include <random>
#include "test_class/test_class.h"

int main(void){
    solution s;
    std::random_device r;
    std::default_random_engine el(r());

    for(int i = 0; i <= 10; ++i){
        std::vector<int> v;
        std::uniform_int_distribution<int> uniform_dist(-i,i);
        int val;
        for(int j=0; j < i; ++j){
            val = uniform_dist(el);
            v.push_back(val);
        }
        std::cout << "before: ";
        for(auto &a : v){
            std::cout << a << ' ';
        }
        std::cout << std::endl;
        s.Heapsort(v);
        std::cout << "after: ";
        for(auto &a : v){
            std::cout << a << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
