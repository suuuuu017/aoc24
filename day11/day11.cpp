#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

map<unsigned long long, unsigned long long> dict;

map<unsigned long long, vector<unsigned long long>> splitDict;

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

int main(int argc, char* argv[]) {

    string filename = argv[1];
    ifstream file(filename);
    string line;

    getline(file, line);
    istringstream stream(line);
    vector<unsigned long long> nums;

    unsigned long long scan;
    while (stream >> scan) {
        nums.push_back(scan);
    }

    file.close();

    unsigned long long blink = 25;

    for(unsigned long long i = 0; i < blink; i++){
        vector<unsigned long long> newNums;
        for(unsigned long long j = 0; j < nums.size(); j++){
            unsigned long long a = nums[j];
            if(a == 0){
                unsigned long long tmp = zero2one(a);
                newNums.push_back(tmp);
            }
            else {
                vector<unsigned long long> sRes = split(a);
                if(sRes.empty()){
                    unsigned long long tmp = multi(a);
                    newNums.push_back(tmp);
                }
                else{
                    newNums.insert(newNums.end(), sRes.begin(), sRes.end());
                }
            }
        }
        nums = newNums;
    }
//    for(int i = 0; i < nums.size(); i++) {
//        cout << nums[i] << " ";
//        cout << nums.size() << endl;
//    }
    unsigned long long res= nums.size();
    cout << res << endl;

    return 0;

}