#include <random>

#include "test_class.h"

void solution::RandomInPlace(std::vector<int> &v){
    if(v.empty() || v.size() == 1) return;

    std::random_device r;
    std::default_random_engine el(r());
    int rnum;

    for(std::size_t i=0, j=1; j<v.size(); ++i, ++j){
        std::uniform_int_distribution<int> uniform_dist(j, v.size()-1);
        rnum = uniform_dist(el);
        std::swap(v[i],v[rnum]);
    }
}
