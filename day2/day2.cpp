#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

bool stable(vector<int> nums){
    int num;
    int next;
    for(int i = 0; i < nums.size() - 1; i++){
        num = nums[i];
        next = nums[i+1];
        if(abs(next - num) < 1 || abs(next - num) > 3){
            return false;
        }
    }
    return true;
}

bool mono(vector<int> nums){
    bool increase = true;
    bool decrease = true;
    int num;
    int next;
    for(int i = 0; i < nums.size() - 1; i++){
        num = nums[i];
        next = nums[i+1];
        if(next > num){
            decrease = false;
        }
        if(next < num){
            increase = false;
        }
    }
    return increase || decrease;
}

int main() {
    string filename = "input.txt";

    ifstream file(filename);

    string line;

    int res = 0;

    while (getline(file, line)) {
        istringstream stream(line);
        vector<int> nums;

        int scan;
        while (stream >> scan) {
            nums.push_back(scan);
        }
        if(stable(nums) && mono(nums)) {
            res++;
            continue;
        }
        for(int i = 0; i < nums.size(); i++){
            vector<int> newNums = nums;
            newNums.erase(newNums.begin() + i);
            if(stable(newNums) && mono(newNums)){
                res++;
                break;
            }
        }
    }
    file.close();

    cout << res << endl;

    return 0;
}
