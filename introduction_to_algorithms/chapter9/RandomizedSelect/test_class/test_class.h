#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <vector>

class solution{
public:
    int RandomizedSelect(std::vector<int> &vec, std::size_t num);
private:
    int randomizedSelect(std::vector<int> &vec, std::size_t num,
                                   std::size_t minidx, std::size_t maxidx);
    std::size_t randomizedPartition(std::vector<int> &vec, std::size_t minidx,
                                    std::size_t maxidx);
    std::size_t partition(std::vector<int> &vec, std::size_t minidx,
                          std::size_t maxidx);
};

class Test{
public:
    void TestFunc(void);
};

#endif // TEST_CLASS_H
