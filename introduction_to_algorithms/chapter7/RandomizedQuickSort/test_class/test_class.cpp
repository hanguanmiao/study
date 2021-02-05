#include <cassert>

#include <random>
#include <iostream>

#include "test_class.h"

void solution::RandomizedQuickSort(std::vector<int> &vec){
    if(1 < vec.size()){
        randomizedQuickSort(vec, 0, vec.size() - 1);
    }
}

/* ---------- private fucntion --------- */
void solution::randomizedQuickSort(std::vector<int> &vec, std::size_t minidx,
                         std::size_t maxidx){
    if(minidx < maxidx){
        std::size_t res = randomizedPartition(vec, minidx, maxidx);
        if(res){
            randomizedQuickSort(vec, minidx, res-1);
        }
        randomizedQuickSort(vec, res+1, maxidx);
    }
}

std::size_t solution::randomizedPartition(std::vector<int> &vec,
        std::size_t minidx, std::size_t maxidx){
//    std::random_device rd;
//    std::default_random_engine re(rd());
//    std::uniform_int_distribution<int> dist(minidx,maxidx);
//    std::size_t idx = dist(re);
//    std::swap(vec[idx],vec[maxidx]);
    return partition(vec, minidx, maxidx);
}

std::size_t solution::partition(std::vector<int> &vec, std::size_t minidx,
                         std::size_t maxidx){
    assert(minidx<maxidx);
    std::size_t i = minidx - 1, j = minidx;
    for(;j<maxidx;++j){
        if(vec[j] < vec[maxidx]){
            std::swap(vec[++i], vec[j]);
        }
    }
    std::swap(vec[++i], vec[j]);
    return i;
}

/* ------------------ */

void Test::TestRQS(void){
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
        s.RandomizedQuickSort(vec);
        std::cout << "after: ";
        for(auto &v:vec){
            std::cout << v << ' ';
        }
        std::cout << std::endl;
    }
}
