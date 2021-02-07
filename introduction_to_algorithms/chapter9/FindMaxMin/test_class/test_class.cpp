#include "test_class.h"

#include <climits>
#include <cassert>

#include <random>
#include <set>
#include <iostream>



std::tuple<bool, int, int> solution::FindMaxMin(
        const std::vector<int> &vec){
    if(vec.empty()) return std::make_tuple(false,0,0);
    if(vec.size() == 1) return std::make_tuple(true, vec[0], vec[0]);

    int min,max;
    std::size_t idx, jdx;
    if(vec.size()%2){
        min = max = vec[0];
        idx = 1;
        jdx = 2;
    }else{
        if(vec[0] < vec[1]){
            min = vec[0];
            max = vec[1];
        }else{
            min = vec[1];
            max = vec[0];
        }
        idx = 2;
        jdx = 3;
    }
    for(;idx < vec.size(); idx += 2, jdx+=2){
        if(vec[idx] < vec[jdx]){
            if(vec[idx] < min){
                min = vec[idx];
            }
            if(max < vec[jdx]){
                max = vec[jdx];
            }
        }else{
            if(vec[jdx] < min){
                min = vec[jdx];
            }
            if(max < vec[idx]){
                max = vec[idx];
            }
        }
    }
    return std::make_tuple(true,min,max);
}

/* ---------- private fucntion --------- */


/* ------------------ */
void Test::TestFMM(void){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::vector<int> vec;
    solution s;
    int rnum;

    for(std::size_t i=0; i < 100;++i){
        std::uniform_int_distribution<int> dist(-i,i);

        vec.clear();
        for(std::size_t j=0; j<i; ++j){
            rnum = dist(re);
            vec.push_back(rnum);
        }
        std::cout << "before: ";
        for(auto &v:vec){
            std::cout << v << ' ';
        }
        std::cout << std::endl;
        auto res = s.FindMaxMin(vec);
        std::cout << "after: ";
        std::cout << std::get<0>(res) << ' ' << std::get<1>(res)
                  << ' ' << std::get<2>(res);
        std::cout << std::endl << std::endl;
    }
}
