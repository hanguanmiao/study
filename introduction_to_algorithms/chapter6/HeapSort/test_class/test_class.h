#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <vector>

class solution{
public:
    void Heapsort(std::vector<int> &v);

private:
    void maxheapify(std::vector<int> &v, std::size_t ci, std::size_t mi);
    void buildmaxheap(std::vector<int> &v);
};


#endif // TEST_CLASS_H
