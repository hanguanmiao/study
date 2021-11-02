#include <iostream>
#include <string>

//g++ -std=c++11 -Wall -Wextra -g -O0 main.cpp
using namespace std;


int main() {
    string str;
    int size;
    int count=0;
    int res;

    cin >> str;

    size = static_cast<int>(str.size());
    for(int i=0; i<size; ++i){
        if(str[i] == 'o') ++count;
    }

    if(count%2 == 0){
        res = size;
    }else{
        res = size - 1;
    }

    cout << res << endl;

    return 0;
}

//
// alolobo
// looxdolx
// bcbcbc
// oooooooo
// ooooooooo
