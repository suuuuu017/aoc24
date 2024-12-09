#include <iostream>
#include <fstream>
#include <regex>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <cmath>

using namespace std;

bool isGood(long long res, vector<int> nums, int index, long long curr){
    if(index == nums.size()){
        return curr == res;
    }
    if(curr > res){
        return false;
    }

    if(isGood(res, nums, index + 1, curr + nums[index])){
        return true;
    }
    if(isGood(res, nums, index + 1, curr * nums[index])){
        return true;
    }

    return false;
}

bool isGood2(long long res, vector<int> nums, int index, long long curr){
    if(index == nums.size()){
        return curr == res;
    }
    if(curr > res){
        return false;
    }

    if(isGood2(res, nums, index + 1, curr + nums[index])){
        return true;
    }
    if(isGood2(res, nums, index + 1, curr * nums[index])){
        return true;
    }

    int d = (nums[index] > 0) ? static_cast<int>(log10(nums[index])) + 1 : 1;
    if(isGood2(res, nums, index + 1, curr * pow(10, d) + nums[index])){
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {

    string filename = argv[1];
    ifstream file(filename);
    string line;

    long long total = 0;

    while (getline(file, line)) {
        istringstream curr(line);
        string tmp;
        getline(curr, tmp, ':');

        long long res = stoll(tmp);
        vector<int> nums;

        string numsTmp;
        while(getline(curr >> ws, numsTmp, ' ')){
            nums.push_back(stoi(numsTmp));
        }

        if(isGood(res, nums, 1 , nums[0])){
            total = total + res;
        }
        else if(isGood2(res, nums, 1, nums[0])){
            total = total + res;
        }

//        cout << res << " : ";
//        for(const auto & num : nums){
//            cout << num << " ";
//        }
//        cout << endl;

    }
    file.close();

    cout << "Result: " << total << endl;
    return total;
}