#include <iostream>
#include <map>
#include <set>

//g++ -std=c++11 -Wall -Wextra -g -O0 main.cpp
using namespace std;


int main() {
    int nummask;
    int numnode;
    int totalbt;
    int totaltime;

    multimap<int,int> brts;
    multiset<int> rts;

    cin >> nummask;
    for(int i=0; i<nummask; ++i){
        cin >> numnode;

        totalbt = 0;
        totaltime = 0;
        int bt, rt;
        int tmptotalbt;
        for(int j=0; j<numnode; ++j){
            cin >> bt >> rt;

            totalbt += bt;
            brts.insert({rt,bt});
        }

        tmptotalbt = totalbt;

        for(auto it=brts.rbegin(); it != brts.rend(); ++it){
            tmptotalbt -= it->second;
            rts.insert(it->first - tmptotalbt);
        }

        totaltime += totalbt + *rts.rbegin();
        brts.clear();
        rts.clear();

        cout << totaltime << endl;
    }

    return 0;
}

/*
1
1
2 2
*/

/*
2
2
1 1
2 2
3
1 1
2 2
3 3
*/

/*
1
3
1 100
2 100
3 3
*/
