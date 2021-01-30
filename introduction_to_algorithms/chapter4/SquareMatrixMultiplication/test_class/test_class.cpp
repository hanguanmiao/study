#include "test_class.h"

#include <tuple>
#include <random>
#include <memory>

std::vector<std::vector<int>> solution::SquareMatrixMultiplication(
     std::vector<std::vector<int>> left, std::vector<std::vector<int>> right){
    if(left.empty() || left.size() != right.size()){
        return std::vector<std::vector<int>>(0);
    }
    for(const auto &v : left){
        if(v.size() != left.size()) return std::vector<std::vector<int>>(0);
    }
    for(const auto &v : right){
        if(v.size() != right.size()) return std::vector<std::vector<int>>(0);
    }

    std::vector<std::vector<int>> l_res(left.size(),
                                        std::vector<int>(left[0].size(),0));
    for(std::size_t i=0; i<l_res.size(); ++i){
        for(std::size_t j=0; j<l_res.size(); ++j){
            for(std::size_t k=0; k<l_res.size(); ++k){
                l_res[i][j] += left[i][k] * right[k][j];
            }
        }
    }
    return l_res;
}


std::vector<int> generate::GenerateNums(std::size_t size, int rangelow,
                                         int rangehigh){
    std::random_device l_rd;
    std::mt19937 l_gen(l_rd());
    std::uniform_int_distribution<> l_dist(rangelow, rangehigh);
    std::vector<int> l_ret(size, 0);

    for(std::size_t i=0; i<size; ++i){
        l_ret[i] = l_dist(l_gen);
    }
    return l_ret;
}


std::vector<std::vector<int>> generate::GenerateMatrix(std::size_t size, int rangelow,
                                             int rangehigh){
    std::random_device lrd;
    std::mt19937 lgen(lrd());
    std::uniform_int_distribution<> ldist(rangelow, rangehigh);
    std::vector<std::vector<int>> lMatrix(size, std::vector<int>(size,0));

    for(auto &a : lMatrix){
        for(auto &b : a){
            b = ldist(lgen);
        }
    }
    return lMatrix;
}
