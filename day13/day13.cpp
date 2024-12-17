#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <cmath>
#include <set>
#include <climits>
#include <regex>

using namespace std;

int find(pair<int, int> currPos, map<pair<int, int>, int> & dict, pair<int, int> A, pair<int, int> B, pair<int, int> target){
    auto curr = currPos;
    int currX = curr.first;
    int currY = curr.second;
    // cout << currX << " " << currY << " " << endl;
    if(dict.find({currX, currY}) != dict.end()){
        return dict[{currX, currY}];
    }
    if(currX == 0 && currY == 0){
        dict[{currX, currY}] = 0;
        return 0;
    }
    if(currX < 0 || currY < 0 || currX > target.first || currY > target.second){
        dict[{currX, currY}] = INT_MAX;
        return INT_MAX;
    }
    int first = find({currX - A.first, currY - A.second}, dict, A, B, target);
    int second = find({currX - B.first, currY - B.second}, dict, A, B, target);
    if(first > 400 && second > 400){
        dict[{currX, currY}] = INT_MAX;
    }
    else if(first == INT_MAX){
        dict[{currX, currY}] = second + 1;
    }
    else if(second == INT_MAX){
        dict[{currX, currY}] = first + 3;
    }
    else{
        // cout << currX << " " << currY << " " << min(first + 3, second + 1) << endl;
        dict[{currX, currY}] = min(first + 3, second + 1);
    }
    return dict[{currX, currY}];
}

int main(int argc, char* argv[]){

    string filename = argv[1];
    ifstream file(filename);
    string line;

    int res = 0;

    while (getline(file, line)) {
        string block;
        vector<int> nums;
        while(!line.empty()){
            block = block + line;
            getline(file, line);
            if(file.eof()){
                break;
            }
        }
//        cout << block << endl;
        regex numberPattern("[-]?\\d+");
        auto numbersBegin = sregex_iterator(block.begin(), block.end(), numberPattern);
        auto numbersEnd = sregex_iterator();
        for (auto it = numbersBegin; it != numbersEnd; ++it) {
            nums.push_back(stoi(it->str()));
        }

        pair<int, int> currPos = {0, 0};
        map<pair<int, int>, int> dict;
        pair<int, int> A = {nums[0], nums[1]};
        pair<int, int> B = {nums[2], nums[3]};
        pair<int, int> target = {nums[4], nums[5]};

        int tmp = find(target, dict, A, B, target);
//        cout << tmp << endl;
        if(tmp == INT_MAX){
            res = res + 0;
        }
        else{
            res = res + tmp;
        }
    }
    file.close();

    cout << res << endl;

//    map<pair<int, int>, int> dict;
//    pair<int, int> A = {17, 86};
//    pair<int, int> B = {84, 37};
//    pair<int, int> target = {7870, 6450};
//
//    cout << find(target, dict, A, B, target);

    return 0;
}