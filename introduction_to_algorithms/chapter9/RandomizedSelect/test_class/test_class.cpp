#include <cassert>

#include <random>
#include <iostream>
#include <climits>

#include "test_class.h"

int solution::RandomizedSelect(std::vector<int> &vec, std::size_t num){
    if(vec.empty()){
        std::cerr << "empty" << std::endl;
        return 0;
    }
    if(vec.size() == 1){
        return vec[0];
    }

    return randomizedSelect(vec, num, 0, vec.size()-1);
}

int solution::randomizedSelect(std::vector<int> &vec, std::size_t num,
                               std::size_t minidx, std::size_t maxidx){
    assert(minidx <= maxidx);
    assert(num);
    if(minidx == maxidx) {
        return vec[minidx];
    }

    std::size_t pid = randomizedPartition(vec, minidx, maxidx);
    std::size_t needidx = num - 1 + minidx;
    if(pid == needidx) return vec[needidx];
    if(pid < needidx) return randomizedSelect(vec, num - (pid - minidx + 1),
                                              pid+1, maxidx);
    return randomizedSelect(vec, num, minidx, pid - 1);
}

std::size_t solution::randomizedPartition(std::vector<int> &vec, std::size_t minidx,
                                std::size_t maxidx){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<std::size_t> dist(minidx, maxidx);

    std::size_t rnum = dist(re);
    std::swap(vec[maxidx], vec[rnum]);
    return partition(vec, minidx, maxidx);
}

std::size_t solution::partition(std::vector<int> &vec, std::size_t minidx,
                      std::size_t maxidx){
    assert(minidx < maxidx);
    std::size_t i = minidx - 1, j = minidx;
    for(;j<maxidx; ++j){
        if(vec[j] < vec[maxidx]){
            std::swap(vec[++i], vec[j]);
        }
    }
    std::swap(vec[++i], vec[maxidx]);
    return i;
}


/* ---------- private fucntion --------- */


/* ------------------ */
void Test::TestFunc(void){
    std::random_device rd;
    std::default_random_engine re(rd());
    std::vector<int> vec;
    solution s;
    int rnum;

    for(std::size_t i=0; i < 30;++i){
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
        std::uniform_int_distribution<std::size_t> distsec(1,vec.size());
        std::size_t secnum = distsec(re);
        std::cout << "select: " << secnum << std::endl;

        auto res = s.RandomizedSelect(vec, secnum);
        std::cout << "after: " << res;
        std::cout << std::endl << std::endl;
    }
}

