#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
        int outsize = orders.size();
        map<int,map<string, int>> tablefoodCounts;
        set<string> foods;
        vector<vector<string>> ret;

        for(int i=0; i<outsize; ++i){
            int tablenum = stoi(orders[i][1]);
            foods.insert(orders[i][2]); // 保存食物名
            if(tablefoodCounts.count(tablenum)){
                map<string,int> &foodcounts = tablefoodCounts[tablenum];
                if(foodcounts.count(orders[i][2])){
                    ++foodcounts[orders[i][2]];
                }else{
                    foodcounts[orders[i][2]] = 1;
                }
            }else{
                map<string,int> temp;
                temp[orders[i][2]] = 1;
                tablefoodCounts[tablenum] = temp;
//                tablefoodCounts[tablenum] = map<string,int>({orders[i][2], 1});
            }
        }

        vector<string> temp;
        temp.push_back("Table");
        for (auto it=foods.begin(); it!=foods.end(); ++it) {
            temp.push_back(*it);
        }
        ret.push_back(std::move(temp));
        temp.clear();

        for(auto it=tablefoodCounts.begin(); it!=tablefoodCounts.end(); ++it){
            temp.push_back(to_string(it->first));
            map<string,int> &foodcounts = it->second;
            for(auto ij=foods.begin(); ij!=foods.end(); ++ij){
                if(foodcounts.count(*ij)){
                    temp.push_back(to_string(foodcounts[*ij]));
                }else{
                    temp.push_back(to_string(0));
                }
            }
            ret.push_back(std::move(temp));
            temp.clear();
        }

        return ret;
    }
};


void printVec(vector<vector<string>> &input){
    int size = input.size();

    for(int i=0; i<size; ++i){
        vector<string> &inter = input[i];
        int intersize = inter.size();

        for(int j=0; j<intersize; ++j){
            cout<<inter[j]<<',';
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[]){
    Solution s;
    vector<vector<string>> input;
    vector<vector<string>> res;

    input = {{"David","3","Ceviche"},{"Corina","10","Beef Burrito"},{"David","3","Fried Chicken"},
             {"Carla","5","Water"},{"Carla","5","Ceviche"},{"Rous","3","Ceviche"}};
    res = s.displayTable(input);
    printVec(res);

    return 0;
}

