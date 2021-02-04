#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <string>
#include <vector>

class PriorityQueue{
public:
    void Insert(int val);
    bool Maximum(int &num);
    bool ExtractMax(int &num);
    bool IncreaseKey(std::size_t idx, int val);

    const std::string &GetErr(void) const;
    std::size_t GetQueueSize(void) const;
    void PrintQueue(void) const;

private:
    void maxHeapify(std::vector<int> &vec, std::size_t cidx, std::size_t maxidx);
    void bubbleMaxHeap(std::vector<int> &vec, std::size_t cidx);
    void setErr(const std::string &err);

private:
    std::vector<int> m_queue;
    std::string m_err;
};

class TestPQ{
public:
    void Test(void);

private:
    void test(std::size_t totalnum);
};

#endif // PRIORITY_QUEUE_H
