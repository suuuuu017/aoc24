#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <cmath>

using namespace std;

map<unsigned long long, unsigned long long> dict;

map<unsigned long long, vector<unsigned long long>> splitDict;

map<pair<unsigned long long, int>, unsigned long long> memo;

unsigned long long zero2one(unsigned long long a){
    if(a == 0){
        return 1;
    }
    return a;
}

vector<unsigned long long> split(unsigned long long a){
//    cout << a << endl;
    unsigned long long digit = static_cast<unsigned long long>(log10(a)) + 1;
    if(digit % 2 == 0){
        unsigned long long half = pow(10, digit / 2);
        return {a / half, a % half};
    }
    return {};
}

unsigned long long multi(unsigned long long a){
    if(dict.find(a) == dict.end()){
        dict[a] = a * 2024;
    }
    return dict[a];
//    return a * 2024;
}

unsigned long long dp(map<pair<unsigned long long, int>, unsigned long long>& memo, pair<unsigned long long, int> tmp){
    unsigned long long a = tmp.first;
    int currB = tmp.second;
    // cout << "finding " << a << " " << currB << endl;
    if(currB == 0){
        if(memo.find(tmp) == memo.end()){
            memo[tmp] = 1;
            // cout << "found  " << memo[tmp] << endl;
            return 1;
        }
        else{
            return memo[tmp];
        }
    }
    else if(memo.find(tmp) == memo.end()){
        if(a == 0){
            unsigned long long tmpN = zero2one(a);
            // newNums.push_back(tmp);
            memo[{a, currB}] = dp(memo, {tmpN, currB - 1});
        }
        else {
            vector<unsigned long long> sRes = split(a);
            if(sRes.empty()){
                unsigned long long tmpN = multi(a);
                memo[{a, currB}] = dp(memo, {tmpN, currB - 1});
            }
            else{
                memo[{a, currB}] = dp(memo, {sRes[0], currB - 1}) + dp(memo, {sRes[1], currB - 1});
            }
        }
        return memo[tmp];
    }
    else{
        // cout << "found  " << memo[tmp] << endl;
        return memo[tmp];
    }
}

int main(int argc, char* argv[]) {

    // string filename = argv[1];
    // ifstream file(filename);
    // string line;

    // getline(file, line);
    // istringstream stream(line);
    vector<unsigned long long> nums;

    // unsigned long long scan;
    // while (stream >> scan) {
    //     nums.push_back(scan);
    // }

    // file.close();
    nums = {572556, 22, 0, 528, 4679021, 1, 10725, 2790};
    int blink = 75;

    // for(unsigned long long i = 0; i < blink; i++){
    // vector<unsigned long long> newNums;
    unsigned long long res = 0;
    cout << "bf for " << res << endl;
    for(unsigned long long j = 0; j < nums.size(); j++){
        // }
        // nums = newNums;
        // cout << " cal is " << dp(memo, {nums[j], blink}) << endl;
        res = res + dp(memo, {nums[j], blink});
    }
//    for(int i = 0; i < nums.size(); i++) {
//        cout << nums[i] << " ";
//        cout << nums.size() << endl;
//    }
    // unsigned long long res= nums.size();
    cout << res << endl;

    return 0;

}