#include <vector>
#include <unordered_map>
#include <list>
#include <iostream>

class Solution {
public:

    void set(int key, int val, int k){
        std::unordered_map<int, std::list<std::pair<int,int>>::iterator>::iterator it = m_mapits.find(key);

        if(it != m_mapits.end()){
            m_vals.erase(it->second);
            m_mapits.erase(it);
        }else{
            while(static_cast<int>(m_mapits.size()) >= k){
                m_mapits.erase(m_mapits.find(m_vals.back().first));
                m_vals.pop_back();
            }
        }

        m_vals.push_front(std::make_pair(key, val));
        m_mapits.insert({key, m_vals.begin()});
    }

    int get(int key, int k){
        std::unordered_map<int, std::list<std::pair<int,int>>::iterator>::iterator it = m_mapits.find(key);

        if(it != m_mapits.end()){
            int res = it->second->second;
            set(key, res, k);

            return res;
        }

        return -1;
    }

    /**
     * lru design
     * @param operators int整型vector<vector<>> the ops
     * @param k int整型 the k
     * @return int整型vector
     */
    std::vector<int> LRU(std::vector<std::vector<int> >& operators, int k) {
        std::vector<int> res;
        int size = static_cast<int>(operators.size());

        for(int i=0; i<size; ++i){
            std::vector<int> &oper = operators[i];

            if(oper[0] == 1){
                set(oper[1], oper[2], k);
            }else{
                res.push_back(get(oper[1], k));
            }
        }

        return res;
    }

private:
    std::list<std::pair<int,int>> m_vals;
    std::unordered_map<int, std::list<std::pair<int,int>>::iterator> m_mapits;
};


void test(void);
void test1(void);

int main(void){
    test();
    return 0;
}

void test(void){
    test1();
}

void test1(void){
    Solution s;
    std::vector<std::vector<int> > operators = {{1,1,1},{1,2,2},{1,3,2},{2,1},{1,4,4},{2,2}};
    int k = 3;
    std::vector<int> ret = s.LRU(operators, k);

    for(auto val : ret){
        std::cout << val << ' ';
    }
    std::cout << std::endl;
}

//void test1(void){
//    Solution s;
//    std::vector<std::vector<int> > operators = {{1,1,1},{1,2,2},{2,1},{1,3,3},{2,2},{1,4,4},{2,1},{2,3},{2,4}};
//    int k = 3
//}
