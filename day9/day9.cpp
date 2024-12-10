#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

unsigned long long compact(map<int, int, std::greater<int>> fMap, vector<int> space){
    int pos = 0 + fMap[0];
    unsigned long long res = 0;

    while(!space.empty() && fMap.size() > 1){
        int currSpace = space.front();
        space.erase(space.begin());
        while(currSpace > 0){
            auto it = fMap.begin();
            if(it->first == 0){
                return res;
            }
            if(it->second == 0){
                fMap.erase(it);
                continue;
            }
            cout << pos << " " << it->first << endl;
            res = res + pos * it->first;
            it->second--;
            currSpace--;
            pos++;
        }
        auto it = prev(prev(fMap.end()));
        while(it->second > 0){
            cout << pos << " " << it->first << endl;
            res = res + pos * it->first;
            it->second--;
            pos++;
        }
        fMap.erase(it);
    }
    for(auto & it : fMap) {
        cout << it.first << " " << it.second << endl;
    }
    return res;
}

unsigned long long compact2(map<int, int, std::greater<int>> fMap, vector<int> space){
    int pos = 0 + fMap[0];
    unsigned long long res = 0;

    auto itB = fMap.begin();
    auto itE = prev(prev(fMap.end()));

    while(!space.empty() && fMap.size() > 1){
        int currSpace = space.front();
        space.erase(space.begin());

        if(currSpace >= itB->second) {
            while(itB->second > 0) {
                if (itB->first == 0) {
                    return res;
                }
                cout << " moved " << pos << " " << itB->first << endl;
                res = res + pos * itB->first;
                itB->second--;
                pos++;
            }
            fMap.erase(itB);
            itB = fMap.begin();
        }
        else{
            pos = pos + currSpace;
            while(itE->second >= 0) {
                if (itE->first == 0) {
                    return res;
                }
                if (itE->second == 0) {
                    fMap.erase(itE);
                }
                cout << "in order " << pos << " " << itB->first << endl;
                res = res + pos * itE->first;
                itE->second--;
                pos++;
            }
            itE = prev(prev(fMap.end()));
        }
    }
    for(auto & it : fMap) {
        cout << it.first << " " << it.second << endl;
    }

    return res;
}

int main(int argc, char* argv[]) {
    string filename = argv[1];
    ifstream file(filename);
    string line;

    bool f = true;

    getline(file, line);
    istringstream is(line);

    char scan;

    int fileIdx = 0;
    map<int, int, std::greater<int>> fMap;
    vector<int> space;
    map<int, int> spaceMsp;

    while(is >> scan){
        if(f){
            fMap[fileIdx] = scan - '0';
            fileIdx++;
            f = false;
        }
        else if(!f){
            space.push_back(scan - '0');
            f = true;

        }
    }

//    for(auto & tmp : fMap){
//        cout << " index is " << tmp.first << " num of file is " << tmp.second << endl;
//    }
//    for(int i = 0; i < space.size(); i++){
//        cout << " space is " << space[i] << " ";
//    }
//    cout << endl;

    file.close();

    cout << "idx is " << fileIdx << endl;
    unsigned long long res = compact(fMap, space);
    cout << res << endl;

//    unsigned long long res2 = compact2(fMap, space);
//    cout << res2 << endl;

    return 0;
}