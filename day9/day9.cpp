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

unsigned long long compact2(map<int, int, std::greater<int>> fMap, vector<int> space,
                            vector<vector<int>> space2pos, map<int, int> idx2pos){
    int pos = 0 + fMap[0];
    unsigned long long res = 0;

//    for(int i = 0; i < space2pos.size(); i++){
//        cout << "spaceSize " << space2pos[i][0] << " pos is " << space2pos[i][1] << endl;
//    }
//    for(auto & a : idx2pos){
//        cout << "idx " << a.first << " pos is " << a.second << endl;
//    }

    int i = 0;

//    while(!space.empty() && fMap.size() > 1){
        auto curr = fMap.begin();


        while(curr->first != 0) {
//            cout << " current procssing "  << curr->first << endl;
            i = 0;
            int currSize = space[i];
            while (currSize < curr->second && i < space.size()) {
                i++;
                currSize = space[i];
            }
            if (i < space.size() && space2pos[i][1] < idx2pos[curr->first]) {
//                cout << "found space " << space2pos[i][1] << " space size " << space[i] << endl;
                idx2pos[curr->first] = space2pos[i][1];
                space[i] = space[i] - curr->second;
                space2pos[i][1] = space2pos[i][1] + curr->second;
            }
            advance(curr, 1);
        }
//    }
    for(auto & a : idx2pos){
//        cout << "idx " << a.first << " pos is " << a.second << endl;
        int l = fMap[a.first];
        for(int j = 0; j < l; j++){
            res = res + (a.second + j) * a.first;
        }
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

    vector<vector<int>> space2pos;
    map<int, int> idx2pos;
    int pos = 0;

    while(is >> scan){
        if(f){
            fMap[fileIdx] = scan - '0';
            f = false;

            idx2pos[fileIdx] = pos;
            pos = pos + scan - '0';

            fileIdx++;
        }
        else if(!f){
            space.push_back(scan - '0');
            f = true;

            space2pos.push_back({scan - '0', pos});
            pos = pos + scan - '0';
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

//    cout << "idx is " << fileIdx << endl;
//    unsigned long long res = compact(fMap, space);
//    cout << res << endl;

    unsigned long long res2 = compact2(fMap, space, space2pos, idx2pos);
    cout << res2 << endl;

    return 0;
}