#include <random>

#include "test_class.h"

void solution::Heapsort(std::vector<int> &v){
    if(v.empty() || v.size() == 1) return;
    buildmaxheap(v);

    std::size_t maxi=v.size() -1;
    for(;maxi;){
        std::swap(v[maxi], v[0]);
        maxheapify(v,0, --maxi);
    }
}


/* ---------- private fucntion --------- */

void solution::maxheapify(std::vector<int> &v, std::size_t ci, std::size_t mi){
    std::size_t lci, rci, vi;

    while (ci < mi) {
        lci = ci*2+1;
        rci = ci*2+2;

        vi = ci;
        if(lci <= mi && v[vi] < v[lci]){
            vi = lci;
        }
        if(rci <= mi && v[vi] < v[rci]){
            vi = rci;
        }
        if(vi != ci){
            std::swap(v[vi], v[ci]);
            ci = vi;
        }else{
            break;
        }
    }
}

void solution::buildmaxheap(std::vector<int> &v){
    std::size_t maxi = v.size() - 1, maxloopi = (v.size()-2)/2;

    for(;;--maxloopi){
        maxheapify(v,maxloopi,maxi);
        if(!maxloopi) break;
    }
}
