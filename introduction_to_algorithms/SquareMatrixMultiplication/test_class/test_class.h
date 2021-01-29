#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <atomic>
#include <vector>

class solution{
public:
   std::vector<std::vector<int>> SquareMatrixMultiplication(
        std::vector<std::vector<int>> left, std::vector<std::vector<int>> right);
private:

};

class generate{
public:
    std::vector<int> GenerateNums(std::size_t size, int rangelow, int rangehigh);
    std::vector<std::vector<int>> GenerateMatrix(std::size_t size, int rangelow,
                                                 int rangehigh);
};

#endif // TEST_CLASS_H
