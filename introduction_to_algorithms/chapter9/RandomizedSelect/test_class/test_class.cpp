#include <cassert>

#include <random>
#include <iostream>
#include <climits>

#include "test_class.h"

std::vector<int> solution::CountingSort(std::vector<int> &vec, int minval, int maxval){
    if(maxval < minval){
        std::cout << "minval: " << minval << "maxval: " << maxval << std::endl;
        return vec;
    }
    if(vec.empty() || vec.size() == 1 || minval == maxval){
        return vec;
    }

    std::vector<int> count(maxval - minval + 1, 0);
    for(auto &v : vec){
        ++count[v-minval];
    }
    for(std::size_t i=1,j=0; i<count.size(); ++i,++j){
        count[i] += count[j];
    }

    std::vector<int> ret(vec.size());
    for(auto &v : vec){
        ret[count[v-minval] - 1] = v;
        --count[v-minval];
    }
    return ret;
}

/* ---------- private fucntion --------- */


/* ------------------ */
void Test::TestCS(void){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::vector<int> vec;
    solution s;
    int rnum, minval, maxval;

    for(std::size_t i=0; i < 100;++i){
        std::uniform_int_distribution<int> dist(-i,i);

        vec.clear();
        minval = INT32_MAX;
        maxval = INT32_MIN;
        for(std::size_t j=0; j<i; ++j){
            rnum = dist(re);
            vec.push_back(rnum);
            if(rnum < minval) minval = rnum;
            if(maxval < rnum) maxval = rnum;
        }
        std::cout << "before: ";
        for(auto &v:vec){
            std::cout << v << ' ';
        }
        std::cout << std::endl;
        auto res = s.CountingSort(vec, minval, maxval);
        std::cout << "after: ";
        for(auto &v:res){
            std::cout << v << ' ';
        }
        std::cout << std::endl << std::endl;
    }
}

