#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>

//g++ -std=c++11 -Wall -Wextra -g -O0 main.cpp
//using namespace std;


class Solution {
public:
    std::vector<int> killPids(std::vector<int> pids, std::vector<int> ppids, int killpid);
};

void test(void);
void test1(void);

int main() {
    test();

    return 0;
}


std::vector<int> Solution::killPids(std::vector<int> pids, std::vector<int> ppids, int killpid){
    int sizepids = static_cast<int>(pids.size());
    int sizeppids = static_cast<int>(ppids.size());
    std::multimap<int,int> keypair;
    std::queue<int> needkills;
    std::vector<int> res;

    if(sizepids != sizeppids) return res;

    for(int i=0; i<sizepids; ++i){
        keypair.insert({ppids[i], pids[i]});
    }

    needkills.push(killpid);

    while (!needkills.empty()) {
        int kpid = needkills.front();
        needkills.pop();

        res.push_back(kpid);

        auto range = keypair.equal_range(kpid);
        for(auto it=range.first; it != range.second; ++it){
            needkills.push(it->second);
        }
    }

    return res;
}


void test(void){
    test1();
}

void test1(void){
    Solution s;
    std::vector<int> pids({1,3,10,5});
    std::vector<int> ppids({3,0,5,3});
    std::vector<int> ret;
    int killpid = 5;

    ret = s.killPids(pids, ppids, killpid);
    for(auto pid : ret){
        std::cout << pid << ',';
    }
    std::cout << std::endl;
}

