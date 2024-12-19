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

unsigned long long find2(pair<int, int> A, pair<int, int> B, pair<unsigned long long, unsigned long long> target,
                         pair<unsigned long long, unsigned long long> start,
                         map<pair<unsigned long long, unsigned long long>, unsigned long long> & dict){
    queue<pair<unsigned long long, unsigned long long>> q;
    dict[target] = INT_MAX;
    dict[start] = 0;
    q.push(start);
    while(!q.empty()) {
        auto curr = q.front();
        q.pop();
        if(curr == target){
            return dict[curr];
        }
        if(curr.first > target.first && curr.second > target.second) {
            break;
        }
        cout << "curr is " << curr.first << " " << curr.second <<endl;
        dict[{curr.first + A.first, curr.second + A.second}] = min(dict[curr] + 3, dict[{curr.first + A.first, curr.second + A.second}]);
        dict[{curr.first + B.first, curr.second + B.second}] = min(dict[curr] + 1, dict[{curr.first + B.first, curr.second + B.second}]);
        q.push({curr.first + A.first, curr.second + A.second});
        q.push({curr.first + B.first, curr.second + B.second});
    }
    return dict[target];
}

long long find3(pair<long long, long long> A, pair<long long, long long> B, pair<long long, long long> target){
    long long det = A.first * B.second - A.second * B.first;
    long long detA = target.first * B.second - target.second * B.first;
    long long detB = A.first * target.second - A.second * target.first;

    cout << A.first << " " << A.second << " " << B.first << " " << B.second << " " << target.first << " " << target.second << endl;

    cout << A.first * B.second << " " << detA << " " << detB << endl;
    if(detA == 0 || detA % det != 0 || detB % det != 0){
        return 0;
    }
    else if(detA / det < 0 || detB / det < 0){
        return 0;
    }
    else{
        return detA / det * 3 + detB / det * 1;
    }
}

int main(int argc, char* argv[]){

    string filename = argv[1];
    ifstream file(filename);
    string line;

//    int res = 0;

    long long res = 0;

    while (getline(file, line)) {
        string block;
//        vector<int> nums;

        vector<long long> nums;

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
//            nums.push_back(stoi(it->str()));

            // --- part 2 ---
            nums.push_back(stoll(it->str()));
        }

//        pair<int, int> currPos = {0, 0};
//        map<pair<int, int>, int> dict;
//        pair<int, int> A = {nums[0], nums[1]};
//        pair<int, int> B = {nums[2], nums[3]};
//        pair<int, int> target = {nums[4], nums[5]};

//        int tmp = find(target, dict, A, B, target);
//        cout << tmp << endl;
//        if(tmp == INT_MAX){
//            res = res + 0;
//        }
//        else{
//            res = res + tmp;
//        }

        // --- part 2 ---
        pair<long long, long long> A = {nums[0], nums[1]};
        pair<long long , long long > B = {nums[2], nums[3]};
        pair<long long , long long > target = {nums[4], nums[5]};
//        cout << A.first << " " << A.second << " " << B.first << " " << B.second << " " << target.first << " " << target.second << endl;
        int tmp = find3(A, B, target);
        cout << tmp << endl;
        res = res + tmp;
    }
    file.close();

    cout << res << endl;

    return 0;
}