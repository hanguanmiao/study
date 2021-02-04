#include <sstream>
#include <iostream>
#include "priority_queue.h"

void PriorityQueue::Insert(int val){
    m_queue.push_back(val);

    bubbleMaxHeap(m_queue, m_queue.size() - 1);
}

bool PriorityQueue::Maximum(int &num){
    if(m_queue.empty()){
        setErr("priority queue is empty");
        return false;
    }
    num = m_queue[0];
    return true;
}

bool PriorityQueue::ExtractMax(int &num){
    if(m_queue.empty()){
        setErr("priority queue is empty");
        return false;
    }

    num = m_queue[0];
    if(1 < m_queue.size()){
        std::swap(m_queue[0], m_queue[m_queue.size()-1]);
        maxHeapify(m_queue,0,m_queue.size()-2);
    }

    m_queue.pop_back();
    return true;
}


bool PriorityQueue::IncreaseKey(std::size_t idx, int val){
    if(m_queue.empty() || m_queue.size() - 1 < idx){
        std::stringstream ios;
        ios << "idx:" << idx << ", size:" << m_queue.size();
        setErr(ios.str());
        return false;
    }
    if(val <= m_queue[idx]){
        std::stringstream ios;
        ios << "val:" << val << ", queval:" << m_queue[idx];
        setErr(ios.str());
        return false;
    }
    m_queue[idx] = val;
    bubbleMaxHeap(m_queue, idx);
    return true;
}

const std::string &PriorityQueue::GetErr(void) const{
    return m_err;
}

std::size_t PriorityQueue::GetQueueSize(void) const{
    return m_queue.size();
}

void PriorityQueue::PrintQueue(void) const{
    for(auto &v : m_queue){
        std::cout << v <<' ';
    }
    std::cout << std::endl;
}

/* ------------------- private function -------------- */
void PriorityQueue::maxHeapify(std::vector<int> &vec, std::size_t cidx,
                               std::size_t maxidx){
    std::size_t grtValIdx = cidx;
    std::size_t lchdi, rchdi;

    while (grtValIdx < maxidx) {
        lchdi = cidx * 2 + 1;
        rchdi = cidx * 2 + 2;
        if(lchdi <= maxidx && vec[grtValIdx] < vec[lchdi]){
            grtValIdx = lchdi;
        }
        if(rchdi <= maxidx && vec[grtValIdx] < vec[rchdi]){
            grtValIdx = rchdi;
        }

        if(grtValIdx ^ cidx){
            std::swap(vec[grtValIdx], vec[cidx]);
            cidx = grtValIdx;
        }else{
            // vec[cidx] is greater than vec[lchdi] and vec[rchdi]
            break;
        }
    }
}

void PriorityQueue::bubbleMaxHeap(std::vector<int> &vec, std::size_t cidx){
    std::size_t paridx = (cidx - 1)/2;
    while (cidx && vec[paridx] < vec[cidx]) {
        std::swap(vec[cidx], vec[paridx]);
        cidx = paridx;
        paridx = (cidx - 1)/2;
    }
}

void PriorityQueue::setErr(const std::string &err){
    m_err = err;
}

/* ----------------------------- */
#include <stdexcept>
#include <random>
void TestPQ::Test(void){
    PriorityQueue pq;

    /* test empty */
    int num;
    if(pq.IncreaseKey(0, 4)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }
    if(pq.Maximum(num)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }
    if(pq.ExtractMax(num)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }

    /* test one element */
    pq.Insert(5);
    if(pq.IncreaseKey(1, 6)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }
    if(pq.IncreaseKey(0, 5)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }
    if(pq.IncreaseKey(0, 4)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }
    if(pq.Maximum(num)){
        std::cout << num << std::endl;
    }else{
        throw std::runtime_error("error");
    }
    if(pq.ExtractMax(num)){
        std::cout << num << std::endl;
    }else{
        throw std::runtime_error("error");
    }
    if(pq.Maximum(num)){
        throw std::runtime_error("error");
    }else{
        std::cout << pq.GetErr() << std::endl;
    }

    test(20);
}

void TestPQ::test(std::size_t totalnum){
    PriorityQueue pq;
    std::random_device r;
    std::default_random_engine el(r());
    std::uniform_int_distribution<int> uniform_dist(-totalnum, totalnum);
    std::uniform_int_distribution<int> uniform_d(0,3);
    int action, num;
    std::size_t idx;

    while (pq.GetQueueSize() < totalnum) {
        action = uniform_d(el);
        if(!action /*|| !~action*/){
            num = uniform_dist(el);
            pq.Insert(num);
            std::cout << "insert: " << num << std::endl;
        }else if(1 == action){
            std::cout << "max: ";
            if(pq.Maximum(num)){
                std::cout << num << std::endl;
            }else{
                std::cout << pq.GetErr() << std::endl;
            }
        }else if(2 == action){
            std::cout << "extract: ";
            if(pq.ExtractMax(num)){
                std::cout << num << std::endl;
            }else{
                std::cout << pq.GetErr() << std::endl;
            }
        }else{
            std::uniform_int_distribution<std::size_t>
                    uniform_x(0, pq.GetQueueSize()-1);
            idx = uniform_x(el);
            num = uniform_dist(el);
            std::cout << "increase: ";
            if(pq.IncreaseKey(idx, num)){
                std::cout << "idx: " << idx << "   num: " << num << std::endl;
            }else{
                std::cout << pq.GetErr() << std::endl;
            }
        }
        pq.PrintQueue();
    }
}
