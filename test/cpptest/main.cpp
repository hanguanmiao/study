#include <iostream>
#include <string>

//g++ -std=c++11 -Wall -Wextra -g -O0 main.cpp
using namespace std;

string covertString(string str);
int findsubstring(string str);
bool isyuanyin(char ch);
bool isfuyin(char ch);
bool isfuyinExecptR(char ch);

int main() {
    string str;
    int count=0;

    while(cin >> str){
        str = covertString(str);
        count += findsubstring(str);
    }

    cout << count << endl;

    return 0;
}

string covertString(string str){
    string res;
    int size = static_cast<int>(str.size());

    res.resize(size);

    for(int i=size-1, j=0; i>=0; --i,++j){
        if(str[i] < 'a' || str[i] > 'z'){
            res = str;
            break;
        }

        res[j] = str[i];
    }

    return res;
}


int findsubstring(string str){
    int size = static_cast<int>(str.size());
    int count = 0;

    if(size < 4) return 0;

    for(int i=size-1; i>=3; --i){
        if(str[i] != 'e') continue;
        if(!isfuyinExecptR(str[i-1])) continue;
        if(!isyuanyin(str[i-2])) continue;
        if(!isfuyin(str[i-3])) continue;

        ++count;
        --i;
    }

    return count;
}

bool isyuanyin(char ch){
    if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'){
        return true;
    }

    return false;
}

bool isfuyin(char ch){
    if(ch < 'a' || ch > 'z') return false;

    return !isyuanyin(ch);
}

bool isfuyinExecptR(char ch){
    if(ch == 'r') return false;

    return isfuyin(ch);
}


// ekam a ekac
// !ekam a ekekac

// make a cake
// !ekam a cakeke
