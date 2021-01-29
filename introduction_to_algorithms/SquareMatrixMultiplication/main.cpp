#include <iostream>
#include <chrono>
#include <iomanip>

#include "test_class/test_class.h"


int main(void){
    class solution ls;
    class generate lg;

    for(std::size_t i=0; i < 10; ++i){
        std::vector<std::vector<int>> lleft = lg.GenerateMatrix(i, -i, i);
        std::vector<std::vector<int>> lright = lg.GenerateMatrix(i,-i,i);

        std::cout << "Matrix left: " << std::endl;
        for(const auto &v:lleft){
            for(const auto a:v){
                std::cout << std::left << std::setw(6) << a <<' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Matrix right: " << std::endl;
        for(const auto &v:lright){
            for(const auto a:v){
                std::cout << std::left << std::setw(6) << a <<' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        auto lMatrix = ls.SquareMatrixMultiplication(lleft, lright);
        std::cout << "Matrix result: " << std::endl;
        for(const auto &v:lMatrix){
            for(const auto a:v){
                std::cout << std::left << std::setw(6) << a <<' ';
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}




