#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

using namespace std;

//struct CustomHash {
//    size_t operator()(unsigned long x) const {
//        x ^= (x >> 33);
//        x *= 0xff51afd7ed558ccd;
//        x ^= (x >> 33);
//        x *= 0xc4ceb9fe1a85ec53;
//        x ^= (x >> 33);
//        return x;
//    }
//};

unordered_map<unsigned long, unsigned long> dict;

unordered_map<unsigned long, vector<unsigned long>> splitDict;

unsigned long zero2one(unsigned long a){
    if(a == 0){
        return 1;
    }
    return a;
}

vector<unsigned long> split(unsigned long a){
//    cout << a << endl;
    if(splitDict.find(a) == splitDict.end()) {
//        unsigned long digit = static_cast<unsigned long>(log10(a)) + 1;
        unsigned long digit = 0;
        unsigned long temp = a;
        while (temp > 0) {  // Count the number of digits
            temp /= 10;
            digit++;
        }
        if (digit % 2 == 0) {
            unsigned long half = pow(10, digit / 2);
            splitDict[a] = {a / half, a % half};
        }
        else{
            splitDict[a] = {};
        }
    }
    return splitDict[a];
}

unsigned long multi(unsigned long a){
    if(dict.find(a) == dict.end()){
//        dict[a] = a * 2024;
        dict[a] = -24 * a + (a << 11);
    }
    return dict[a];
//    return a * 2024;
}

int main(int argc, char* argv[]) {

    string filename = argv[1];
    ifstream file(filename);
    string line;

    getline(file, line);
    istringstream stream(line);
    vector<unsigned long> nums;

    unsigned long scan;
    while (stream >> scan) {
        nums.push_back(scan);
    }

    file.close();

    int blink = 75;

    dict.reserve(10000);
    splitDict.reserve(10000);

    sort(nums.begin(), nums.end());

    for(int i = 0; i < blink; i++){
        cout << "blinking " << i << endl;
        cout << "dict size " << dict.size() << endl;
        cout << "split dict size " << splitDict.size() << endl;
        vector<unsigned long> newNums;
        newNums.reserve(nums.size() * 2);

        for(unsigned long j = 0; j < nums.size(); j++){
            unsigned long a = nums[j];
            if(a == 0){
                unsigned long tmp = zero2one(a);
                newNums.push_back(tmp);
            }
            else {
                vector<unsigned long> sRes = split(a);
                if(sRes.empty()){
                    unsigned long tmp = multi(a);
                    newNums.push_back(tmp);
                }
                else{
                    unsigned long res1 = sRes[0];
                    unsigned long res2 = sRes[1];
                    newNums.push_back(res1);
                    newNums.push_back(res2);
//                    newNums.insert(newNums.end(), std::make_move_iterator(sRes.begin()), std::make_move_iterator(sRes.end()));
                }
            }
        }
//        nums = newNums;
        nums.swap(newNums);
    }
//    for(int i = 0; i < nums.size(); i++) {
//        cout << nums[i] << " ";
//        cout << nums.size() << endl;
//    }
    unsigned long res= nums.size();
    cout << res << endl;

    return 0;

}