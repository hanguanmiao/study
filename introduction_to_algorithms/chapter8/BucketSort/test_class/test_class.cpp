#include "test_class.h"

#include <climits>
#include <cassert>

#include <random>
#include <set>
#include <iostream>



std::vector<double> solution::BucketSort(const std::vector<double> &vec){
    if(!vec.size() >> 1) return vec;

    std::vector<std::multiset<double>> tmpvec(vec.size());
    for(auto &v : vec){
        tmpvec[vec.size() * v].insert(v);
    }
    std::vector<double> ret(vec.size());
    std::size_t i=0;
    for(auto &tset : tmpvec){
        for(auto &v : tset){
            ret[i++] = v;
        }
    }
    return  ret;
}

/* ---------- private fucntion --------- */


/* ------------------ */
void Test::TestBS(void){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::vector<double> vec;
    solution s;
    double rnum;

    for(std::size_t i=0; i < 100;++i){
        std::uniform_real_distribution<double> dist(0,1);

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
        auto res = s.BucketSort(vec);
        std::cout << "after: ";
        for(auto &v:res){
            std::cout << v << ' ';
        }
        std::cout << std::endl << std::endl;
    }
}
