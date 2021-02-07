#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <vector>
#include <tuple>

class solution{
public:
    std::tuple<bool,int,int> FindMaxMin(const std::vector<int> &vec);
private:

};

class Test{
public:
    void TestFMM(void);
};

#endif // TEST_CLASS_H
